#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include "SimProType.h"
#include <string.h>
#include <math.h>
#include <mutex>

#define USE_UDP_OR_TCP true                                                           // true:使用UDP false:使用TCP

char              *msgBuffer;                                                         //一帧数据的buffer
int                msgBufferAllocSize  = 1024 * 40;                                   //对应的已申请空间
int                msgBufferUsedSize   = 0;                                           //对应的已使用空间

int                client_sockfd;
struct sockaddr_in remote_addr;                                                       //服务器端网络地址结构体
unsigned int       sin_size            = sizeof(struct sockaddr_in);
#define RECV_BUF_SIZE 1024 * 1024 * 2
//#define RECV_BUF_SIZE 16                                                            //for testing
char              recvBuf[RECV_BUF_SIZE];                                             //接收数据的缓冲区

bool              bScenarioFinished    = true;                                        //当前测试场景是否结束场景
static const unsigned int scOwnId      = 1;                                           // ID of own vehicle

// globally store nearest object
typedef struct{
    S_SP_MIL_OBJECT_STATE mNearestObject;
    S_SP_MIL_EGO_STATE    mOwnObject;
    std::mutex            mMutex;                                                     //互斥量
}ObjData;
ObjData objData;

#if 1 //粘包拆包问题的处理
#define PARSE_PACKAGE_SUCESS            0
#define PARSE_PACKAGE_ERROR            -1

#define PARSE_SOCKET_SUCESS             0
#define PARSE_SOCKET_NODATA             1                                            // need receiving the next sockets
#define PARSE_SOCKET_CURBUFFER_NODATA   2                                            // need receiving the next sockets
#define PARSE_SOCKET_ERROR             -1
#endif

#if 1 //粘包拆包问题的处理
unsigned int  mTotalLen;                                                             //PKG总长
char*         mCurrPBuffer;                                                          //当前拼接PKG的buff
unsigned int  mCurrPkgLen;
char          mTempBuff[sizeof(S_SP_MSG_HDR) * 2];                                   //存放PKG的head的一部分
unsigned int  mTempLen;
bool          mIsMerge;                                                              //flag
#endif

/**
 * 测试场景限制：
 * 场景中只能有主车和一个交通车两个对象 (缺乏处理多个障碍物的能力)
 * 两车必须在同一条路上 (pkgBody->sObjectState.sPos.u8X作为道路坐标系s坐标，用于计算相对距离)
 * 沿s轴正方向行驶
 * 主车在交通车后面
 * 不能进行转向 (缺乏转向功能)
 */
double computeAcc()
{
    S_SP_MIL_OBJECT_STATE   mNearestObject{0};
    S_SP_MIL_EGO_STATE      mOwnObject{0};

    objData.mMutex.lock();
    mOwnObject            = objData.mOwnObject;
    mNearestObject        = objData.mNearestObject;
    objData.mMutex.unlock();

    // do we have a valid nearest object?
    bool haveSensorObject = ( mNearestObject.sObjectState.u4Id > 0 );               // sensor object must not be older than 1.0s

    double ownSpeed       = sqrt( mOwnObject.sObjectState.sSpeed.u8X * mOwnObject.sObjectState.sSpeed.u8X + mOwnObject.sObjectState.sSpeed.u8Y * mOwnObject.sObjectState.sSpeed.u8Y );

    double accelTgtDist   = 0.0;
    double accelTgtSpeed  = ( 30.0 - ownSpeed ) / 5.0;                              // default speed should be own preferred speed

    if ( haveSensorObject )
    {
        // 计算相对速度
        double relativeSpeed = mNearestObject.sObjectState.sSpeed.u8X - mOwnObject.sObjectState.sSpeed.u8X;

        // let's go for the same speed as preceding vehicle:
        if ( relativeSpeed < -1.0e-3 )
        {
            accelTgtSpeed  = 2.0 * relativeSpeed / 5.0;
        }
        else
        {
            accelTgtSpeed  = 0.0;
        }

        // let's go for a 2s distance
        double tgtDist      = ownSpeed * 2.0;                                       //与前车保持的距离

        if ( tgtDist < 10.0 )                                                       // minimum  distance to keep
            tgtDist  = 10.0;

        // 计算相对距离
        double relativeDist = mNearestObject.sObjectState.u4RoadS - mOwnObject.sObjectState.u4RoadS;

        accelTgtDist        =  ( relativeDist - tgtDist ) / 10.0;
    }

    float accelTgt          = accelTgtDist + accelTgtSpeed;
    // std::cout << "accelTgt=" << accelTgt << std::endl;

    return accelTgt;
}


/**
 * 非控制在环，世界坐标系，需要提供准确数值的数据项：
 * pkgBody->sObjectState.sPos.u8X
 * pkgBody->sObjectState.sPos.u8Y
 * pkgBody->sObjectState.sPos.u8Z
 * pkgBody->sObjectState.sPos.u4H
 * pkgBody->sObjectState.sSpeed.u8X
 * pkgBody->sObjectState.sSpeed.u8Y
 * pkgBody->sObjectState.sSpeed.u4H
 * pkgBody->sObjectState.sAccel.u8X
 * pkgBody->sObjectState.sAccel.u8Y
 * pkgBody->sObjectState.sAccel.u4H
 * pkgBody->sObjectState.u4TraveledDist
 * pkgBody->sObjectState.u8RoadId
 * pkgBody->sObjectState.sPos.u1Type = D_SP_COORDINATE_TYPE_GEO;
 *
 * 非控制在环，道路坐标系，需要提供准确数值的数据项：
 * pkgBody->sObjectState.u8RoadId
 * pkgBody->sObjectState.u1LaneId
 * pkgBody->sObjectState.u4RoadS
 * pkgBody->sObjectState.u4RoadT
 * pkgBody->sObjectState.u4HdgRel
 * pkgBody->sObjectState.u1Dir
 * pkgBody->sObjectState.sSpeed.u8X
 * pkgBody->sObjectState.sSpeed.u8Y
 * pkgBody->sObjectState.sSpeed.u4H
 * pkgBody->sObjectState.sAccel.u8X
 * pkgBody->sObjectState.sAccel.u8Y
 * pkgBody->sObjectState.sAccel.u4H
 * pkgBody->sObjectState.u4TraveledDist
 * pkgBody->sObjectState.base.pos.type = D_SP_COORDINATE_TYPE_TRACK;
 */
void generatePkgEgoData1()
{
    //生成S_SP_MIL_EGO_STATE
    S_SP_MSG_ENTRY_HDR *pkghead          = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->u4HeaderSize                = sizeof(S_SP_MSG_ENTRY_HDR);
    pkghead->u4DataSize                  = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u4ElementSize               = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u2PkgId                     = D_SP_MIL_PKG_ID_EGO_DATA;

    //填充PKG body
    S_SP_MIL_EGO_STATE *pkgBody          = (S_SP_MIL_EGO_STATE *)(pkghead + 1);

    //线速度与角速度
    pkgBody->sObjectState.sSpeed.u8X     = 0.0;                                               //Ego->getDu();
    pkgBody->sObjectState.sSpeed.u8Y     = 0.0;                                               //Ego->getDv();
    pkgBody->sObjectState.sSpeed.u8Z     = 0.0;
    pkgBody->sObjectState.sSpeed.u4H     = 0.0;                                               //Ego->getDYaw();//航向角的角速度
    pkgBody->sObjectState.sSpeed.u4P     = 0.0;
    pkgBody->sObjectState.sSpeed.u4R     = 0.0;
    pkgBody->sObjectState.sSpeed.u1Type  = D_SP_COORDINATE_TYPE_TRACK;

    //线加速度与角加速度
    pkgBody->sObjectState.sAccel.u8X     = 0.0;
    pkgBody->sObjectState.sAccel.u8Y     = 0.0;
    pkgBody->sObjectState.sAccel.u8Z     = 0.0;
    pkgBody->sObjectState.sAccel.u4H     = 0.0;
    pkgBody->sObjectState.sAccel.u4P     = 0.0;
    pkgBody->sObjectState.sAccel.u4R     = 0.0;
    pkgBody->sObjectState.sAccel.u1Type  = D_SP_COORDINATE_TYPE_TRACK;

    //
    pkgBody->sObjectState.sGeo.u4DimX    = 0.0;
    pkgBody->sObjectState.sGeo.u4DimY    = 0.0;
    pkgBody->sObjectState.sGeo.u4DimZ    = 0.0;
    pkgBody->sObjectState.sGeo.u4OffX    = 0.0;
    pkgBody->sObjectState.sGeo.u4OffY    = 0.0;
    pkgBody->sObjectState.sGeo.u4OffZ    = 0.0;

    // 世界坐标
    pkgBody->sObjectState.sPos.u8X       = -2110;
    pkgBody->sObjectState.sPos.u8Y       = -5296;
    pkgBody->sObjectState.sPos.u8Z       = 12;
    pkgBody->sObjectState.sPos.u4H       = 1.6;
    pkgBody->sObjectState.sPos.u4P       = 0.0;
    pkgBody->sObjectState.sPos.u4R       = 0.0;
    pkgBody->sObjectState.sPos.u1Type    = D_SP_COORDINATE_TYPE_GEO;

   
#if 1 // 转向灯
    pkgBody->u4LightMask                 = 0;
     // 刹车灯亮
    if (1)//如果刹车灯亮
    {
        pkgBody->u4LightMask             = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_REAR_BRAKE;
    }

    if (1)//如果左转向灯亮
    {
        pkgBody->u4LightMask             = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_L;
    }

    if (1)//如果右转向灯亮
    {
        pkgBody->u4LightMask             = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_R;
    }
#endif
    // pkgBody->u4WheelSpeedFL           = ;
    // pkgBody->u4WheelSpeedFR           = ;
    // pkgBody->u4WheelSpeedRL           = ;
    // pkgBody->u4WheelSpeedRR           = ;
    // pkgBody->u4MasterCylinderPressure = ;

    msgBufferUsedSize                   += pkghead->u4HeaderSize + pkghead->u4DataSize;               //更新msgBuffer的已使用空间
}


/**
 * 控制在环(动力学模型挂载外部)，需要提供准确数值的数据项：
 * pkgBody->sObjectState.sSpeed.u4H
 * pkgBody->sObjectState.sAccel.u8X
 */
void generatePkgEgoData2()
{
    double             accelTgt = computeAcc();

    //生成D_SP_MIL_PKG_ID_EGO_DATA
    S_SP_MSG_ENTRY_HDR *pkghead = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
    pkghead->u4DataSize         = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u4ElementSize      = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u2PkgId            = D_SP_MIL_PKG_ID_EGO_DATA;

    //填充PKG body
    S_SP_MIL_EGO_STATE *pkgBody = (S_SP_MIL_EGO_STATE *)(pkghead + 1);

    pkgBody->sObjectState.u4Id  = 1;                                                                     //主车Id为1
    strcpy(pkgBody->sObjectState.au1Name, "Ego");

    //线速度与角速度
    pkgBody->sObjectState.sSpeed.u4H     = 0.0;
    pkgBody->sObjectState.sSpeed.u1Type  = D_SP_COORDINATE_TYPE_TRACK;                                   //坐标系类型,道路坐标系(x=s, y=t )

    //线加速度与角加速度
    pkgBody->sObjectState.sAccel.u8X     = accelTgt;
    pkgBody->sObjectState.sAccel.u1Type  = D_SP_COORDINATE_TYPE_TRACK;                                   //坐标系类型，道路坐标系(x=s, y=t )

    //转向灯
    pkgBody->u4LightMask     = 0;
    if (1)                                                                                               //如果刹车灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_REAR_BRAKE;
    }
    if (1)                                                                                               //如果左转向灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_L;
    }
    if (1)                                                                                               //如果右转向灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_R;
    }

    msgBufferUsedSize       += pkghead->u4HeaderSize + pkghead->u4DataSize;                              //更新msgBuffer的已使用空间
}

/**
 * 控制在环(动力学模型挂载内部)，需要提供准确数值的数据项：
 * 使用第一套动力学模型:
 * pkgBody->u4AccelTgt
 * pkgBody->u4SteeringWheel
 * 
 * 使用第二套动力学模型:
 * pkgBody->u4SteeringWheel
 * pkgBody->u4ThrottlePedal
 * pkgBody->u8MasterCylinderPressure
 */

void generatePkgDriverCtrl()
{
    double             accelTgt = computeAcc();
    S_SP_MSG_ENTRY_HDR *pkghead = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
    pkghead->u4DataSize         = sizeof(S_SP_DRIVER_CTRL);
    pkghead->u4ElementSize      = sizeof(S_SP_DRIVER_CTRL);
    pkghead->u2PkgId            = D_SP_PKG_ID_DRIVER_CTRL;

    //填充PKG body
    S_SP_DRIVER_CTRL *pkgBody   = (S_SP_DRIVER_CTRL *)(pkghead + 1);

#if 1                                                                                          // 使用第一套动力学模型
    pkgBody->u4AccelTgt         = accelTgt;                                                         //预期目标加速度(m/s2)
    pkgBody->u4SteeringWheel    = 1.0;                                                         //方向盘转角(弧度)
    std::cout << " acc=" << pkgBody->u4AccelTgt << " u4SteeringWheel=" << pkgBody->u4SteeringWheel << std::endl;
#else                                                                                          // 使用第二套动力学模型
    pkgBody->u4SteeringWheel          = 1.0;                                                   // 方向盘转角(弧度)
    pkgBody->u4ThrottlePedal          = 0.5;                                                   // 油门踏板(0~1)
    pkgBody->u8MasterCylinderPressure = 6;                                                     //制动主缸压力(mpa)
    std::cout << " u4SteeringWheel=" << pkgBody->u4SteeringWheel << " u4ThrottlePedal=" << pkgBody->u4ThrottlePedal << " u8MasterCylinderPressure=" << pkgBody->u8MasterCylinderPressure << std::endl;
#endif

    msgBufferUsedSize += pkghead->u4HeaderSize + pkghead->u4DataSize;                          //更新msgBuffer的已使用空间
}

void generatePkgEgoData()
{
    S_SP_MSG_ENTRY_HDR *pkghead = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkghead->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
    pkghead->u4DataSize         = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u4ElementSize      = sizeof(S_SP_MIL_EGO_STATE);
    pkghead->u2PkgId            = D_SP_MIL_PKG_ID_EGO_DATA;

    //填充PKG body
    S_SP_MIL_EGO_STATE *pkgBody = (S_SP_MIL_EGO_STATE *)(pkghead + 1);

    pkgBody->sObjectState.u4Id  = 1;                                                           //主车Id为1
    strcpy(pkgBody->sObjectState.au1Name, "Ego");

    pkgBody->u4LightMask                = 0;
    if (1)                                                                                     //如果刹车灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_REAR_BRAKE;
    }
    if (1)                                                                                     //如果左转向灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_L;
    }
    if (1)                                                                                     //如果右转向灯亮
    {
        pkgBody->u4LightMask = pkgBody->u4LightMask | D_SP_VEHICLE_LIGHT_INDICATOR_R;
    }

    msgBufferUsedSize       += pkghead->u4HeaderSize + pkghead->u4DataSize;                    //更新msgBuffer的已使用空间
    
}

void generateMsg()
{
    //清空msgBuffer
    memset(msgBuffer, 0, msgBufferAllocSize);
    msgBufferUsedSize     = 0;                                                                 //更新msgBuffer的已使用空间

    //生成Msg头部
    S_SP_MSG_HDR *msgHead = (S_SP_MSG_HDR *) msgBuffer;

    //填充Msg头部
    msgHead->u8SimTime    = 1.2;                                                               //仿真时间
    msgHead->u4HeaderSize = sizeof(S_SP_MSG_HDR);                                              //Msg头部大小
    msgHead->u4FrameNo    = 1;                                                                 //帧号

    msgBufferUsedSize    += sizeof(S_SP_MSG_HDR);                                              //更新msgBuffer的已使用空间

    //生成D_SP_PKG_ID_START_FRAME
    S_SP_MSG_ENTRY_HDR *pkgHead = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkgHead->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
    pkgHead->u4DataSize         = 0;
    pkgHead->u4ElementSize      = 0;
    pkgHead->u2PkgId            = D_SP_PKG_ID_START_FRAME;

    msgBufferUsedSize          += pkgHead->u4HeaderSize + pkgHead->u4DataSize;                 //更新msgBuffer的已使用空间

    if (bScenarioFinished)                                                                     //如果当前测试场景结束，发送trigger
    {
        //生成D_SP_PKG_ID_SYNC
        S_SP_MSG_ENTRY_HDR *pkgTrigger = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

        //填充PKG头部
        pkgTrigger->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
        pkgTrigger->u4DataSize         = sizeof(S_SP_SYNC);
        pkgTrigger->u4ElementSize      = sizeof(S_SP_SYNC);
        pkgTrigger->u2PkgId            = D_SP_PKG_ID_SYNC;
        
        //填充PKG的body
        S_SP_SYNC *syncTrigger         = (S_SP_SYNC *)(pkgTrigger + 1);
        syncTrigger->u4CmdMask         = D_SP_SYNC_CMD_TRIGGER;

        msgBufferUsedSize              += pkgTrigger->u4HeaderSize + pkgTrigger->u4DataSize;     //更新msgBuffer的已使用空间

        bScenarioFinished              = false;
    }
    else //发送其他pkg
    {
#if 0   
        //非控制在环
        generatePkgEgoData1();
#elif 1
        //控制在环(动力学模型挂载外部)
        generatePkgEgoData2();
#else
        //控制在环(动力学模型挂载内部)
        generatePkgDriverCtrl();
        generatePkgEgoData();
#endif
    }

    //生成D_SP_PKG_ID_END_FRAME
    S_SP_MSG_ENTRY_HDR* pkgEnd = (S_SP_MSG_ENTRY_HDR *)(msgBuffer + msgBufferUsedSize);

    //填充PKG头部
    pkgEnd->u4HeaderSize       = sizeof(S_SP_MSG_ENTRY_HDR);
    pkgEnd->u4DataSize         = 0;
    pkgEnd->u4ElementSize      = 0;
    pkgEnd->u2PkgId            = D_SP_PKG_ID_END_FRAME;

    msgBufferUsedSize         += pkgEnd->u4HeaderSize + pkgEnd->u4DataSize;                 //更新msgBuffer的已使用空间

    msgHead->u4DataSize        = msgBufferUsedSize - msgHead->u4HeaderSize;                 //Msg数据部分大小
}

#if 1 //解析数据包
/**
 * 对parseSocket()中解析完socket后所生成的PKG的处理
 * pkgId的判断：D_SP_MIL_PKG_ID_EGO_DATA、D_SP_MIL_PKG_ID_OBJECT_DATA、D_SP_PKG_ID_SYNC、D_SP_PKG_ID_END_FRAME
 */
static int parsePackage(char *pkgBuff)
{
    if(nullptr == pkgBuff)
    {
        return PARSE_PACKAGE_ERROR;
    }

    //std::cout << "parsePackage  start" << std::dec << __LINE__ << std::endl;

    //解析数据
    S_SP_MSG_HDR *msgHead    = (S_SP_MSG_HDR *)pkgBuff;                                                     //Msg的头部指针
    //std::cout << "headerSize=" << msgHead->headerSize << " dataSize=" << msgHead->dataSize << std::endl;
    char         *currentPkg = pkgBuff + msgHead->u4HeaderSize;                                             //当前Pkg的头部指针

    //第一帧为D_SP_PKG_ID_START_FRAME
    S_SP_MSG_ENTRY_HDR *startPkgHead = (S_SP_MSG_ENTRY_HDR *)currentPkg;
    if (startPkgHead->u2PkgId != D_SP_PKG_ID_START_FRAME)
    {
        return PARSE_PACKAGE_ERROR;
    }

    //std::cout << "parsePackage  " << std::dec << __LINE__ << std::endl;

    //printf("receiveD_SP_PKG_ID_START_FRAME\n");
    currentPkg += startPkgHead->u4HeaderSize + startPkgHead->u4DataSize;                                    //指向下一个pkg

    //AD端内部自定义数据结构
    S_SP_MIL_OBJECT_STATE mNearestObject{0};
    S_SP_MIL_EGO_STATE    mOwnObject{0};

    while (1)
    {
        S_SP_MSG_ENTRY_HDR *pkgHead = (S_SP_MSG_ENTRY_HDR *)currentPkg;                                      //Pkg的头部指针
        if (pkgHead->u2PkgId == D_SP_MIL_PKG_ID_EGO_DATA)                                                    //S_SP_MIL_EGO_STATE
        {
            //printf("receive D_SP_MIL_PKG_ID_EGO_DATA\n");
            S_SP_MIL_EGO_STATE *pkgData = (S_SP_MIL_EGO_STATE *)(currentPkg + pkgHead->u4HeaderSize);        //数据部分指针

            //1.解析数据
            int elementNum = pkgHead->u4DataSize / pkgHead->u4ElementSize;                                   //元素数量
            for (int i = 0; i < elementNum; i++)                                                             //解析每个元素
            {
                memcpy( &mOwnObject, pkgData, sizeof( S_SP_MIL_EGO_STATE ) );
                pkgData += 1;
            }

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->u2PkgId == D_SP_MIL_PKG_ID_OBJECT_DATA)                                            //S_SP_MIL_OBJECT_STATE
        {
            //printf("receive D_SP_MIL_PKG_ID_OBJECT_DATA\n");
            S_SP_MIL_OBJECT_STATE *pkgData = (S_SP_MIL_OBJECT_STATE *)(currentPkg + pkgHead->u4HeaderSize);  //数据部分指针

            //1.解析数据
            int elementNum = pkgHead->u4DataSize / pkgHead->u4ElementSize;                                   //元素数量
            for (int i = 0; i < elementNum; i++)                                                             //解析每个元素
            {
                memcpy( &mNearestObject, pkgData, sizeof( S_SP_MIL_OBJECT_STATE ) );
                pkgData += 1;
            }

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->u2PkgId == D_SP_PKG_ID_SYNC)
        {
            //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //printf("receive S_SP_SYNC\n");
            S_SP_SYNC *pkgData = (S_SP_SYNC *)(currentPkg + pkgHead->u4HeaderSize);                        //数据部分指针
            //1.解析数据
            if (pkgData->u4CmdMask & D_SP_SYNC_CMD_FINISH_CURRENT)                                         //最低位为1代表当前测试场景结束
            {
                bScenarioFinished  = true;                                                                 //收到仿真器发的结束信号
                //std::cout << "FinishSync" << std::endl;
            }

             //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //2.AD端内部处理
            //AD TODO
        }
        else if (pkgHead->u2PkgId == D_SP_PKG_ID_END_FRAME)                                              //如果是最后一个Pkg
        {
             //std::cout << "parsePackage   while(1)  " << std::dec << __LINE__ << std::endl;

            //printf("receive D_SP_PKG_ID_END_FRAME\n");
            break;
        }
        currentPkg += pkgHead->u4HeaderSize + pkgHead->u4DataSize;                                       //指向下一个pkg
    }

    //更新数据到objData
    objData.mMutex.lock();
    objData.mOwnObject     = mOwnObject;
    objData.mNearestObject = mNearestObject;
    objData.mMutex.unlock();

    //std::cout << "parsePackage   end  " << std::dec << __LINE__ << std::endl;

    return PARSE_PACKAGE_SUCESS;
}
#endif

#if 1 //处理粘包拆包问题(porting)
/**
 * 解析每一帧socket中粘包和拆包问题
 * 合成PKG数据包，当完全合成后调用parsePackage()解析PKG并发送数据
 */
static int parseSocket(int recvLen)
{
    int   ret     = PARSE_SOCKET_SUCESS;
    char *pbuffer = recvBuf;

    //std::cout << "parseSocket " <<std::dec << __LINE__ << " currPkgLen=" << mCurrPkgLen << " recvLen=" << recvLen << " totalLen=" << mTotalLen << std::endl;

    if (recvLen == 0)                                                                                    //TBD：test
    {
        return PARSE_SOCKET_NODATA;
    }
    else if (recvLen > sizeof(S_SP_MSG_HDR))                                                             // 如果接收长度大于 Msg Head
    {
        //TBD：test
        if (mCurrPkgLen == 0)
        {
            const S_SP_MSG_HDR *const msgHead = reinterpret_cast<const S_SP_MSG_HDR *>((pbuffer ));      //Msg的头部指针
            mTotalLen          = msgHead->u4HeaderSize + msgHead->u4DataSize;
            mCurrPBuffer       = (char *)malloc(mTotalLen);
            if (mCurrPBuffer  == nullptr)
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
        if (mCurrPkgLen == 0)                                                                           // mCurrPBuffer 没有数据，此时mCurrPBuffer还没有分配空间，需要借助临时空间存储接收数据
        {
            memcpy(mTempBuff + mTempLen, pbuffer, recvLen);
            mTempLen += recvLen;

            if (mTempLen >= sizeof(S_SP_MSG_HDR))                                                       // 接收到完整 S_SP_MSG_HDR数据，分配 mCurrPBuffer空间
            {
                const S_SP_MSG_HDR *const msgHead = reinterpret_cast<const S_SP_MSG_HDR *>((mTempBuff));
                mTotalLen          = msgHead->u4HeaderSize + msgHead->u4DataSize;
                mCurrPBuffer       = (char *)malloc(mTotalLen);
                if (mCurrPBuffer  == nullptr)
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
                mCurrPkgLen     = mTempLen;
                mTempLen        = 0;
            }
            else                                                                                        // mCurrPBuffer 没有数据，mTempLen 也小于 sizeof(S_SP_MSG_HDR) ，不做处理
            {
                return PARSE_SOCKET_CURBUFFER_NODATA;
            }
        }
    }

    //std::cout << "parseSocket " << std::hex << (long)mCurrPBuffer << std::dec << " " << __LINE__ <<  " totalLen=" <<mTotalLen << std::endl;

    if ( mCurrPkgLen + recvLen < mTotalLen)                                                             // 缓存已有数据长度 + 本次接收数据长度 < 包数据长度，把接收数据接到缓存后面，不发送数据
    {
        memcpy(mCurrPBuffer + mCurrPkgLen, pbuffer, recvLen);

        //std::cout << "parseSocket " << std::dec << __LINE__ << std::endl;

        mCurrPkgLen += recvLen;
        mIsMerge     = true;
    }
    else if ( mCurrPkgLen + recvLen == mTotalLen)                                                        // 缓存已有数据长度 + 本次接收数据长度 = 包数据长度，把接收数据接到缓存后面，发送数据
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

        mCurrPkgLen       = 0;
        mTotalLen         = 0;
        mIsMerge          = false;
        if(mCurrPBuffer  != nullptr)
        {
            free(mCurrPBuffer);
            mCurrPBuffer  = nullptr;
        }
    }
    else // 缓存已有数据长度 + 本次接收数据长度 > 包数据长度
    {
        int recLeaveLen   = recvLen;
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
            if (recLeaveLen  >  mTotalLen)
            {
                recLeaveLen  = recLeaveLen - mTotalLen;
                mCurrPkgLen += mTotalLen;
            }
            else
            {
                recLeaveLen  = recLeaveLen - (mTotalLen - mCurrPkgLen);
                mCurrPkgLen  = 0;                                                                                           // 为再次进入此循环准备，说明 recLeaveLen > totalLen， currPBuffer 还是空，所以 currPkgLen = 0
            }

            //std::cout << "parseSocket " << std::dec << __LINE__ << " recLeaveLen=" << recLeaveLen << " currPkgLen=" << mCurrPkgLen << std::endl;

            const S_SP_MSG_HDR *const msgHead = reinterpret_cast<const S_SP_MSG_HDR *>((pbuffer+ (recvLen - recLeaveLen)));
            mTotalLen                         = msgHead->u4HeaderSize + msgHead->u4DataSize;
            mCurrPBuffer                      = (char *)malloc(mTotalLen);
            if (mCurrPBuffer  ==  nullptr)
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
            else if ( recLeaveLen == mTotalLen )                                                                       // 本次接收数据剩下部分 正好是一个包大小，发送数据 ， 解析部分每次只解析一个包
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
                mCurrPkgLen      = 0;
                mTotalLen        = 0;

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
    int ret     = PARSE_SOCKET_SUCESS;
    int recvLen = 0;

    while (true)
    {
#if USE_UDP_OR_TCP                                                                                                            // udp
        /*接收服务端的数据--recvfrom是无连接的,第5个参数可以获得数据发送者的地址*/
        if((recvLen = recvfrom(client_sockfd, recvBuf , RECV_BUF_SIZE , 0, (struct sockaddr *)&remote_addr, &sin_size)) < 0)  //recvfrom()返回数据字节长度，若对方已经结束返回0,出错返回-1
        {
            perror("recvfrom error");
            return;
        }
        //printf("received packet from %s:\n", inet_ntoa(remote_addr.sin_addr));
#else                                                                                                                         // tcp
        /*接收服务端的数据 */
        if ((recvLen = recv(client_sockfd, recvBuf , RECV_BUF_SIZE , 0)) < 0)
        {
            perror("recv error");
            return;
        }
#endif

        //AddFunc:parser msgPKG
        ret     = parseSocket(recvLen);
        if(ret == PARSE_SOCKET_ERROR)
        {
            //清空数据
            memset(recvBuf, 0, RECV_BUF_SIZE);
            mTotalLen     = 0;
            if(mCurrPBuffer != nullptr)
            {
                free(mCurrPBuffer);
                mCurrPBuffer = nullptr;
            }
            mCurrPkgLen     = 0;
            memset(mTempBuff, 0, sizeof(S_SP_MSG_HDR) * 2);
            mTempLen        = 0;

            return;
        }
    }
}

int main() {
    int sendLen;
    memset(&remote_addr,0,sizeof(remote_addr));                                                                           //数据初始化--清零
    remote_addr.sin_family       =AF_INET;                                                                                //设置为IP通信
    remote_addr.sin_addr.s_addr  =inet_addr("127.0.0.1");                                                                 //服务器IP地址
    remote_addr.sin_port         =htons(8000);                                                                            //服务器端口号

#if USE_UDP_OR_TCP                                                                                                        // udp
    /*创建客户端套接字--IPv4协议，面向无连接通信，UDP协议*/
    if((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket error");
        return 1;
    }
#else                                                                                                                    // tcp
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

    msgBuffer = (char *)malloc(msgBufferAllocSize);                                                                     //一帧数据的buffer
    if (!msgBuffer)                                                                                                     //失败
    {
        //std::cout << "Error: msgBuffer malloc fail" << std::endl;
        msgBufferAllocSize = 0;
        return 1;
    }

    // reset the information about the nearest and own object
    memset( &(objData.mNearestObject), 0, sizeof( S_SP_MIL_OBJECT_STATE ) );
    memset( &(objData.mOwnObject), 0, sizeof( S_SP_MIL_EGO_STATE ) );

    while (true)
    {
        //生成仿真应答数据
        generateMsg();

#if USE_UDP_OR_TCP                                                                                                                              // udp
        /*向服务器发送数据包*/
        if ((sendLen = sendto(client_sockfd, msgBuffer, msgBufferUsedSize, 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr))) < 0)   //返回发送的数据长度，出错返回-1
        {
            perror("send error!");
            return 1;
        }
#else                                                                                                                                             // tcp
        /*向服务器发送数据包*/
        if ((sendLen = send(client_sockfd, msgBuffer, msgBufferUsedSize, 0)) < 0)                                                                 //返回发送的数据长度，出错返回-1
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

