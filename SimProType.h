#ifndef SP_COMMUNICATION_TYPE_H
#define SP_COMMUNICATION_TYPE_H
#include <stdint.h>

#pragma pack(4) //指定默认对齐数

#define D_SP_TRAFFIC_SIGN_TYPE_MAX_SPEED_LIMIT                  "1010203800001413"    /** 最高限速标志 */
#define D_SP_TRAFFIC_SIGN_TYPE_NO_ENTRY                         "1010200500001513"    /** 禁止驶入 */
#define D_SP_TRAFFIC_SIGN_TYPE_No_PEDESTRIAN                    "1010202100001413"    /** 禁止行人 */
#define D_SP_TRAFFIC_SIGN_TYPE_No_RIGHT_TURN                    "1010202311001413"    /** 禁止右转 */
#define D_SP_TRAFFIC_SIGN_TYPE_No_STRAIGHT                      "1010202400001413"    /** 禁止直行 */
#define D_SP_TRAFFIC_SIGN_TYPE_No_LIFT_TURN                     "1010202211001413"    /** 禁止左转 */
#define D_SP_TRAFFIC_SIGN_TYPE_STOP                             "1010200100001914"    /** 停止 */  
#define D_SP_TRAFFIC_SIGN_TYPE_YIELD                            "1010200200002012"    /** 让行 */
#define D_SP_TRAFFIC_SIGN_TYPE_ATTENTION                        "1010103400001111"    /** 注意 */
#define D_SP_TRAFFIC_SIGN_TYPE_PAY_ATTENTION_TO_PEDESTRIAN      "1010101000001111"    /** 注意行人 */
#define D_SP_TRAFFIC_SIGN_TYPE_CROSSWALK                        "1010301800002616"    /** 人行横道 */
#define D_SP_TRAFFIC_SIGN_TYPE_PAVEMENT_MARKER_CROSSWALK_LINE   "RoadSign_Sidewalk"   /** 路面标志, 人行横道线 */
#define D_SP_TRAFFIC_SIGN_TYPE_PAVEMENT_MARKER_STOP_LINE        "RoadSign_Stop"       /** 路面标志, 停止线 */

#define D_SP_TRAFFIC_SIGN_SUBTYPE_MAX_SPEED_LIMIT_30               30    /** 最高限速30标志 */
#define D_SP_TRAFFIC_SIGN_SUBTYPE_MAX_SPEED_LIMIT_40               40    /** 最高限速40标志 */
#define D_SP_TRAFFIC_SIGN_SUBTYPE_MAX_SPEED_LIMIT_60               60    /** 最高限速60标志 */
#define D_SP_TRAFFIC_SIGN_SUBTYPE_MAX_SPEED_LIMIT_80               80    /** 最高限速80标志 */

#define D_SP_SIZE_OBJECT_NAME       32

#define D_SP_PKG_ID_START_FRAME                  1
#define D_SP_PKG_ID_END_FRAME                    2
#define D_SP_PKG_ID_CONTACT_POINT                3
#define D_SP_PKG_ID_ROAD_QUERY                   4
#define D_SP_PKG_ID_LANE_INFO                    5
#define D_SP_PKG_ID_SENSOR_INFO                  6
#define D_SP_PKG_ID_SENSOR_DETECTION_INFO        7
#define D_SP_PKG_ID_ENVIRONMENT                  8
#define D_SP_PKG_ID_ROAD_STATE                   9
#define D_SP_PKG_ID_DRIVER_CTRL                 10
#define D_SP_PKG_ID_TRAFFIC_LIGHT               11
#define D_SP_PKG_ID_TRAFFIC_SIGN                12
#define D_SP_PKG_ID_SYNC                        13
#define D_SP_PKG_ID_REQUEST_AD_DATA             14
#define D_SP_MIL_PKG_ID_EGO_DATA                15
#define D_SP_MIL_PKG_ID_OBJECT_DATA             16
#define D_SP_MIL_PKG_ID_ROADMARK                17
#define D_SP_PKG_ID_INIT_PARAM                  18


#define D_SP_OBJECT_TYPE_NONE                   0
#define D_SP_OBJECT_TYPE_CAR                    1
#define D_SP_OBJECT_TYPE_PEDESTRIAN             2
#define D_SP_OBJECT_TYPE_BARRIER                3
#define D_SP_OBJECT_TYPE_STREET_LAMP            4
#define D_SP_OBJECT_TYPE_TRAFFIC_SIGN           5
#define D_SP_OBJECT_TYPE_LANE                   6
#define D_SP_OBJECT_TYPE_ROADMARK               7


#define D_SP_GEAR_BOX_POS_AUTO             0
#define D_SP_GEAR_BOX_POS_P                1
#define D_SP_GEAR_BOX_POS_R                2
#define D_SP_GEAR_BOX_POS_N                3
#define D_SP_GEAR_BOX_POS_D                4
#define D_SP_GEAR_BOX_POS_1                5
#define D_SP_GEAR_BOX_POS_2                6
#define D_SP_GEAR_BOX_POS_3                7
#define D_SP_GEAR_BOX_POS_4                8
#define D_SP_GEAR_BOX_POS_5                9
#define D_SP_GEAR_BOX_POS_6               10
#define D_SP_GEAR_BOX_POS_7               11
#define D_SP_GEAR_BOX_POS_8               12


#define D_SP_SENSOR_TYPE_NONE            0
#define D_SP_SENSOR_TYPE_RADAR           1
#define D_SP_SENSOR_TYPE_CAMERA          2
#define D_SP_SENSOR_TYPE_LIDAR           3
#define D_SP_SENSOR_TYPE_ULTRASONIC      4
#define D_SP_SENSOR_TYPE_GPS             5
#define D_SP_SENSOR_TYPE_IMU             6

#define D_SP_TRLIGHT_STATUS_OFF           0
#define D_SP_TRLIGHT_STATUS_STOP          1
#define D_SP_TRLIGHT_STATUS_ATTN          2
#define D_SP_TRLIGHT_STATUS_GO            3


#define D_SP_COORDINATE_TYPE_GEO              0
#define D_SP_COORDINATE_TYPE_TRACK            1


#define D_SP_ENV_CLOUD_STATE_OFF         0
#define D_SP_ENV_CLOUD_STATE_RAINY       1
#define D_SP_ENV_CLOUD_STATE_OVERCAST    2
#define D_SP_ENV_CLOUD_STATE_CLOUDY      3
#define D_SP_ENV_CLOUD_STATE_BLUE        4


#define D_SP_ROADMARK_TYPE_UNDECIDED                0      /**< 未定义 */
#define D_SP_ROADMARK_TYPE_SOLID                    1      /**< 实线   */
#define D_SP_ROADMARK_TYPE_BROKEN                   2      /**< 虚线   */
#define D_SP_ROADMARK_TYPE_DLM                      3      /**<       */
#define D_SP_ROADMARK_TYPE_BOTTS                    4      /**<       */
#define D_SP_ROADMARK_TYPE_DECELERATION             5      /**< 减速带 */
#define D_SP_ROADMARK_TYPE_HOV_LANE                 6      /**<       */
#define D_SP_ROADMARK_TYPE_BROKEN_SOLID             7
#define D_SP_ROADMARK_TYPE_SOLID_BROKEN             8
#define D_SP_ROADMARK_TYPE_SOLID_SOLID              9


#define D_SP_ROADMARK_COLOR_UNDECIDED               0      /**< 未定义 */
#define D_SP_ROADMARK_COLOR_WHITE                   1      /**< 白色   */
#define D_SP_ROADMARK_COLOR_YELLOW                  2      /**< 黄色   */
#define D_SP_ROADMARK_COLOR_BLUE                    3      /**< 蓝色   */


#define D_SP_VEHICLE_LIGHT_OFF                    0x00000000
#define D_SP_VEHICLE_LIGHT_INDICATOR_L            0x00000001
#define D_SP_VEHICLE_LIGHT_INDICATOR_R            0x00000002
#define D_SP_VEHICLE_LIGHT_REAR_BRAKE             0x00000004
#define D_SP_VEHICLE_LIGHT_LOW_BEAM               0x00000008
#define D_SP_VEHICLE_LIGHT_HIGH_BEAM              0x00000010
#define D_SP_VEHICLE_LIGHT_REAR_DRIVE             0x00000020
#define D_SP_VEHICLE_LIGHT_FOG                    0x00000040


#define D_SP_LANE_EXISTS_OWN                      0x01
#define D_SP_LANE_EXISTS_LEFT                     0x02
#define D_SP_LANE_EXISTS_RIGHT                    0x04


#define D_SP_SENSOR_OBJECT_FLAG_NONE               0x0000
#define D_SP_SENSOR_OBJECT_FLAG_CRITICALITY_LOW    0x0001
#define D_SP_SENSOR_OBJECT_FLAG_CRITICALITY_MEDIUM 0x0002
#define D_SP_SENSOR_OBJECT_FLAG_CRITICALITY_HIGH   0x0003
#define D_SP_SENSOR_OBJECT_FLAG_LANE_POS_VALID     0x0008


#define D_SP_ROAD_DIR_FLAG_NONE                    0x00
#define D_SP_ROAD_DIR_FLAG_DIR_FWD                 0x01
#define D_SP_ROAD_DIR_FLAG_DIR_REAR                0x02
#define D_SP_ROAD_DIR_FLAG_OFFROAD                 0x04


#define D_SP_SYNC_CMD_NONE                       0x0000
#define D_SP_SYNC_CMD_FINISH_CURRENT             0x0001
#define D_SP_SYNC_CMD_FINISH_ALL                 0x0002
#define D_SP_SYNC_CMD_TRIGGER                    0x0004

/*******************转向灯********************/
#define ASIM_VEHICLE_LIGHT_REAR_BRAKE             0x00000008  /**< only rear lights are ON                                 @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_INDICATOR_L            0x00000020  /**< left indicator lights are ON                            @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_INDICATOR_R            0x00000040  /**< right indicator lights are ON                           @version 0x0100 */

/** ------ 坐标 ------ */
typedef struct
{
    double   u8X;
    double   u8Y;
    double   u8Z;
    float    u4H;
    float    u4P;
    float    u4R;
    uint8_t  u1Type;                     /**< @link D_SP_COORDINATE_TYPE  */
    uint8_t  au1Spare[3];
} S_SP_COORDINATE;

/** ------ 初始化参数 ------ */
typedef struct
{
    uint64_t         u8StartRoadId;
    uint64_t         u8EndRoadId;
    float            u4RoadS;
    float            u4Speed;
    uint16_t         u2ScenarioId;
    int8_t           u1LaneId;
    uint8_t          u1Spare;
} S_SP_INIT_PARAM;

/** ------ 车道信息 ------ */
typedef struct
{
    uint64_t    u8RoadId;
    uint32_t    u4ObjectId;
    float       u4Width;
    uint16_t    u2Type;
    int8_t      u1Id;
    uint8_t     u1NeighborMask;            /**< @link D_SP_LANE_EXISTS */
    int8_t      u1LeftLaneId;
    int8_t      u1RightLaneId;
    uint8_t     au1Spare[2];
} S_SP_LANE_INFO;

/** ------ 几何信息 ------ */
typedef struct
{
    float u4DimX;
    float u4DimY;
    float u4DimZ;
    float u4OffX;
    float u4OffY;
    float u4OffZ;
} S_SP_GEOMETRY;

/** ------ 对象信息 ------ */
typedef struct
{
    S_SP_COORDINATE        sSpeed;
    S_SP_COORDINATE        sAccel;
    S_SP_GEOMETRY          sGeo;
    S_SP_COORDINATE        sPos;
    char                   au1Name[D_SP_SIZE_OBJECT_NAME];
    uint64_t               u8RoadId;
    uint32_t               u4Id;
    float                  u4RoadS;
    float                  u4RoadT;
    float                  u4HdgRel;
    float                  u4LaneOffset;
    float                  u4TraveledDist;
    uint8_t                u1Type;                       /**< @link D_SP_OBJECT_TYPE */
    int8_t                 u1LaneId;
    uint8_t                u1Dir;                        /**< @link D_SP_ROAD_DIR_FLAG */
    uint8_t                u1Spare;
} S_SP_OBJECT_STATE;

/** ------ 传感器定义和状态 ------ */
typedef struct
{
    S_SP_COORDINATE     sPos;
    S_SP_COORDINATE     sOriginCoordSys;
    char                au1Name[D_SP_SIZE_OBJECT_NAME];
    uint32_t            u8HostId;
    uint32_t            u8Id;
    float               au4FovHV[2];
    float               au4ClipNF[2];
    float               au4FovOffHV[2];
    uint8_t             u1Type;                        /**< @link D_SP_SENSOR_TYPE */
    uint8_t             au1Spare[3];
} S_SP_SENSOR_INFO;

/** ------ 传感器探测到的对象信息 ------ */
typedef struct
{
    S_SP_COORDINATE     sSensorPos;
    double              u8Dist;
    uint32_t            u4Id;
    uint32_t            u4SensorId;
    uint16_t            u2Flags;        /**< @link D_SP_SENSOR_OBJECT_FLAG */
    uint8_t             u1Type;         /**< @link D_SP_OBJECT_TYPE */
    int8_t              u1Occlusion;
    int8_t              u1DeltaLanePos;
    uint8_t             au1Spare[3];
} S_SP_SENSOR_DETECTION_INFO;

/** ------ 接触点信息 ------ */
typedef struct
{
    S_SP_COORDINATE     sRoadDataIn;
    uint16_t            u2Id;
    uint16_t            u2Spare;
} S_SP_CONTACT_POINT;

/** ------ 交通标志信息 ------ */
typedef struct
{
    char                au1Type[32];          /**< @link D_SP_TRAFFIC_SIGN_TYPE */
    S_SP_COORDINATE     sPos;
    uint32_t            u4TrafficSignId;
    uint32_t            u4ObjectId;
    int32_t             u4SubType;            /**< @link D_SP_TRAFFIC_SIGN_SUBTYPE */
    float               u4RoadDist;
    float               u4Value;
    int8_t              u1MinLane;
    int8_t              u1MaxLane;
    uint8_t             au1Spare[2];
} S_SP_TRAFFIC_SIGN;

/** ------ 车辆对应的道路状态 ------ */
typedef struct
{
    uint64_t            u8RoadId;
    uint32_t            u4ObjectId;
    float               u4DefaultSpeed;
    float               u4WaterLevel;
    float               u4DistToJunc;
} S_SP_ROAD_STATE;

/** ------ 环境信息 ------ */
typedef struct
{
    uint32_t            u4TimeOfDay;
    int16_t             u2TimeZoneMinutesWest;
    uint16_t            u2Year;
    uint8_t             u1Precipitation;
    uint8_t             u1CloudState;            /**< @link D_SP_ENV_CLOUD_STATE */
    uint8_t             u1Day;
    uint8_t             u1Month;
} S_SP_ENVIRONMENT;

/** ------ 驾驶员控制输入的信息 ------ */
typedef struct
{
    double              u8MasterCylinderPressure;
    uint32_t            u4ObjectId;
    float               u4SteeringWheel;
    float               u4ThrottlePedal;
    float               u4BrakePedal;
    float               u4AccelTgt;
    uint8_t             u1Gear;                    /**< @link D_SP_GEAR_BOX_POS */
    uint8_t             au1Spare0[3];
} S_SP_DRIVER_CTRL;

/** ------ 交通灯相位信息 ------ */
typedef struct
{
    float               u4Duration;
    uint8_t             u1Status;                            /**< @link D_SP_TRLIGHT_STATUS */
    uint8_t             au1Spare[3];
} S_SP_TRAFFIC_LIGHT_PHASE;

/** ------ 交通灯信息 ------ */
typedef struct
{
    int32_t             u4Id;
    int32_t             u4CtrlId;
    uint32_t            u4NoPhases;
    uint32_t            u4DataSize;
    float               u4State;
    float               u4CycleTime;
} S_SP_TRAFFIC_LIGHT;

/** ------ 同步信号 ------ */
typedef struct
{
    uint32_t            u4CmdMask;       /**< @link D_SP_SYNC_CMD             */
} S_SP_SYNC;

/** ------ 查询道路点 ------ */
typedef struct
{
    double              u8X;
    double              u8Y;
    uint16_t            u2Id;
    uint16_t            u2Spare;
} S_SP_ROAD_QUERY;

/** ------ MIL测试主车信息描述包 ------ */
typedef struct
{
    S_SP_OBJECT_STATE	            sObjectState;
    uint32_t                        u4LightMask;               /**< @link D_SP_VEHICLE_LIGHT */
    float                           u4WheelSpeedFL;
    float                           u4WheelSpeedFR;
    float                           u4WheelSpeedRL;
    float                           u4WheelSpeedRR;
    float                           u4MasterCylinderPressure;
} S_SP_MIL_EGO_STATE;

/** ------ MIL测试环境车、行人、障碍物信息描述包 ------ */
typedef struct
{
    uint32_t    u4LightMask;               /**< @link D_SP_VEHICLE_LIGHT */
    float	    u4DistanceX;
    float	    u4DistanceY;
    float	    u4VelocityX;
    float	    u4VelocityY;
    float	    u4AccelerationX;
    float	    u4YawRate;
    float       u4Dist;
    float       u4Angle;
    uint8_t	    u1ObjClass;
    uint8_t     au1Spare[3];
} S_SP_MIL_OBJECT_STATE_BASE;

/** ------ MIL测试环境车、行人、障碍物信息 ------ */
typedef struct
{
    S_SP_OBJECT_STATE	            sObjectState;
    S_SP_MIL_OBJECT_STATE_BASE	    sMilBase;
} S_SP_MIL_OBJECT_STATE;

/** ------ MIL测试车道线信息描述包 ------ */
typedef struct
{
    uint64_t            u8RoadId;
    float               u4StartDx;
    float               u4Width;
    float	            u4ViewRangeStart;
    float	            u4ViewRangeEnd;
    float	            u4MeasuredVREnd;
    float	            u4C0;
    float	            u4C1;
    float	            u4C2;
    float	            u4C3;
    uint16_t	        u2LaneChange;
    int8_t	            u1LaneId;
    uint8_t	            u1Quality;
    uint8_t	            u1Type;           	/** @link D_SP_ROADMARK_TYPE */
    uint8_t	            u1Color;          	/** @link D_SP_ROADMARK_COLOR */
    uint8_t	            u1LeftCrossing;
    uint8_t	            u1RightCrossing;
} S_SP_MIL_ROADMARK;

/** ------ Msg header ------ */
typedef struct
{
    double          u8SimTime;
    uint32_t        u4HeaderSize;
    uint32_t        u4DataSize;
    uint32_t        u4FrameNo;
} S_SP_MSG_HDR;

/** ------ Pkg header ------ */
typedef struct
{
    uint32_t        u4HeaderSize;
    uint32_t        u4DataSize;
    uint32_t        u4ElementSize;
    uint16_t        u2PkgId;
    uint16_t        u2Spare;
} S_SP_MSG_ENTRY_HDR;

/** ------ Pkg data ------ */
typedef union
{
    S_SP_LANE_INFO                 sLaneInfo;                      /**< @msgid D_SP_PKG_ID_LANE_INFO                 */
    S_SP_SENSOR_INFO               sSensorState;                   /**< @msgid D_SP_PKG_ID_SENSOR_INFO               */
    S_SP_SENSOR_DETECTION_INFO     sSensorObject;                  /**< @msgid D_SP_PKG_ID_SENSOR_DETECTION_INFO     */
    S_SP_CONTACT_POINT             sContactPoint;                  /**< @msgid D_SP_PKG_ID_CONTACT_POINT             */
    S_SP_TRAFFIC_SIGN              sTrafficSign;                   /**< @msgid D_SP_PKG_ID_TRAFFIC_SIGN              */
    S_SP_ROAD_STATE                sRoadState;                     /**< @msgid D_SP_PKG_ID_ROAD_STATE                */
    S_SP_ENVIRONMENT               sEnvironment;                   /**< @msgid D_SP_PKG_ID_ENVIRONMENT               */
    S_SP_DRIVER_CTRL               sDriverCtrl;                    /**< @msgid D_SP_PKG_ID_DRIVER_CTRL               */
    S_SP_TRAFFIC_LIGHT             sTrafficLight;                  /**< @msgid D_SP_PKG_ID_TRAFFIC_LIGHT             */
    S_SP_SYNC                      sSync;                          /**< @msgid D_SP_PKG_ID_SYNC                      */
    S_SP_ROAD_QUERY                sRoadQuery;                     /**< @msgid D_SP_PKG_ID_ROAD_QUERY                */
    S_SP_MIL_EGO_STATE             sEgoState;                      /**< @msgid D_SP_MIL_PKG_ID_EGO_DATA              */
    S_SP_MIL_OBJECT_STATE          sMilObjectState;                /**< @msgid D_SP_MIL_PKG_ID_OBJECT_DATA           */
    S_SP_MIL_ROADMARK              sMilRoadMark;                   /**< @msgid D_SP_MIL_PKG_ID_ROADMARK              */
    S_SP_INIT_PARAM                sInitParam;                     /**< @msgid D_SP_PKG_ID_INIT_PARAM                */
} S_SP_MSG_UNION;

/** ------ Msg struct ------ */
typedef struct
{
    S_SP_MSG_HDR            sMsgHdr;
    S_SP_MSG_ENTRY_HDR      sPkgHdr;
    S_SP_MSG_UNION          sPkgData;
} S_SP_MSG_t;

#pragma pack()
#endif //SP_COMMUNICATION_TYPE_H