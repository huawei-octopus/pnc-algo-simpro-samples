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

#define USE_UDP_OR_TCP false // true:使用UDP false:使用TCP

char *msgBuffer;//一帧数据的buffer
int msgBufferAllocSize = 1024 * 40;//对应的已申请空间
int msgBufferUsedSize = 0;//对应的已使用空间

int client_sockfd;
struct sockaddr_in remote_addr; //服务器端网络地址结构体
unsigned int sin_size = sizeof(struct sockaddr_in);
#define RECV_BUF_SIZE 1024 * 1024 * 2
//#define RECV_BUF_SIZE 16  //for testing
char recvBuf[RECV_BUF_SIZE];  //接收数据的缓冲区

bool bScenarioFinished = true; //当前测试场景是否结束场景
static const unsigned int scOwnId = 1;  // ID of own vehicle

// globally store nearest object
typedef struct{
    uint32_t frontVehId; //前车Id
    double frontVehSpeedX; //前车纵向速度
    double ownObjectSpeedX; //主车纵向速度
    double ownObjectSpeedY; //主车横向速度
    double relativeDist; //与前车相对距离
    std::mutex mMutex; //互斥量
}ObjData;
ObjData objData;

#if 1 //zxl 2021.08.31 粘包拆包问题的处理
#define PARSE_PACKAGE_SUCESS 0
#define PARSE_PACKAGE_ERROR -1

#define PARSE_SOCKET_SUCESS 0
#define PARSE_SOCKET_NODATA 1               // need receiving the next sockets
#define PARSE_SOCKET_CURBUFFER_NODATA 2     // need receiving the next sockets
#define PARSE_SOCKET_ERROR -1
#endif

#if 1 //zxl 2021.08.31 粘包拆包问题的处理
unsigned int mTotalLen;                          //PKG总长
char* mCurrPBuffer;                              //当前拼接PKG的buff
unsigned int mCurrPkgLen;
char mTempBuff[sizeof(ASIM_MSG_HDR_t) * 2];     //存放PKG的head的一部分
unsigned int mTempLen;
bool mIsMerge;                                  //flag
#endif

/**
 * 测试场景限制：
 * 场景中只能有主车和一个交通车两个对象 (缺乏处理多个障碍物的能力)
 * 两车必须在同一条路上
 * 沿s轴正方向行驶
 * 主车在交通车后面
 * 不能进行转向 (缺乏转向功能)
 */
double computeAcc()
{
    objData.mMutex.lock();
    uint32_t frontVehId = objData.frontVehId; //前车Id
    double frontVehSpeedX = objData.frontVehSpeedX; //前车纵向速度
    double ownObjectSpeedX = objData.ownObjectSpeedX; //主车纵向速度
    double ownObjectSpeedY = objData.ownObjectSpeedY; //主车横向速度
    double relativeDist = objData.relativeDist; //与前车相对距离
    objData.mMutex.unlock();

    // do we have a valid nearest object?
    bool haveSensorObject = ( frontVehId > 0 );   // sensor object must not be older than 1.0s

    double ownSpeed = sqrt( ownObjectSpeedX * ownObjectSpeedX + ownObjectSpeedY * ownObjectSpeedY );

    double accelTgtDist  = 0.0;
    double accelTgtSpeed = ( 30.0 - ownSpeed ) / 5.0;   // default speed should be own preferred speed

    if ( haveSensorObject )
    {
        // 计算相对速度
        double relativeSpeed = frontVehSpeedX - ownObjectSpeedX;

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

        accelTgtDist = ( relativeDist - tgtDist ) / 10.0;
    }

    float accelTgt = accelTgtDist + accelTgtSpeed;
    std::cout << "accelTgt=" << accelTgt << std::endl;

    return accelTgt;
}

void generatePkgDriverCtrl()
{
    double accelTgt = computeAcc();

    //生成ASIM_PKG_ID_DRIVER_CTRL
    ASIM_MSG_ENTRY_HDR_t *pkghead = (ASIM_MSG_ENTRY_HDR_t *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->headerSize = sizeof(ASIM_MSG_ENTRY_HDR_t);
    pkghead->dataSize = sizeof(ASIM_DRIVER_CTRL_t);
    pkghead->elementSize = sizeof(ASIM_DRIVER_CTRL_t);
    pkghead->pkgId = ASIM_PKG_ID_DRIVER_CTRL;
    pkghead->flags = ASIM_PKG_FLAG_NONE;

    //填充PKG body
    ASIM_DRIVER_CTRL_t *pkgBody = (ASIM_DRIVER_CTRL_t *)(pkghead + 1);
    pkgBody->accelTgt = accelTgt;

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
        generatePkgDriverCtrl();
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

#if 1 //zxl 2021.08.31 将解析数据包的功能抽成函数
/**
 * 对parseSocket()中解析完socket后所生成的PKG的处理
 * pkgId的判断：ASIM_PKG_ID_OBJECT_STATE、ASIM_PKG_ID_VEHICLE_SYSTEMS、
 *             ASIM_PKG_ID_ROAD_POS、ASIM_PKG_ID_SYNC、ASIM_PKG_ID_END_OF_FRAME
 */
static int parsePackage(char *pkgBuff)
{
    if(nullptr == pkgBuff)
    {
        return PARSE_PACKAGE_ERROR;
    }

    //std::cout << "parsePackage  start" << std::dec << __LINE__ << std::endl;

    //解析数据
    ASIM_MSG_HDR_t *msgHead = (ASIM_MSG_HDR_t *)pkgBuff;//Msg的头部指针
    //std::cout << "headerSize=" << msgHead->headerSize << " dataSize=" << msgHead->dataSize << std::endl;
    char *currentPkg = pkgBuff + msgHead->headerSize;//当前Pkg的头部指针

    //第一帧为ASIM_PKG_ID_START_OF_FRAME
    ASIM_MSG_ENTRY_HDR_t *startPkgHead = (ASIM_MSG_ENTRY_HDR_t *)currentPkg;
    if (startPkgHead->pkgId != ASIM_PKG_ID_START_OF_FRAME)
    {
        return PARSE_PACKAGE_ERROR;
    }

    //std::cout << "parsePackage  " << std::dec << __LINE__ << std::endl;

    //printf("receive ASIM_PKG_ID_START_OF_FRAME\n");
    currentPkg += startPkgHead->headerSize + startPkgHead->dataSize; //指向下一个pkg

    //AD端内部自定义数据结构
    uint32_t frontVehId = 0; //前车Id
    double frontVehSpeedX = 0.0; //前车纵向速度
    double ownObjectSpeedX = 0.0; //主车纵向速度
    double ownObjectSpeedY = 0.0; //主车横向速度
    double relativeDist = 0.0; //与前车相对距离

    while (1)
    {
        ASIM_MSG_ENTRY_HDR_t *pkgHead = (ASIM_MSG_ENTRY_HDR_t *)currentPkg;//Pkg的头部指针

        if (pkgHead->pkgId == MIL_PKG_ID_EGO_DATA) //解析MIL_PKG_ID_EGO_DATA
        {
            //printf("receive MIL_PKG_ID_EGO_DATA\n");
            MIL_EGO_STATE_t *pkgData = (MIL_EGO_STATE_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

            //1.解析数据
            int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
            for (int i = 0; i < elementNum; i++) //解析每个元素
            {
                ownObjectSpeedX = pkgData->ext.speed.x; //主车纵向速度
                ownObjectSpeedY = pkgData->ext.speed.y; //主车横向速度

                break;
                //pkgData += 1;
            }

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->pkgId == MIL_PKG_ID_OBJECT_DATA) //解析MIL_PKG_ID_OBJECT_DATA
        {
            //printf("receive MIL_PKG_ID_OBJECT_DATA\n");
            MIL_OBJECT_STATE_t *pkgData = (MIL_OBJECT_STATE_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

            //1.解析数据
            int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
            for (int i = 0; i < elementNum; i++) //解析每个元素
            {
                frontVehId = pkgData->base.id; //前车Id
                frontVehSpeedX = pkgData->ext.speed.x; //前车纵向速度
                relativeDist = pkgData->milBase.distance_X; //与前车相对距离

                break;
                //pkgData += 1;
            }

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->pkgId == ASIM_PKG_ID_VEHICLE_SYSTEMS) //解析ASIM_PKG_ID_VEHICLE_SYSTEMS
        {
            //printf("receive ASIM_PKG_ID_VEHICLE_SYSTEMS\n");
            ASIM_VEHICLE_SYSTEMS_t *pkgData = (ASIM_VEHICLE_SYSTEMS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

            //1.解析数据
            int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
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
            ASIM_ROAD_POS_t *pkgData = (ASIM_ROAD_POS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

            //1.解析数据
            int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
            for (int i = 0; i < elementNum; i++) //解析每个元素
            {
                pkgData += 1;
            }

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->pkgId == ASIM_PKG_ID_SYNC)
        {
             //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //printf("receive ASIM_PKG_ID_SYNC\n");
            ASIM_SYNC_t *pkgData = (ASIM_SYNC_t *)(currentPkg + pkgHead->headerSize);//数据部分指针
            //1.解析数据
            if (pkgData->cmdMask & 0x01) //最低位为1代表当前测试场景结束
            {
                bScenarioFinished = true;//收到仿真器发的结束信号
                //std::cout << "FinishSync" << std::endl;
            }

             //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->pkgId == ASIM_PKG_ID_END_OF_FRAME) //如果是最后一个Pkg
        {
             //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //printf("receive ASIM_PKG_ID_END_OF_FRAME\n");
            break;
        }
        currentPkg += pkgHead->headerSize + pkgHead->dataSize; //指向下一个pkg
    }

    //更新数据到objData
    objData.mMutex.lock();
    objData.frontVehId = frontVehId; //前车Id
    objData.frontVehSpeedX = frontVehSpeedX; //前车纵向速度
    objData.ownObjectSpeedX = ownObjectSpeedX; //主车纵向速度
    objData.ownObjectSpeedY = ownObjectSpeedY; //主车横向速度
    objData.relativeDist = relativeDist; //与前车相对距离
    objData.mMutex.unlock();

    //std::cout << "parsePackage   end  " << std::dec << __LINE__ << std::endl;

    return PARSE_PACKAGE_SUCESS;
}
#endif

#if 1 //zxl 2021.08.30 处理粘包拆包问题(porting)
/**
 * 解析每一帧socket中粘包和拆包问题
 * 合成PKG数据包，当完全合成后调用parsePackage()解析PKG并发送数据
 */
static int parseSocket(int recvLen)
{
    int ret = PARSE_SOCKET_SUCESS;
    char *pbuffer = recvBuf;

    //std::cout << "parseSocket " <<std::dec << __LINE__ << " currPkgLen=" << mCurrPkgLen << " recvLen=" << recvLen << " totalLen=" << mTotalLen << std::endl;

    if (recvLen == 0) //TBD：test
    {
        return PARSE_SOCKET_NODATA;
    }
    else if (recvLen > sizeof(ASIM_MSG_HDR_t)) // 如果接收长度小于sizeof(ASIM_MSG_HDR_t) ，丢弃数据
    {
        //TBD：test
        if (mCurrPkgLen == 0)
        {
            const ASIM_MSG_HDR_t *const msgHead = reinterpret_cast<const ASIM_MSG_HDR_t *>((pbuffer )); //Msg的头部指针
            mTotalLen = msgHead->headerSize + msgHead->dataSize;
            mCurrPBuffer = (char *)malloc(mTotalLen);
            if (mCurrPBuffer == nullptr)
            {
                //std::cout << "parseSocket mCurrPBuffer mcalloc failed." << std::dec << __LINE__ << std::endl;
                return PARSE_SOCKET_ERROR;
            }
            else
            {
                memset(mCurrPBuffer, 0, mTotalLen);
            }
        }
    }
    else
    {
        //if (mCurrPkgLen > 0)   mCurrPBuffer 已有数据，不需要处理，下面会进行拼接，
        if (mCurrPkgLen == 0) // mCurrPBuffer 没有数据，此时mCurrPBuffer还没有分配空间，需要借助临时空间存储接收数据
        {
            memcpy(mTempBuff + mTempLen, pbuffer, recvLen);
            mTempLen += recvLen;

            if (mTempLen >= sizeof(ASIM_MSG_HDR_t)) // 接收到完整 ASIM_MSG_HDR_t数据，分配 mCurrPBuffer空间
            {
                const ASIM_MSG_HDR_t *const msgHead = reinterpret_cast<const ASIM_MSG_HDR_t *>((mTempBuff));
                mTotalLen = msgHead->headerSize + msgHead->dataSize;
                mCurrPBuffer = (char *)malloc(mTotalLen);
                if (mCurrPBuffer == nullptr)
                {
                    //std::cout << "parseSocket mCurrPBuffer mcalloc failed." << std::dec << __LINE__ << std::endl;
                    return PARSE_SOCKET_ERROR;
                }
                else
                {
                    memset(mCurrPBuffer, 0, mTotalLen);
                }
                memcpy(mCurrPBuffer, mTempBuff, mTempLen);
                memset(mTempBuff, 0, mTempLen);
                mCurrPkgLen = mTempLen;
                mTempLen = 0;
            }
            else // mCurrPBuffer 没有数据，mTempLen 也小于 sizeof(ASIM_MSG_HDR_t) ，不做处理
            {
                return PARSE_SOCKET_CURBUFFER_NODATA;
            }
        }
    }

    //std::cout << "parseSocket " << std::hex << (long)mCurrPBuffer << std::dec << " " << __LINE__ <<  " totalLen=" <<mTotalLen << std::endl;

    if ( mCurrPkgLen + recvLen < mTotalLen) // 缓存已有数据长度 + 本次接收数据长度 < 包数据长度，把接收数据接到缓存后面，不发送数据
    {
        memcpy(mCurrPBuffer + mCurrPkgLen, pbuffer, recvLen);

        //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

        mCurrPkgLen += recvLen;
        mIsMerge = true;
    }
    else if ( mCurrPkgLen + recvLen == mTotalLen) // 缓存已有数据长度 + 本次接收数据长度 = 包数据长度，把接收数据接到缓存后面，发送数据
    {
        memcpy(mCurrPBuffer + mCurrPkgLen, pbuffer, recvLen);

        //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

        //拼接好数据包的后续处理
        ret = parsePackage(mCurrPBuffer);
        if(ret != PARSE_PACKAGE_SUCESS)
        {
            return PARSE_SOCKET_ERROR;
        }

        //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

        mCurrPkgLen = 0;
        mTotalLen = 0;
        mIsMerge = false;
        if(mCurrPBuffer != nullptr)
        {
            free(mCurrPBuffer);
            mCurrPBuffer = nullptr;
        }
    }
    else // 缓存已有数据长度 + 本次接收数据长度 > 包数据长度
    {
        int recLeaveLen = recvLen;
        while (1)
        {
            // 首先拼完一个数据包先发送
            if (recLeaveLen > mTotalLen && mIsMerge == false)
            {
                memcpy(mCurrPBuffer, pbuffer + mCurrPkgLen, mTotalLen);
            }
            else
            {
                memcpy(mCurrPBuffer + mCurrPkgLen, pbuffer, mTotalLen - mCurrPkgLen);
            }

            //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

            //拼接好数据包的后续处理
            ret = parsePackage(mCurrPBuffer);
            if(ret != PARSE_PACKAGE_SUCESS)
            {
                return PARSE_SOCKET_ERROR;
            }

            //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

            if(mCurrPBuffer != nullptr)
            {
                free(mCurrPBuffer);
                mCurrPBuffer = nullptr;
            }
            mIsMerge = false;

            //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

            // 接下来计算 本次接收数据剩下部分大小
            if (recLeaveLen > mTotalLen)
            {
                recLeaveLen = recLeaveLen - mTotalLen;
                mCurrPkgLen += mTotalLen;
            }
            else
            {
                recLeaveLen = recLeaveLen - (mTotalLen - mCurrPkgLen);
                mCurrPkgLen = 0; // 为再次进入此循环准备，说明 recLeaveLen > totalLen， currPBuffer 还是空，所以 currPkgLen = 0
            }

            //std::cout << "parseSocket " << std::dec << __LINE__ << " recLeaveLen=" << recLeaveLen << " currPkgLen=" << mCurrPkgLen << std::endl;

            const ASIM_MSG_HDR_t *const msgHead = reinterpret_cast<const ASIM_MSG_HDR_t *>((pbuffer+ (recvLen - recLeaveLen)));
            mTotalLen = msgHead->headerSize + msgHead->dataSize;
            mCurrPBuffer = (char *)malloc(mTotalLen);
            if (mCurrPBuffer == nullptr)
            {
                //std::cout << "mCurrPBuffer mcalloc failed." << std::dec << __LINE__ << std::endl;
                return PARSE_SOCKET_ERROR;
            }
            else
            {
                 memset(mCurrPBuffer, 0, mTotalLen);
            }

            //std::cout << "parseSocket " << std::hex << mCurrPBuffer << std::dec << " " << __LINE__ << " currPkgLen=" << mCurrPkgLen << " totalLen=" << mTotalLen << std::endl;

            if (recLeaveLen < mTotalLen)
            {
                // currPBuffer指向 本次接收数据剩下部分
                memcpy(mCurrPBuffer, pbuffer + (recvLen - recLeaveLen), recLeaveLen);
                mCurrPkgLen = recLeaveLen;
                break;
            }
            else if ( recLeaveLen == mTotalLen ) // 本次接收数据剩下部分 正好是一个包大小，发送数据 ， 解析部分每次只解析一个包
            {
                memcpy(mCurrPBuffer, pbuffer + (recvLen - recLeaveLen), recLeaveLen);

                //拼接好数据包的后续处理
                ret = parsePackage(mCurrPBuffer);
                if(ret != PARSE_PACKAGE_SUCESS)
                {
                    return PARSE_SOCKET_ERROR;
                }

                //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

                if(mCurrPBuffer != nullptr)
                {
                    free(mCurrPBuffer);
                    mCurrPBuffer = nullptr;
                }
                mCurrPkgLen = 0;
                mTotalLen = 0;

                break;
            }
        }
    }

    //std::cout << "parseSocket end --- " <<std::dec << __LINE__ << std::endl;

    return PARSE_SOCKET_SUCESS;
}
#endif

void recvData()
{
    int ret = PARSE_SOCKET_SUCESS;
    int recvLen = 0;

    while (true)
    {
#if USE_UDP_OR_TCP // udp
        /*接收服务端的数据--recvfrom是无连接的,第5个参数可以获得数据发送者的地址*/
        if((recvLen = recvfrom(client_sockfd, recvBuf , RECV_BUF_SIZE , 0, (struct sockaddr *)&remote_addr, &sin_size)) < 0)//recvfrom()返回数据字节长度，若对方已经结束返回0,出错返回-1
        {
            perror("recvfrom error");
            return;
        }
        //printf("received packet from %s:\n", inet_ntoa(remote_addr.sin_addr));
#else // tcp
        /*接收服务端的数据 */
        if ((recvLen = recv(client_sockfd, recvBuf , RECV_BUF_SIZE , 0)) < 0)
        {
            perror("recv error");
            return;
        }
#endif

        //zxl 2021.08.30 AddFunc:parser msgPKG
        ret = parseSocket(recvLen);
        if(ret == PARSE_SOCKET_ERROR)
        {
            //清空数据
            memset(recvBuf, 0, RECV_BUF_SIZE);
            mTotalLen = 0;
            if(mCurrPBuffer != nullptr)
            {
                free(mCurrPBuffer);
                mCurrPBuffer = nullptr;
            }
            mCurrPkgLen = 0;
            memset(mTempBuff, 0, sizeof(ASIM_MSG_HDR_t) * 2);
            mTempLen = 0;

            return;
        }

#if 0 //zxl 2021.08.31 -> parsePackage()
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

        while (1)
        {
            ASIM_MSG_ENTRY_HDR_t *pkgHead = (ASIM_MSG_ENTRY_HDR_t *)currentPkg;//Pkg的头部指针
            if (pkgHead->pkgId == ASIM_PKG_ID_OBJECT_STATE) //解析ASIM_PKG_ID_OBJECT_STATE
            {
                //printf("receive ASIM_PKG_ID_OBJECT_STATE\n");
                ASIM_OBJECT_STATE_t *pkgData = (ASIM_OBJECT_STATE_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
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
                ASIM_VEHICLE_SYSTEMS_t *pkgData = (ASIM_VEHICLE_SYSTEMS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
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
                ASIM_ROAD_POS_t *pkgData = (ASIM_ROAD_POS_t *)(currentPkg + pkgHead->headerSize);//数据部分指针

                //1.解析数据
                int elementNum = pkgHead->dataSize / pkgHead->elementSize; //元素数量
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
                ASIM_SYNC_t *pkgData = (ASIM_SYNC_t *)(currentPkg + pkgHead->headerSize);//数据部分指针
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
                //printf("receive ASIM_PKG_ID_END_OF_FRAME\n");
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
#endif
    }
}

int main() {
    int sendLen;
    memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
    remote_addr.sin_family=AF_INET; //设置为IP通信
    remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//服务器IP地址
    remote_addr.sin_port=htons(8000); //服务器端口号

#if USE_UDP_OR_TCP // udp
    /*创建客户端套接字--IPv4协议，面向无连接通信，UDP协议*/
    if((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket error");
        return 1;
    }
#else // tcp
    /*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
    if ((client_sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket error");
        return 1;
    }

    /*连接服务器*/
    if (connect(client_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("connect error");
        return 1;
    }
#endif

    std::thread recv_thread(recvData);

    msgBuffer = (char *)malloc(msgBufferAllocSize);//一帧数据的buffer
    if (!msgBuffer)//失败
    {
        //std::cout << "Error: msgBuffer malloc fail" << std::endl;
        msgBufferAllocSize = 0;
        return 1;
    }

    // reset the information about the nearest and own object
    objData.frontVehId = 0; //前车Id
    objData.frontVehSpeedX = 0.0; //前车纵向速度
    objData.ownObjectSpeedX = 0.0; //主车纵向速度
    objData.ownObjectSpeedY = 0.0; //主车横向速度
    objData.relativeDist = 0.0; //与前车相对距离

    while (true)
    {
        //生成仿真应答数据
        generateMsg();

#if USE_UDP_OR_TCP // udp
        /*向服务器发送数据包*/
        if ((sendLen = sendto(client_sockfd, msgBuffer, msgBufferUsedSize, 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr))) < 0)//返回发送的数据长度，出错返回-1
        {
            perror("send error!");
            return 1;
        }
#else // tcp
        /*向服务器发送数据包*/
        if ((sendLen = send(client_sockfd, msgBuffer, msgBufferUsedSize, 0)) < 0)//返回发送的数据长度，出错返回-1
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

