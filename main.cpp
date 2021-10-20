#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include "ASIMType.h"
#include <string.h>
#include <math.h>
#include <mutex>

#define USE_UDP_OR_TCP true
char *msgBuffer;//一帧数据的buffer
int msgBufferAllocSize = 1024 * 40;//对应的已申请空间
long msgBufferUsedSize = 0;//对应的已使用空间

int client_sockfd;
struct sockaddr_in remote_addr; //服务器端网络地址结构体
unsigned int sin_size = sizeof(struct sockaddr_in);
#define RECV_BUF_SIZE (1024 * 1024 * 2)
char recvBuf[RECV_BUF_SIZE];  //接收数据的缓冲区

bool bScenarioFinished = true; //当前测试场景是否结束场景
static const unsigned int scOwnId = 1;  // ID of own vehicle

// globally store nearest object
typedef struct{
    ASIM_OBJECT_STATE_t mNearestObject;
    ASIM_OBJECT_STATE_t mOwnObject;
    std::mutex mMutex; //互斥量
}ObjData;
ObjData objData;


/**
 * 测试场景限制：
 * 场景中只能有主车和一个交通车两个对象 (缺乏处理多个障碍物的能力)
 * 两车必须在同一条路上 (ObjectState.base.pos.x作为道路坐标系s坐标，用于计算相对距离)
 * 沿s轴正方向行驶
 * 主车在交通车后面
 * 不能进行转向 (缺乏转向功能)
 */
double computeAcc()
{
    ASIM_OBJECT_STATE_t mNearestObject{0};
    ASIM_OBJECT_STATE_t mOwnObject{0};

    objData.mMutex.lock();
    mOwnObject = objData.mOwnObject;
    mNearestObject = objData.mNearestObject;
    objData.mMutex.unlock();

    // do we have a valid nearest object?
    bool haveSensorObject = ( mNearestObject.base.id > 0 );   // sensor object must not be older than 1.0s

    double ownSpeed = sqrt( mOwnObject.ext.speed.x * mOwnObject.ext.speed.x + mOwnObject.ext.speed.y * mOwnObject.ext.speed.y );

    double accelTgtDist  = 0.0;
    double accelTgtSpeed = ( 30.0 - ownSpeed ) / 5.0;   // default speed should be own preferred speed

    if ( haveSensorObject )
    {
        // 计算相对速度
        double relativeSpeed = mNearestObject.ext.speed.x - mOwnObject.ext.speed.x;

        // let's go for the same speed as preceding vehicle:
        if ( relativeSpeed < -1.0e-3 )
        {
            accelTgtSpeed = 2.0 * relativeSpeed / 5.0;
        }
        else
        {
            accelTgtSpeed = 0.0;
        }

        // let's go for a 2s distance
        double tgtDist = ownSpeed * 2.0; //与前车保持的距离

        if ( tgtDist < 10.0 )   // minimum  distance to keep
            tgtDist = 10.0;

        // 计算相对距离
        double relativeDist = mNearestObject.base.pos.x - mOwnObject.base.pos.x;

        accelTgtDist = ( relativeDist - tgtDist ) / 10.0;
    }

    float accelTgt = accelTgtDist + accelTgtSpeed;
    std::cout << "accelTgt=" << accelTgt << std::endl;

    return accelTgt;
}

/**
 * 非控制在环，需要提供准确数值的数据项：
 * pkgBody->base.pos.x
 * pkgBody->base.pos.y
 * pkgBody->base.pos.z
 * pkgBody->base.pos.h
 * pkgBody->ext.speed.x
 * pkgBody->ext.speed.y
 * pkgBody->ext.speed.h
 * pkgBody->ext.accel.x
 * pkgBody->ext.accel.y
 * pkgBody->ext.accel.h
 * pkgBody->ext.traveledDist
 *
 * 控制在环(动力学模型挂载外部)，需要提供准确数值的数据项：
 * pkgBody->ext.speed.h
 * pkgBody->ext.accel.x
 */
void generatePkgObjectState()
{
    double accelTgt = computeAcc();

    //生成ASIM_PKG_ID_OBJECT_STATE
    ASIM_MSG_ENTRY_HDR_t *pkghead = (ASIM_MSG_ENTRY_HDR_t *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->headerSize = sizeof(ASIM_MSG_ENTRY_HDR_t);
    pkghead->dataSize = sizeof(ASIM_OBJECT_STATE_t);
    pkghead->elementSize = sizeof(ASIM_OBJECT_STATE_t);
    pkghead->pkgId = ASIM_PKG_ID_OBJECT_STATE;
    pkghead->flags = ASIM_PKG_FLAG_EXTENDED; //包括扩展信息字段ext

    //填充PKG body
    ASIM_OBJECT_STATE_t *pkgBody = (ASIM_OBJECT_STATE_t *)(pkghead + 1);

    pkgBody->base.id = 1;//主车Id为1
    strcpy(pkgBody->base.name, "Ego");

    //线速度与角速度
    pkgBody->ext.speed.h = 0.0;
    pkgBody->ext.speed.flags = ASIM_COORD_FLAG_ANGLES_VALID;//角速度有效
    pkgBody->ext.speed.type = ASIM_COORD_TYPE_TRACK;//坐标系类型,道路坐标系(x=s, y=t )

    //线加速度与角加速度
    pkgBody->ext.accel.x = accelTgt;
    pkgBody->ext.accel.flags = ASIM_COORD_FLAG_POINT_VALID;//线加速度有效
    pkgBody->ext.accel.type = ASIM_COORD_TYPE_TRACK;//坐标系类型，道路坐标系(x=s, y=t )

    msgBufferUsedSize += pkghead->headerSize + pkghead->dataSize;//更新msgBuffer的已使用空间
}

void generateMsg()
{
    //清空msgBuffer
    memset(msgBuffer, 0, msgBufferAllocSize);
    msgBufferUsedSize = 0;//更新msgBuffer的已使用空间

    //生成Msg头部
    ASIM_MSG_HDR_t *msgHead = (ASIM_MSG_HDR_t *) msgBuffer;

    //填充Msg头部
    msgHead->version = 01; //版本
    msgHead->headerSize = sizeof(ASIM_MSG_HDR_t); //Msg头部大小
    msgHead->frameNo = 1; //帧号
    msgHead->simTime = 1.2; //仿真时间

    msgBufferUsedSize += sizeof(ASIM_MSG_HDR_t);//更新msgBuffer的已使用空间

    //生成PKG_ID_START_OF_FRAME
    ASIM_MSG_ENTRY_HDR_t *pkgHead = (ASIM_MSG_ENTRY_HDR_t *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkgHead->headerSize = sizeof(ASIM_MSG_ENTRY_HDR_t);
    pkgHead->pkgId = ASIM_PKG_ID_START_OF_FRAME;
    pkgHead->dataSize = 0;
    pkgHead->elementSize = 0;
    pkgHead->flags = ASIM_PKG_FLAG_NONE;

    msgBufferUsedSize += pkgHead->headerSize + pkgHead->dataSize;//更新msgBuffer的已使用空间

    if (bScenarioFinished) //如果当前测试场景结束，发送trigger
    {
        //生成ASIM_PKG_ID_TRIGGER
        ASIM_MSG_ENTRY_HDR_t *pkgTrigger = (ASIM_MSG_ENTRY_HDR_t *)(msgBuffer + msgBufferUsedSize);

        //填充PKG头部
        pkgTrigger->headerSize = sizeof(ASIM_MSG_ENTRY_HDR_t);
        pkgTrigger->pkgId = ASIM_PKG_ID_TRIGGER;
        pkgTrigger->dataSize = 0;
        pkgTrigger->elementSize = 0;
        pkgTrigger->flags = ASIM_PKG_FLAG_NONE;

        msgBufferUsedSize += pkgTrigger->headerSize + pkgTrigger->dataSize;//更新msgBuffer的已使用空间

        bScenarioFinished = false;
    }
    else //发送其他pkg
    {
        generatePkgObjectState();
    }

    //生成ASIM_PKG_ID_END_OF_FRAME
    ASIM_MSG_ENTRY_HDR_t* pkgEnd = (ASIM_MSG_ENTRY_HDR_t *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkgEnd->headerSize = sizeof(ASIM_MSG_ENTRY_HDR_t);
    pkgEnd->pkgId = ASIM_PKG_ID_END_OF_FRAME;
    pkgEnd->dataSize = 0;
    pkgEnd->elementSize = 0;
    pkgEnd->flags = ASIM_PKG_FLAG_NONE;

    msgBufferUsedSize += pkgEnd->headerSize + pkgEnd->dataSize;//更新msgBuffer的已使用空间

    msgHead->dataSize = msgBufferUsedSize - msgHead->headerSize; //Msg数据部分大小
}

void recvData()
{
    int recvLen = 0;
    while (true)
    {
#if USE_UDP_OR_TCP
        /*接收服务端的数据--recvfrom是无连接的,第5个参数可以获得数据发送者的地址*/
        if((recvLen = recvfrom(client_sockfd, recvBuf , RECV_BUF_SIZE , 0, (struct sockaddr *)&remote_addr, &sin_size)) < 0)//recvfrom()返回数据字节长度，若对方已经结束返回0,出错返回-1
        {
            perror("recvfrom error");
            return;
        }
        //printf("received packet from %s:\n", inet_ntoa(remote_addr.sin_addr));
#else
        if ((recvLen = recv(client_sockfd, recvBuf, RECV_BUF_SIZE, 0)) < 0) {
            perror("recv error");
            return;
        }
#endif
        //解析数据
        ASIM_MSG_HDR_t *msgHead = (ASIM_MSG_HDR_t *)recvBuf;//Msg的头部指针
        //std::cout << "headerSize=" << msgHead->headerSize << " dataSize=" << msgHead->dataSize << std::endl;
        char *currentPkg = recvBuf + msgHead->headerSize;//当前Pkg的头部指针

        //第一帧为ASIM_PKG_ID_START_OF_FRAME
        ASIM_MSG_ENTRY_HDR_t *startPkgHead = (ASIM_MSG_ENTRY_HDR_t *)currentPkg;
        if (startPkgHead->pkgId != ASIM_PKG_ID_START_OF_FRAME)
        {
            return;
        }
        //printf("receive ASIM_PKG_ID_START_OF_FRAME\n");
        currentPkg += startPkgHead->headerSize + startPkgHead->dataSize; //指向下一个pkg

        //AD端内部自定义数据结构
        ASIM_OBJECT_STATE_t mNearestObject{0};
        ASIM_OBJECT_STATE_t mOwnObject{0};
        ASIM_ROAD_POS_t mNearestRoadPos{0};
        ASIM_ROAD_POS_t mOwnRoadPos{0};

        while (true)
        {
            auto *pkgHead = (ASIM_MSG_ENTRY_HDR_t *)currentPkg;//Pkg的头部指针
            if (pkgHead->pkgId == ASIM_PKG_ID_OBJECT_STATE) //解析ASIM_PKG_ID_OBJECT_STATE
            {
                //printf("receive ASIM_PKG_ID_OBJECT_STATE\n");
                auto *pkgData = (ASIM_OBJECT_STATE_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                unsigned int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
                for (int i = 0; i < elementNum; i++) //解析每个元素
                {
                    if ( pkgData->base.id == scOwnId )
                    {
                        memcpy( &mOwnObject, pkgData, sizeof( ASIM_OBJECT_STATE_t ) );
                    }
                    else
                    {
                        memcpy( &mNearestObject, pkgData, sizeof( ASIM_OBJECT_STATE_t ) );
                    }

                    pkgData += 1;
                }

                //2.AD端内部处理
                //AD TODO
            }
            else if (pkgHead->pkgId == ASIM_PKG_ID_VEHICLE_SYSTEMS) //解析ASIM_PKG_ID_VEHICLE_SYSTEMS
            {
                //printf("receive ASIM_PKG_ID_VEHICLE_SYSTEMS\n");
                auto *pkgData = (ASIM_VEHICLE_SYSTEMS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                unsigned int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
                for (int i = 0; i < elementNum; i++) //解析每个元素
                {
                    pkgData += 1;
                }

                //2.AD端内部处理
                //AD TODO

            }
            else if (pkgHead->pkgId == ASIM_PKG_ID_ROAD_POS) //解析ASIM_PKG_ID_ROAD_POS
            {
                //printf("receive ASIM_PKG_ID_ROAD_POS\n");
                auto *pkgData = (ASIM_ROAD_POS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                unsigned int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
                for (int i = 0; i < elementNum; i++) //解析每个元素
                {
                    if ( pkgData->playerId == scOwnId )
                    {
                        memcpy( &mOwnRoadPos, pkgData, sizeof( ASIM_ROAD_POS_t ) );
                    }
                    else
                    {
                        memcpy( &mNearestRoadPos, pkgData, sizeof( ASIM_ROAD_POS_t ) );
                    }

                    pkgData += 1;
                }

                //2.AD端内部处理
                //AD TODO

            }
            else if (pkgHead->pkgId == ASIM_PKG_ID_SYNC)
            {
                //printf("receive ASIM_PKG_ID_SYNC\n");
                auto *pkgData = (ASIM_SYNC_t *)(currentPkg + pkgHead->headerSize);//数据部分指针
                //1.解析数据
                if (pkgData->cmdMask & 0x01) //最低位为1代表当前测试场景结束
                {
                    bScenarioFinished = true;//收到仿真器发的结束信号
                    std::cout << "FinishSync" << std::endl;
                }

                //2.AD端内部处理
                //AD TODO

            }
            else if (pkgHead->pkgId == ASIM_PKG_ID_END_OF_FRAME) //如果是最后一个Pkg
            {
                printf("receive ASIM_PKG_ID_END_OF_FRAME\n");
                break;
            }

            currentPkg += pkgHead->headerSize + pkgHead->dataSize; //指向下一个pkg
        }

        //base.pos.x作为道路坐标
        mOwnObject.base.pos.x = mOwnRoadPos.roadS;
        mNearestObject.base.pos.x = mNearestRoadPos.roadS;

        //更新数据到objData
        objData.mMutex.lock();
        objData.mOwnObject = mOwnObject;
        objData.mNearestObject = mNearestObject;
        objData.mMutex.unlock();
    }
}

int main() {
    memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
    remote_addr.sin_family=AF_INET; //设置为IP通信
    remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//服务器IP地址
    remote_addr.sin_port=htons(8000); //服务器端口号
#if USE_UDP_OR_TCP
    /*创建客户端套接字--IPv4协议，面向无连接通信，UDP协议*/
    if((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket error");
        return 1;
    }
#else
    if ((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return 1;
    }

    //connect to server
    if (connect(client_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0) {
        perror("socket error");
        return 1;
    }
#endif
        
    std::thread recv_thread(recvData);

    msgBuffer = (char *)malloc(msgBufferAllocSize);//一帧数据的buffer
    if (!msgBuffer)//失败
    {
        std::cout << "Error: msgBuffer malloc fail" << std::endl;
        msgBufferAllocSize = 0;
        return 1;
    }

    // reset the information about the nearest and own object
    memset( &(objData.mNearestObject), 0, sizeof( ASIM_OBJECT_STATE_t ) );
    memset( &(objData.mOwnObject), 0, sizeof( ASIM_OBJECT_STATE_t ) );

    while (true)
    {
        //生成仿真应答数据
        generateMsg();

#if USE_UDP_OR_TCP
        /*向服务器发送数据包*/
        if((sendto(client_sockfd, msgBuffer, msgBufferUsedSize, 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr))) < 0)//返回发送的数据长度，出错返回-1
        {
            perror("send error!");
            return 1;
        }
#else
        if ((send(client_sockfd, msgBuffer, msgBufferUsedSize, 0)) < 0)
        {
            perror("send error!");
            return 1;
        }
#endif

        usleep(20*1000);
    }

    recv_thread.join();
    free(msgBuffer);
    msgBuffer = NULL;
    return 0;
}
