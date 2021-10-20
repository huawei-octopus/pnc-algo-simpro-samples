#ifndef ASIM_COMMUNICATION_ASIMTYPE_H
#define ASIM_COMMUNICATION_ASIMTYPE_H

/* includes for 64bit compatibility */
#ifdef MATLAB_MEX_FILE
#include <sys/types.h>
    #include "viASIMTypes.h"
#else
#include <stdint.h>
#endif


/** @addtogroup ASIM_TRAFFIC_SIGN 交通标志和标线
 *  @{
 *  @ 2020.06.05 update
 */
#define ASIM_TRAFFIC_SIGN_TYPE                            (2000011)    /**< 交通标志 */

#define ASIM_TRAFFIC_SIGN_SUBTYPE_MAX_SPEED_LIMIT         (1)     /**< 最高限速标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_MIN_SPEED_LIMIT         (2)     /**< 最低限速标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_STOP_AND_YIELD          (3)     /**< 停车让行标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_NO_MOTOR_VEHICLE        (4)     /**< 禁止机动车通行标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_SLOW_DOWN_YIELD         (5)     /**< 减速让行标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_WARNING                 (6)     /**< 警告标志 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_PEDESTRIAN_CROSSING     (7)     /**< 人行横道线 */
#define ASIM_TRAFFIC_SIGN_SUBTYPE_SPEED_LIMIT_RELEASE     (8)     /**< 解除限速标志 */
/** @} */

/** @addtogroup GENERAL_DEFINITIONS
 *  @{
 */
#define ASIM_DEFAULT_PORT   48190       /**< default port for ASIM communication      @version 0x0100 */
#define ASIM_FEEDBACK_PORT  48191       /**< port for ASIM feedback to taskControl    @version 0x0100 */
#define ASIM_IMAGE_PORT     48192       /**< port for ASIM image data                 @version 0x0100 */
#define ASIM_MAGIC_NO       35712       /**< magic number                            @version 0x0100 */
#define ASIM_VERSION       0x011F       /**< upper byte = major, lower byte = minor  @version 0x011D */
/** @} */

/** @addtogroup ARRAY_SIZES
 *  ------ array sizes ------
 *  @{
 */
#define ASIM_SIZE_OBJECT_NAME       32       /**< maximum length of an object's name                 @version 0x0100 */
#define ASIM_SIZE_SCP_NAME          64       /**< maximum length of an SCP sender / receiver         @version 0x010C */
#define ASIM_SIZE_FILENAME        1024       /**< number of bytes in a filename (may include path)   @version 0x0100 */
#define ASIM_SIZE_TRLIGHT_PHASES     8       /**< maximum number of phases for a traffic light       @version 0x0100 */
/** @} */


/** @addtogroup ENUM_DEFINITIONS
 *  ------ Enum Definitions ------
 *  @{
 */
/** @addtogroup ASIM_PKG_ID
 *  ------ message types ------
 *  @{
 */
#define ASIM_PKG_ID_START_OF_FRAME               1     /**< sent as first package of a simulation frame                      @version 0x0100 */
#define ASIM_PKG_ID_END_OF_FRAME                 2     /**< sent as last package of a simulation frame                       @version 0x0100 */
#define ASIM_PKG_ID_COORD_SYSTEM                 3     /**< defines a (custom) co-ordinate system                            @version 0x0100 */
#define ASIM_PKG_ID_COORD                        4     /**< single co-ordinate extending previous object information         @version 0x0100 */
#define ASIM_PKG_ID_ROAD_POS                     5     /**< detailed road position of a given entity                         @version 0x0100 */
#define ASIM_PKG_ID_LANE_INFO                    6     /**< lane information for a given entity                              @version 0x0100 */
#define ASIM_PKG_ID_ROADMARK                     7     /**< road mark information of a player (typically EGO)                @version 0x0100 */
#define ASIM_PKG_ID_OBJECT_CFG                   8     /**< object configuration information                                 @version 0x0100 */
#define ASIM_PKG_ID_OBJECT_STATE                 9     /**< state of a standard (static) object                              @version 0x0100 */
#define ASIM_PKG_ID_VEHICLE_SYSTEMS             10     /**< vehicle systems' states (lights etc.)                            @version 0x0100 */
#define ASIM_PKG_ID_VEHICLE_SETUP               11     /**< basic information about a vehicle (mass etc.)                    @version 0x0100 */
#define ASIM_PKG_ID_ENGINE                      12     /**< info about a vehicle's engine                                    @version 0x0100 */
#define ASIM_PKG_ID_DRIVETRAIN                  13     /**< info about a vehicle's drivetrain                                @version 0x0100 */
#define ASIM_PKG_ID_WHEEL                       14     /**< info about a wheel of a player                                   @version 0x0100 */
#define ASIM_PKG_ID_PED_ANIMATION               15     /**< pedestrian animation details (joint angles etc.)                 @version 0x0100 */
#define ASIM_PKG_ID_SENSOR_STATE                16     /**< state (position etc.) of a sensor                                @version 0x0100 */
#define ASIM_PKG_ID_SENSOR_OBJECT               17     /**< information about an object registered within a sensor           @version 0x0100 */
#define ASIM_PKG_ID_CAMERA                      18     /**< camera parameters corresponding to video image                   @version 0x0100 */
#define ASIM_PKG_ID_CONTACT_POINT               19     /**< road data at a given contact point                               @version 0x0100 */
#define ASIM_PKG_ID_TRAFFIC_SIGN                20     /**< info about traffic signs objects                                 @version 0x0100 */
#define ASIM_PKG_ID_ROAD_STATE                  21     /**< road state information for a given player                        @version 0x0100 */
#define ASIM_PKG_ID_IMAGE                       22     /**< video image                                                      @version 0x0100 */
#define ASIM_PKG_ID_LIGHT_SOURCE                23     /**< light source information                                         @version 0x0100 */
#define ASIM_PKG_ID_ENVIRONMENT                 24     /**< environment information                                          @version 0x0100 */
#define ASIM_PKG_ID_TRIGGER                     25     /**< trigger info for next simulation frame                           @version 0x0100 */
#define ASIM_PKG_ID_DRIVER_CTRL                 26     /**< info about mockup or from driver module as input for dynamics    @version 0x0100 */
#define ASIM_PKG_ID_TRAFFIC_LIGHT               27     /**< information about a traffic lights and their states              @version 0x0100 */
#define ASIM_PKG_ID_SYNC                        28     /**< synchronization with external ASIM client                         @version 0x0100 */
#define ASIM_PKG_ID_DRIVER_PERCEPTION           29     /**< driver perception                                                @version 0x0100 */
#define ASIM_PKG_ID_LIGHT_MAP                   30     /**< light map for a headlight                                        @version 0x0100 */
#define ASIM_PKG_ID_TONE_MAPPING                31     /**< tone mapping function                                            @version 0x0100 */
#define ASIM_PKG_ID_ROAD_QUERY                  32     /**< co-ordinates of an explicit ODR road query                       @version 0x0107 */
#define ASIM_PKG_ID_SCP                         33     /**< SCP package via ASIM                                              @version 0x010C */
#define ASIM_PKG_ID_TRAJECTORY                  34     /**< trajectory for path planning                                     @version 0x0110 */
#define ASIM_PKG_ID_DYN_2_STEER                 35     /**< information from dynamics to steering wheel                      @version 0x0111 */
#define ASIM_PKG_ID_STEER_2_DYN                 36     /**< information from steering wheel to dynamics                      @version 0x0111 */
#define ASIM_PKG_ID_PROXY                       37     /**< proxy package handler                                            @version 0x0112 */
#define ASIM_PKG_ID_MOTION_SYSTEM               38     /**< information about motion system                                  @version 0x0116 */
#define ASIM_PKG_ID_OCCLUSION_MATRIX            39     /**< occlusion matrix of a sensor object                              @version 0x0117 */
#define ASIM_PKG_ID_FREESPACE                   40     /**< description of a single freespace object                         @version 0x0119 */
#define ASIM_PKG_ID_DYN_EL_SWITCH               41     /**< control of a dynamic switch element                              @version 0x011B */
#define ASIM_PKG_ID_DYN_EL_DOF                  42     /**< control of a dynamic DOF element                                 @version 0x011B */
#define ASIM_PKG_ID_IG_FRAME                    43     /**< info about frame received by IG                                  @version 0x011B */
#define ASIM_PKG_ID_RAY                         44     /**< information about a (sensor) ray                                 @version 0x011C */
#define ASIM_PKG_ID_RT_PERFORMANCE              45     /**< real-time performance monitorng                                  @version 0x011D */
#define ASIM_PKG_ID_SYMBOL_STATE                46     /**< state of a specific symbol                                       @version 0x011F */
#define ASIM_PKG_ID_REQUEST_AD_DATA             47     /**< request AD Data                                                  @version 0x0100 */

/** @} */

/** @addtogroup ASIM_PKG_ID_CUSTOM
 *  ------ custom message types, not to be expected in "standard" simulations ------
 *  @{
 */
#define ASIM_PKG_ID_CUSTOM_SCORING           10000     /**< parameters for driver scoring (efficiency, safety, race etc.)    @version 0x0100 */
#define ASIM_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK 10001     /**< control of an object using track information                     @version 0x0119 */
#define ASIM_PKG_ID_CUSTOM_LIGHT_B           10002     /**< custom light control package                                     @version 0x0119 */
#define ASIM_PKG_ID_CUSTOM_LIGHT_A           10003     /**< custom light control package                                     @version 0x0119 */
#define ASIM_PKG_ID_CUSTOM_LIGHT_GROUP_B     10004     /**< custom light control package                                     @version 0x011D */
#define ASIM_PKG_ID_CUSTOM_LOOK_AHEAD        10005     /**< custom look-ahead package                                        @version 0x011E */
#define ASIM_PKG_ID_CUSTOM_AUDI_FORUM        12000     /**< parameters for AUDI Forum                                        @version 0x0100 */
#define ASIM_PKG_ID_CUSTOM_OPTIX_START       12100     /**< start of custom packages for OPTIX applications                  @version 0x0100 */
#define ASIM_PKG_ID_OPTIX_BUFFER             12101     /**< custom optix buffer for ASIMInterface Plugin                      @version 0x010C */
#define ASIM_PKG_ID_CUSTOM_OPTIX_END         12149     /**< end of custom packages for OPTIX applications                    @version 0x0100 */
#define ASIM_PKG_ID_CUSTOM_USER_A_START      12150     /**< start of custom packages for user A                              @version 0x0106 */
#define ASIM_PKG_ID_CUSTOM_USER_A_END        12174     /**< end of custom packages for user A                                @version 0x0106 */
#define ASIM_PKG_ID_CUSTOM_USER_B_START      12175     /**< start of custom packages for user B                              @version 0x011C */
#define ASIM_PKG_ID_CUSTOM_USER_B_END        12200     /**< end of custom packages for user B                                @version 0x011C */
/** @} */

/** @addtogroup ASIM_OBJECT_CATEGORY
 *  ------ object types ------
 *  @{
 */
#define ASIM_OBJECT_CATEGORY_NONE           0    /**< no category defined           @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_PLAYER         1    /**< category is player            @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_SENSOR         2    /**< category is sensor            @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_CAMERA         3    /**< category is camera            @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_LIGHT_POINT    4    /**< category is light point       @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_COMMON         5    /**< category is common object     @version 0x0100 */
#define ASIM_OBJECT_CATEGORY_OPENDRIVE      6    /**< category is OpenDRIVE object  @version 0x0110 */
/** @} */

/** @addtogroup ASIM_OBJECT_TYPE
 *  ------ object types ------
 *  @{
 */
#define ASIM_OBJECT_TYPE_NONE                   0    /**< undefined object type for categories other than player         @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_NONE            0    /**< undefined player type             			 					@version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_CAR             1    /**< player of type car                                             @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_TRUCK           2    /**< player of type truck                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_VAN             3    /**< player of type van                                             @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_BIKE            4    /**< player of type bicycle                                         @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_PEDESTRIAN      5    /**< player of type pedestrian                                      @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_PED_GROUP       6    /**< player of type pedestrian group                                @version 0x0100 */
#define ASIM_OBJECT_TYPE_POLE                   7    /**< pole                                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_TREE                   8    /**< tree                                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_BARRIER                9    /**< barrier                                                        @version 0x0100 */
#define ASIM_OBJECT_TYPE_OPT1                  10    /**< optional user type 1                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_OPT2                  11    /**< optional user type 2                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_OPT3                  12    /**< optional user type 3                                           @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_MOTORBIKE      13    /**< player of type motorbike                                       @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_BUS            14    /**< player of type bus                                             @version 0x0100 */
#define ASIM_OBJECT_TYPE_STREET_LAMP           15    /**< street lamp                                                    @version 0x0100 */
#define ASIM_OBJECT_TYPE_TRAFFIC_SIGN          16    /**< traffic sign                                                   @version 0x0100 */
#define ASIM_OBJECT_TYPE_HEADLIGHT             17    /**< headlights                                                     @version 0x0100 */
#define ASIM_OBJECT_TYPE_PLAYER_TRAILER        18    /**< player of type trailer                                         @version 0x0108 */
#define ASIM_OBJECT_TYPE_BUILDING              19    /**< object of type building                                        @version 0x0108 */
#define ASIM_OBJECT_TYPE_PARKING_SPACE         20    /**< object of type parking space                                   @version 0x0112 */
#define ASIM_OBJECT_TYPE_ROAD_WORKS            21    /**< object for road works                                          @version 0x0112 */
#define ASIM_OBJECT_TYPE_ROAD_MISC             22    /**< miscellaneous road object                                      @version 0x0112 */
#define ASIM_OBJECT_TYPE_TUNNEL                23    /**< object for tunnel environment                                  @version 0x0112 */
#define ASIM_OBJECT_TYPE_LEGACY                24    /**< legacy object (not to be used)                                 @version 0x0112 */
#define ASIM_OBJECT_TYPE_VEGETATION            25    /**< common vegetation object                                       @version 0x0114 */
#define ASIM_OBJECT_TYPE_MISC_MOTORWAY         26    /**< common motorway object                                         @version 0x0114 */
#define ASIM_OBJECT_TYPE_MISC_TOWN             27    /**< common town object                                             @version 0x0114 */
#define ASIM_OBJECT_TYPE_PATCH                 28    /**< patch on road                                                  @version 0x0114 */
#define ASIM_OBJECT_TYPE_OTHER                 29    /**< any other unspecified object                                   @version 0x0114 */
#define ASIM_OBJECT_PLAYER_SEMI_TRAILER        30    /**< player of type semi trailer                                    @version 0x0114 */
#define ASIM_OBJECT_PLAYER_RAILCAR             31    /**< player of type rail car                                        @version 0x0114 */
#define ASIM_OBJECT_PLAYER_RAILCAR_SEMI_HEAD   32    /**< player of type rail car semi, head                             @version 0x0114 */
#define ASIM_OBJECT_PLAYER_RAILCAR_SEMI_BACK   33    /**< player of type rail car semi, back                             @version 0x0114 */
#define ASIM_OBJECT_TYPE_VEH_LIGHT_FRONT_LEFT  34    /**< headlight front left                                           @version 0x0119 */
#define ASIM_OBJECT_TYPE_VEH_LIGHT_FRONT_RIGHT 35    /**< headlight front right                                          @version 0x0119 */
#define ASIM_OBJECT_TYPE_VEH_LIGHT_REAR_LEFT   36    /**< tail light left                                                @version 0x0119 */
#define ASIM_OBJECT_TYPE_VEH_LIGHT_REAR_RIGHT  37    /**< tail light right                                               @version 0x0119 */
#define ASIM_OBJECT_TYPE_VEH_CABIN             38    /**< articulated cabin (e.g. for trucks), must have parent          @version 0x0119 */
/** @} */

/** @addtogroup ASIM_LANE_BORDER
 *  ------ lane border types ------
 *  @{
 */
#define ASIM_LANE_BORDER_UNKNOWN          0      /**< unknown border type    @version 0x0100 */
#define ASIM_LANE_BORDER_NONE             1      /**< no border              @version 0x0100 */
#define ASIM_LANE_BORDER_POLE             2      /**< pole border            @version 0x0100 */
#define ASIM_LANE_BORDER_BARRIER          3      /**< barrier border         @version 0x0100 */
#define ASIM_LANE_BORDER_SOFT_SHOULDER    4      /**< soft shoulder border   @version 0x0100 */
#define ASIM_LANE_BORDER_HARD_SHOULDER    5      /**< hard shoulder border   @version 0x0100 */
#define ASIM_LANE_BORDER_CURB             6      /**< curb border */
/** @} */

/** @addtogroup ASIM_ROADMARK_TYPE
 *  ------ road mark types ------
 *  @{
 */
#define ASIM_ROADMARK_TYPE_NONE           0      /**< no roadmark defined    @version 0x0100 */
#define ASIM_ROADMARK_TYPE_SOLID          1      /**< solid marks            @version 0x0100 */
#define ASIM_ROADMARK_TYPE_BROKEN         2      /**< broken marks           @version 0x0100 */
#define ASIM_ROADMARK_TYPE_CURB           3      /**< curb                   @version 0x0100 */
#define ASIM_ROADMARK_TYPE_GRASS          4      /**< grass                  @version 0x0100 */
#define ASIM_ROADMARK_TYPE_BOTDOT         5      /**< Botts' dots            @version 0x0100 */
#define ASIM_ROADMARK_TYPE_OTHER          6      /**< something else         @version 0x0100 */
#define ASIM_ROADMARK_TYPE_SOLID_SOLID    7      /**< solid solid            @version 0x011F */
#define ASIM_ROADMARK_TYPE_BROKEN_SOLID   8      /**< broken solid           @version 0x011F */
#define ASIM_ROADMARK_TYPE_SOLID_BROKEN   9      /**< solid broken           @version 0x011F */
#define ASIM_ROADMARK_TYPE_LANE_CENTER   10      /**< center of the lane     @version 0x011F */
/** @} */

/** @addtogroup ASIM_ROADMARK_COLOR
 *  ------ road mark colors ------
 *  @{
 */
#define ASIM_ROADMARK_COLOR_NONE          0      /**< no color defined   @version 0x0100 */
#define ASIM_ROADMARK_COLOR_WHITE         1      /**< white color        @version 0x0100 */
#define ASIM_ROADMARK_COLOR_RED           2      /**< red color          @version 0x0100 */
#define ASIM_ROADMARK_COLOR_YELLOW        3      /**< yellow color       @version 0x0100 */
#define ASIM_ROADMARK_COLOR_OTHER         4      /**< other color        @version 0x0100 */
#define ASIM_ROADMARK_COLOR_BLUE          5      /**< blue color         @version 0x0113 */
#define ASIM_ROADMARK_COLOR_GREEN         6      /**< green color        @version 0x0113 */
/** @} */

/** @addtogroup ASIM_WHEEL_ID
 *  ------ wheel indices ------
 *  @{
 */
#define ASIM_WHEEL_ID_FRONT_LEFT          0      /**< increase ID clockwise; next one is front right wheel (not on trikes)   @version 0x0100 */
/** @} */

/** @addtogroup ASIM_GEAR_BOX_TYPE
 *  ------ gear box types ------
 *  @{
 */
#define ASIM_GEAR_BOX_TYPE_AUTOMATIC      0      /**< automatic gear shift   @version 0x0100 */
#define ASIM_GEAR_BOX_TYPE_MANUAL         1      /**< manual gear shift      @version 0x0100 */
/** @} */

/** @addtogroup ASIM_GEAR_BOX_POS
 *  ------ gear box positions ------
 *  @{
 */
#define ASIM_GEAR_BOX_POS_AUTO             0     /**< gear set to automatic                 @version 0x0100 */
#define ASIM_GEAR_BOX_POS_P                1     /**< park                                  @version 0x0100 */
#define ASIM_GEAR_BOX_POS_R                2     /**< reverse                               @version 0x0100 */
#define ASIM_GEAR_BOX_POS_N                3     /**< neutral                               @version 0x0100 */
#define ASIM_GEAR_BOX_POS_D                4     /**< drive                                 @version 0x0100 */
#define ASIM_GEAR_BOX_POS_1                5     /**< 1st gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_2                6     /**< 2nd gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_3                7     /**< 3rd gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_4                8     /**< 4th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_5                9     /**< 5th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_6               10     /**< 6th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_7               11     /**< 7th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_8               12     /**< 8th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_9               13     /**< 9th gear                              @version 0x0100 */
#define ASIM_GEAR_BOX_POS_10              14     /**< 10th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_11              15     /**< 11th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_12              16     /**< 12th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_13              17     /**< 13th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_14              18     /**< 14th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_15              19     /**< 15th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_16              20     /**< 16th gear                             @version 0x0100 */
#define ASIM_GEAR_BOX_POS_R1              21     /**< 1st reverse gear                      @version 0x0100 */
#define ASIM_GEAR_BOX_POS_R2              22     /**< 2nd reverse gear                      @version 0x0100 */
#define ASIM_GEAR_BOX_POS_R3              23     /**< 3rd reverse gear                      @version 0x0100 */
#define ASIM_GEAR_BOX_POS_M               24     /**< manual shift position (tiptronic)     @version 0x010A */
#define ASIM_GEAR_BOX_POS_M_UP            25     /**< manual shift up                       @version 0x010A */
#define ASIM_GEAR_BOX_POS_M_DOWN          26     /**< manual shift down                     @version 0x010A */
#define ASIM_GEAR_BOX_POS_C               27     /**< position C                            @version 0x0119 */
#define ASIM_GEAR_BOX_POS_MS              28     /**< position MS                           @version 0x0119 */
#define ASIM_GEAR_BOX_POS_CS              29     /**< position CS                           @version 0x0119 */
#define ASIM_GEAR_BOX_POS_PS              30     /**< position PS                           @version 0x0119 */
#define ASIM_GEAR_BOX_POS_RS              31     /**< position RS                           @version 0x0119 */
#define ASIM_GEAR_BOX_POS_NS              32     /**< position NS                           @version 0x0119 */
#define ASIM_GEAR_BOX_POS_DS              33     /**< position DS                           @version 0x0119 */
/** @} */

/** @addtogroup ASIM_DRIVETRAIN_TYPE
 *  ------ drivetrain types ------
 *  @{
 */
#define ASIM_DRIVETRAIN_TYPE_FRONT        0      /**< front-wheel drive  @version 0x0100 */
#define ASIM_DRIVETRAIN_TYPE_REAR         1      /**< rear-wheel drive   @version 0x0100 */
#define ASIM_DRIVETRAIN_TYPE_AWD          2      /**< all-wheel drive    @version 0x0100 */
/** @} */

/** @addtogroup ASIM_PIX_FORMAT
 *  ------ image pixel formats ------
 *  @{
 */
#define ASIM_PIX_FORMAT_RGB              0  /**< deprecated: use ASIM_PIX_FORMAT_R3_G2_B2        @version 0x0100 */
#define ASIM_PIX_FORMAT_RGB_16           1  /**< deprecated: use ASIM_PIX_FORMAT_R5_G6_B5        @version 0x0100 */
#define ASIM_PIX_FORMAT_RGB_24           2  /**< deprecated: use ASIM_PIX_FORMAT_RGB8            @version 0x0100 */
#define ASIM_PIX_FORMAT_RGBA             3  /**< deprecated: use ASIM_PIX_FORMAT_R3_G2_B2_A8     @version 0x0100 */
#define ASIM_PIX_FORMAT_RGBA_16          4  /**< deprecated: use ASIM_PIX_FORMAT_R5_G6_B5_A16    @version 0x0100 */
#define ASIM_PIX_FORMAT_RGBA_24          5  /**< deprecated: use ASIM_PIX_FORMAT_RGB8_A24        @version 0x0100 */
#define ASIM_PIX_FORMAT_BW_8             6  /**< deprecated: use ASIM_PIX_FORMAT_RED8            @version 0x0100 */
#define ASIM_PIX_FORMAT_BW_16            7  /**< deprecated: use ASIM_PIX_FORMAT_RED16           @version 0x0100 */
#define ASIM_PIX_FORMAT_BW_24            8  /**< deprecated: use ASIM_PIX_FORMAT_RED24           @version 0x0100 */
#define ASIM_PIX_FORMAT_DEPTH_8          9  /**< deprecated: use ASIM_PIX_FORMAT_DEPTH8          @version 0x0100 */
#define ASIM_PIX_FORMAT_DEPTH_16        10  /**< deprecated: use ASIM_PIX_FORMAT_DEPTH16         @version 0x0100 */
#define ASIM_PIX_FORMAT_DEPTH_24        11  /**< deprecated: use ASIM_PIX_FORMAT_DEPTH24         @version 0x0100 */
#define ASIM_PIX_FORMAT_RGB_32_F        12  /**< deprecated: use ASIM_PIX_FORMAT_RGB32F          @version 0x0100 */
#define ASIM_PIX_FORMAT_RGBA_32_F       13  /**< deprecated: use ASIM_PIX_FORMAT_RGBA32F         @version 0x0100 */
#define ASIM_PIX_FORMAT_LUM_32_F        14  /**< deprecated: use ASIM_PIX_FORMAT_RED32F          @version 0x0100 */
#define ASIM_PIX_FORMAT_LUMA_32_F       15  /**< deprecated: use ASIM_PIX_FORMAT_RG32F           @version 0x0100 */
#define ASIM_PIX_FORMAT_RGB_16_F        16  /**< deprecated: use ASIM_PIX_FORMAT_RGB16F          @version 0x0100 */
#define ASIM_PIX_FORMAT_RGBA_16_F       17  /**< deprecated: use ASIM_PIX_FORMAT_RGBA16F         @version 0x0100 */
#define ASIM_PIX_FORMAT_LUM_16_F        18  /**< deprecated: use ASIM_PIX_FORMAT_RED16F          @version 0x0100 */
#define ASIM_PIX_FORMAT_LUMA_16_F       19  /**< deprecated: use ASIM_PIX_FORMAT_RG16F           @version 0x0100 */
#define ASIM_PIX_FORMAT_DEPTH_32        20  /**< deprecated: use ASIM_PIX_FORMAT_DEPTH32         @version 0x0101 */
#define ASIM_PIX_FORMAT_BW_32           21  /**< deprecated: use ASIM_PIX_FORMAT_RED32           @version 0x0106 */
#define ASIM_PIX_FORMAT_RGB_32          22  /**< 32 bit RGB data                                @version 0x0106 */
#define ASIM_PIX_FORMAT_RGBA_32         23  /**< 32 bit RGB data + 32 bit alpha                 @version 0x0106 */

#define ASIM_PIX_FORMAT_R3_G2_B2        24  /**<   8 bit RGB data                          @version 0x010F */
#define ASIM_PIX_FORMAT_R3_G2_B2_A8     25  /**<   8 bit RGB data + 8 bit alpha            @version 0x010F */
#define ASIM_PIX_FORMAT_R5_G6_B5        26  /**<  16 bit RGB data                          @version 0x010F */
#define ASIM_PIX_FORMAT_R5_G6_B5_A16    27  /**<  16 bit RGB data + 16 bit alpha           @version 0x010F */
#define ASIM_PIX_FORMAT_RED8            28  /**<   8 bit RED data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RED16           29  /**<  16 bit RED data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RED16F          30  /**<  16 bit RED floating point data           @version 0x010F */
#define ASIM_PIX_FORMAT_RED24           31  /**<  24 bit RED data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RED32           32  /**<  32 bit RED data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RED32F          33  /**<  32 bit RED floating point data           @version 0x010F */
#define ASIM_PIX_FORMAT_RG8             34  /**<  16 bit RED+GREEN data                    @version 0x010F */
#define ASIM_PIX_FORMAT_RG16            35  /**<  32 bit RED+GREEN data                    @version 0x010F */
#define ASIM_PIX_FORMAT_RG16F           36  /**<  32 bit RED+GREEN floating point data     @version 0x010F */
#define ASIM_PIX_FORMAT_RG32            37  /**<  64 bit RED+GREEN floating point data     @version 0x010F */
#define ASIM_PIX_FORMAT_RG32F           38  /**<  64 bit RED+GREEN floating point data     @version 0x010F */
#define ASIM_PIX_FORMAT_RGB8            39  /**<  24 bit RGB data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RGBA8           40  /**<  24 bit RGB data + 8 bit alpha            @version 0x010F */
#define ASIM_PIX_FORMAT_RGB8_A24        41  /**<  24 bit RGB data + 24 bit alpha           @version 0x010F */
#define ASIM_PIX_FORMAT_RGB16           42  /**<  48 bit RGB data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RGB16F          43  /**<  48 bit RGB floating point data           @version 0x010F */
#define ASIM_PIX_FORMAT_RGBA16          44  /**<  64 bit RGBA data                         @version 0x010F */
#define ASIM_PIX_FORMAT_RGBA16F         45  /**<  64 bit RGBA floating point data          @version 0x010F */
#define ASIM_PIX_FORMAT_RGB32           46  /**<  96 bit RGB data                          @version 0x010F */
#define ASIM_PIX_FORMAT_RGB32F          47  /**<  96 bit RGB floating point data           @version 0x010F */
#define ASIM_PIX_FORMAT_RGBA32          48  /**< 128 bit RGBA data                         @version 0x010F */
#define ASIM_PIX_FORMAT_RGBA32F         49  /**< 128 bit RGBA floating point data          @version 0x010F */
#define ASIM_PIX_FORMAT_DEPTH8          50  /**<   8 bit DEPTH data                        @version 0x010F */
#define ASIM_PIX_FORMAT_DEPTH16         51  /**<  16 bit DEPTH data                        @version 0x010F */
#define ASIM_PIX_FORMAT_DEPTH24         52  /**<  24 bit DEPTH data                        @version 0x010F */
#define ASIM_PIX_FORMAT_DEPTH32         53  /**<  32 bit DEPTH data                        @version 0x010F */

/** @} */

/** @addtogroup ASIM_PIX_FORMAT_CUSTOM
 *  ------ custom pixel formats (any ID above 150 up to 255) may be used ------
 *  @{
 */
#define ASIM_PIX_FORMAT_CUSTOM_01           151     /**< custom image format 01    @version 0x0100 */
#define ASIM_PIX_FORMAT_CUSTOM_02           152     /**< custom image format 02    @version 0x0100 */
#define ASIM_PIX_FORMAT_CUSTOM_03           153     /**< custom image format 03    @version 0x0100 */
/** @} */

/** @addtogroup ASIM_SENSOR_TYPE
 *  ------ sensor types ------
 *  @{
 */
#define ASIM_SENSOR_TYPE_NONE            0  /**< unknown sensor type                      @version 0x0100 */
#define ASIM_SENSOR_TYPE_RADAR           1  /**< radar sensor                             @version 0x0100 */
#define ASIM_SENSOR_TYPE_VIDEO           2  /**< video sensor                             @version 0x0100 */
/** @} */

/** @addtogroup ASIM_TRLIGHT_PHASE
 *  ------ traffic light phases ------
 *  @{
 */
#define ASIM_TRLIGHT_PHASE_OFF           0   /**< traffic light is off                    @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_STOP          1   /**< traffic indicates STOP                  @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_STOP_ATTN     2   /**< traffic indicates STOP/ATTENTION        @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_GO            3   /**< traffic indicates GO                    @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_GO_EXCL       4   /**< traffic indicates GO EXCLUSIVELY        @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_ATTN          5   /**< traffic indicates ATTENTION             @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_BLINK         6   /**< traffic indicates BLINK                 @version 0x0100 */
#define ASIM_TRLIGHT_PHASE_UNKNOWN       7   /**< traffic indicates an unknown state      @version 0x0100 */
/** @} */

/** @addtogroup ASIM_COORD_TYPE
 *  ------ co-ordinate type identifiers ------
 *  @{
 */
#define ASIM_COORD_TYPE_INERTIAL         0  /**< inertial co-ordinate system              @version 0x0101 */
#define ASIM_COORD_TYPE_RESERVED_1       1  /**< reserved for future use                  @version 0x0101 */
#define ASIM_COORD_TYPE_PLAYER           2  /**< player co-ordinate system                @version 0x0100 */
#define ASIM_COORD_TYPE_SENSOR           3  /**< sensor-specific co-ordinate system       @version 0x0100 */
#define ASIM_COORD_TYPE_USK              4  /**< universal sensor co-ordinate system      @version 0x0100 */
#define ASIM_COORD_TYPE_USER             5  /**< relative to a user co-ordinate system    @version 0x0100 */
#define ASIM_COORD_TYPE_WINDOW           6  /**< window co-ordinates [pixel]              @version 0x0100 */
#define ASIM_COORD_TYPE_TEXTURE          7  /**< texture co-ordinates [normalized]        @version 0x010C */
#define ASIM_COORD_TYPE_RELATIVE_START   8  /**< co-ordinate relative to start pos.       @version 0x0110 */
#define ASIM_COORD_TYPE_GEO              9  /**< geographic co-ordinate                   @version 0x0118 */
#define ASIM_COORD_TYPE_TRACK           10  /**< track co-ordinate (x=s, y=t )            @version 0x0119 */
/** @} */

/** @addtogroup ASIM_ENV_CLOUD_STATE
 *  ------ cloud states ------
 *  @{
 */
#define ASIM_ENV_CLOUD_STATE_OFF         0  /**< sky is disabled                          @version 0x0100 */
#define ASIM_ENV_CLOUD_STATE_0_8         1  /**< blue sky                                 @version 0x0100 */
#define ASIM_ENV_CLOUD_STATE_4_8         2  /**< cloudy sky                               @version 0x0100 */
#define ASIM_ENV_CLOUD_STATE_6_8         3  /**< overcast sky                             @version 0x0100 */
#define ASIM_ENV_CLOUD_STATE_8_8         4  /**< rainy sky                                @version 0x0100 */
/** @} */

/** @addtogroup ASIM_FUNCTION_TYPE
 *  ------ function types ------
 *  @{
 */
#define ASIM_FUNCTION_TYPE_NONE          0  /**< unknown                                  @version 0x0100 */
#define ASIM_FUNCTION_TYPE_TONE_MAPPING  1  /**< tone mapping function                    @version 0x0100 */
/** @} */

/** @addtogroup ASIM_ROAD_TYPE
 *  ------ road types ------
 *  @{
 */
#define ASIM_ROAD_TYPE_UNKNOWN          0  /**< unknown                                  @version 0x010A */
#define ASIM_ROAD_TYPE_RURAL            1  /**< rural road (100km/h in Germany)          @version 0x010A */
#define ASIM_ROAD_TYPE_MOTORWAY         2  /**< motorway (no limit in Germany)           @version 0x010A */
#define ASIM_ROAD_TYPE_TOWN             3  /**< town (50km/h in Germany)                 @version 0x010A */
#define ASIM_ROAD_TYPE_LOW_SPEED        4  /**< low speed zone (30km/h in Germany)       @version 0x010A */
#define ASIM_ROAD_TYPE_PEDESTRIAN       5  /**< sidewalk (slow, worldwide)               @version 0x010A */
/** @} */

/** @addtogroup ASIM_DRIVER_SOURCE
 *  ------ sources of driver commands ------
 *  @{
 */
#define ASIM_DRIVER_SOURCE_UNKNOWN          0  /**< unknown                                  @version 0x010F */
#define ASIM_DRIVER_SOURCE_GHOSTDRIVER      1  /**< ghostdriver                              @version 0x010F */
/** @} */

/** @addtogroup ASIM_SHM_SIZE
 *  ------ shared memory sizes ------
 *  @{
 */
#define ASIM_SHM_SIZE_TC              5242880  /**< total SHM size for TC I/O  (5 MB)        @version 0x010F */
/** @} */

/** @addtogroup ASIM_FREESPACE_STATE
 *  ------ freespace state categories ------
 *  @{
 */
#define ASIM_FREESPACE_STATE_OBJECT_NONE      0  /**< no object                                @version 0x0119 */
#define ASIM_FREESPACE_STATE_OBJECT_SAME_DIR  1  /**< object in same direction                 @version 0x0119 */
#define ASIM_FREESPACE_STATE_OBJECT_ONCOMING  2  /**< oncoming object                          @version 0x0119 */
/** @} */


/** @addtogroup ASIM_DYN_EL_SCOPE
 *  ------ scope of the target of a dynamic element ------
 *  @{
 */
#define ASIM_DYN_EL_SCOPE_UNKNOWN            0       /**< scope of a dynamic element definition in unknown                           @version 0x011B */
#define ASIM_DYN_EL_SCOPE_STATIC_DB          1       /**< scope of a dynamic element definition in the static database               @version 0x011B */
#define ASIM_DYN_EL_SCOPE_DYN_OBJECT         2       /**< scope of a dynamic element definition in a dynamic object                  @version 0x011B */
#define ASIM_DYN_EL_SCOPE_ANY                3       /**< scope of a dynamic element definition in any object in the data tree       @version 0x011B */
#define ASIM_DYN_EL_SCOPE_FIRST              4       /**< scope of a dynamic element definition in the first object in the data tree @version 0x011B */
#define ASIM_DYN_EL_SCOPE_STATIC_DB_SIGNAL   5       /**< scope of a signal definition in the static database                        @version 0x011B */
#define ASIM_DYN_EL_SCOPE_STATIC_DB_SWITCH   6       /**< scope of a switch definition in the static database                        @version 0x011B */
/** @} */

/** @addtogroup ASIM_RAY_TYPE
 *  ------ type of ray contained in ray message ------
 *  @{
 */
#define ASIM_RAY_TYPE_UNKNOWN            0       /**< scope of a dynamic element definition in unknown                           @version 0x011C */
#define ASIM_RAY_TYPE_EMIT               1       /**< emitted ray                                                                @version 0x011C */
#define ASIM_RAY_TYPE_HIT                2       /**< hit point information                                                      @version 0x011C */
/** @} */

/** @addtogroup ASIM_UNIT
 *  ------ definition of physical units ------
 *  @{
 */
#define ASIM_UNIT_DEFAULT                0       /**< default unit                                                               @version 0x011E */
#define ASIM_UNIT_M                      1       /**< meters                                                                     @version 0x011E */
#define ASIM_UNIT_S                      2       /**< seconds                                                                    @version 0x011E */
/** @} */


/** @} --END GROUP ENUM_DEFINITIONS--*/

/** @addtogroup BITMASK_DEFINITIONS
 *  ------ Bitmask Definitions ------
 *  @{
 */
/** @addtogroup ASIM_PKG_FLAG
 *  ------ basic package flags ------
 *  @{
 */
#define ASIM_PKG_FLAG_NONE                        0x0000      /**< no flags                                                @version 0x0100 */
#define ASIM_PKG_FLAG_EXTENDED                    0x0001      /**< package contains extended information                   @version 0x0100 */
#define ASIM_PKG_FLAG_HIDDEN                      0x0002      /**< package contains hidden information (not for public)    @version 0x010E */
/** @} */

/** @addtogroup ASIM_OBJECT_VIS_FLAG
 *  ------ object visibility flags ------
 *  @{
 */
#define ASIM_OBJECT_VIS_FLAG_ALL                      0xffff  /**< all visibility flags set                                @version 0x0100 */
#define ASIM_OBJECT_VIS_FLAG_NONE                     0x0000  /**< no visibility flags set                                 @version 0x0100 */
#define ASIM_OBJECT_VIS_FLAG_GFX                      0x0001  /**< object is visible in graphics                           @version 0x0100 */
#define ASIM_OBJECT_VIS_FLAG_TRAFFIC                  0x0002  /**< object is visible for traffic                           @version 0x0100 */
#define ASIM_OBJECT_VIS_FLAG_RECORDER                 0x0004  /**< object is visible on data recorder                      @version 0x0110 */
/** @} */

/** @addtogroup ASIM_VEHICLE_LIGHT
 *  ------ light states ------
 *  @{
 */
#define ASIM_VEHICLE_LIGHT_OFF                    0x00000000  /**< all lights OFF                                          @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_PARK                   0x00000001  /**< front and rear lights are ON                            @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_LOW_BEAM               0x00000002  /**< front and rear lights are ON                            @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_HIGH_BEAM              0x00000004  /**< front lights are ON                                     @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_REAR_BRAKE             0x00000008  /**< only rear lights are ON                                 @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_REAR_DRIVE             0x00000010  /**< only rear lights are ON                                 @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_INDICATOR_L            0x00000020  /**< left indicator lights are ON                            @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_INDICATOR_R            0x00000040  /**< right indicator lights are ON                           @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_FLASH                  0x00000080  /**< special light for police forces etc.                    @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_FRONT_FOG              0x00000100  /**< only front lights are ON                                @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_REAR_FOG               0x00000200  /**< only rear lights are ON                                 @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_VIRES1                 0x00000400  /**< used internally by VIRES                                @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_DRL                    0x00000800  /**< daytime running light                                   @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_DRL_LEFT_LOW           0x00001000  /**< dimmed state of left front DRLs                         @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_DRL_RIGHT_LOW          0x00002000  /**< dimmed state of right front DRLs                        @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_EMERGENCY              0x00004000  /**< emergency indicator lights                              @version 0x0100 */
#define ASIM_VEHICLE_LIGHT_INDICATOR_LAMP_ON      0x00008000  /**< true if an indicator lamp is                            @version 0x0111 */
#define ASIM_VEHICLE_LIGHT_FORCE                  0x00010000  /**< if received via ASIM, ASIM will be the only source for the light mask  @version 0x0111 */
/** @} */

/** @addtogroup ASIM_VEHICLE_ACC_FLAG
 *  ------ acc states, 1 byte ------
 *  @{
 */
#define ASIM_VEHICLE_ACC_FLAG_OFF             0x00  /**< ACC is OFF                                              @version 0x010A */
#define ASIM_VEHICLE_ACC_FLAG_DIST_1          0x01  /**< ACC distance setting 1                                  @version 0x010A */
#define ASIM_VEHICLE_ACC_FLAG_DIST_2          0x02  /**< ACC distance setting 2                                  @version 0x010A */
#define ASIM_VEHICLE_ACC_FLAG_DIST_3          0x03  /**< ACC distance setting 3                                  @version 0x010A */
#define ASIM_VEHICLE_ACC_FLAG_TARGET          0x04  /**< show ACC target vehicle                                 @version 0x010A */
#define ASIM_VEHICLE_ACC_FLAG_SPEED           0x08  /**< show ACC speed                                          @version 0x010A */
/** @} */

/** @addtogroup ASIM_VEHICLE_DISPLAY_LIGHT
 *  ------ display lights, 2 bytes ------
 *  @{
 */
#define ASIM_VEHICLE_DISPLAY_LIGHT_OFF        0x0000  /**< all lights OFF in driver display                         @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_01         0x0001  /**< light 01 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_02         0x0002  /**< light 02 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_03         0x0004  /**< light 03 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_04         0x0008  /**< light 04 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_05         0x0010  /**< light 05 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_06         0x0020  /**< light 06 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_07         0x0040  /**< light 07 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_08         0x0080  /**< light 08 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_09         0x0100  /**< light 09 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_10         0x0200  /**< light 10 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_11         0x0400  /**< light 11 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_12         0x0800  /**< light 12 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_13         0x1000  /**< light 13 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_14         0x2000  /**< light 14 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_15         0x4000  /**< light 15 ON in driver display                            @version 0x010A */
#define ASIM_VEHICLE_DISPLAY_LIGHT_16         0x8000  /**< light 16 ON in driver display                            @version 0x010A */
/** @} */


/** @addtogroup ASIM_LANE_EXISTS
 *  ------ lane existence masks ------
 *  @{
 */
#define ASIM_LANE_EXISTS_OWN                      0x01        /**< own lane exists                                         @version 0x0100 */
#define ASIM_LANE_EXISTS_LEFT                     0x02        /**< left lane exists                                        @version 0x0100 */
#define ASIM_LANE_EXISTS_RIGHT                    0x04        /**< right lane exists                                       @version 0x0100 */
/** @} */

/** @addtogroup ASIM_LANE_STATUS
 *  ------ lane status masks ------
 *  @{
 */
#define ASIM_LANE_STATUS_NONE                     0x0000      /**< nothing special                                         @version 0x0100 */
#define ASIM_LANE_STATUS_ROADWORKS                0x0001      /**< road works                                              @version 0x0100 */
#define ASIM_LANE_STATUS_EXIT                     0x0002      /**< motorway exit                                           @version 0x0100 */
#define ASIM_LANE_STATUS_ENTRY                    0x0004      /**< motorway entry                                          @version 0x0100 */
#define ASIM_LANE_STATUS_LINKED                   0x0008      /**< linked lanes                                            @version 0x0100 */
#define ASIM_LANE_STATUS_WET                      0x0010      /**< wet lane (from rain)                                    @version 0x0100 */
#define ASIM_LANE_STATUS_SNOW                     0x0020      /**< snow-covered lane                                       @version 0x0100 */
/** @} */

/** @addtogroup ASIM_DRIVER_FLAG
 *  ------ dynamics input flags ------
 *  @{
 */
#define ASIM_DRIVER_FLAG_NONE                     0x00000000  /**< default                                                 @version 0x0100 */
#define ASIM_DRIVER_FLAG_INDICATOR_L              0x00000001  /**< driver activated left indicator                         @version 0x0100 */
#define ASIM_DRIVER_FLAG_INDICATOR_R              0x00000002  /**< driver activated right indicator                        @version 0x0100 */
#define ASIM_DRIVER_FLAG_PARKING_BRAKE            0x00000004  /**< driver activated parking brake                          @version 0x0100 */
#define ASIM_DRIVER_FLAG_LIGHT_LOW_BEAM           0x00000008  /**< driver activated low beam headlights                    @version 0x0105 */
#define ASIM_DRIVER_FLAG_LIGHT_HIGH_BEAM          0x00000010  /**< driver activated high beam headlights                   @version 0x0105 */
#define ASIM_DRIVER_FLAG_LIGHT_FOG_FRONT          0x00000020  /**< driver activated front fog light                        @version 0x0105 */
#define ASIM_DRIVER_FLAG_LIGHT_FOG_REAR           0x00000040  /**< driver activated rear fog light                         @version 0x0105 */
#define ASIM_DRIVER_FLAG_LIGHT_EMERGENCY          0x00000080  /**< driver activated emergency light (indic. L&R)           @version 0x0105 */
#define ASIM_DRIVER_FLAG_LIGHT_PRIORITY           0x00000100  /**< driver activated priority light (blue flashlight)       @version 0x0105 */
#define ASIM_DRIVER_FLAG_COLLISION                0x00000200  /**< driver noticed a collision with his vehicle             @version 0x0119 */
/** @} */

/** @addtogroup ASIM_MOCKUP_INPUT0
 *  ------ mockup input flags, part 1 ------
 *  @{
 */
/* INPUT: MFL and SZL bits */
#define ASIM_MOCKUP_INPUT0_MFL_PLUS           0x00000001  /**< input no. 0 for MFL_PLUS               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_MINUS          0x00000002  /**< input no. 0 for MFL_MINUS              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_PHONE          0x00000004  /**< input no. 0 for MFL_PHONE              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_VOICE          0x00000008  /**< input no. 0 for MFL_VOICE              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_UP             0x00000010  /**< input no. 0 for MFL_UP                 @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_DOWN           0x00000020  /**< input no. 0 for MFL_DOWN               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_DIAMOND        0x00000040  /**< input no. 0 for MFL_DIAMOND            @version 0x010B */
#define ASIM_MOCKUP_INPUT0_MFL_STAR           0x00000080  /**< input no. 0 for MFL_STAR               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_UP            0x00000100  /**< input no. 0 for TURN_UP                @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_UP_2          0x00000200  /**< input no. 0 for TURN_UP_2              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_DOWN          0x00000400  /**< input no. 0 for TURN_DOWN              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_DOWN_2        0x00000800  /**< input no. 0 for TURN_DOWN_2            @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_FLASHER       0x00001000  /**< input no. 0 for TURN_FLASHER           @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_HIGHBEAM      0x00002000  /**< input no. 0 for TURN_HIGHBEAM          @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_CHECK         0x00004000  /**< input no. 0 for TURN_CHECK             @version 0x010B */
#define ASIM_MOCKUP_INPUT0_TURN_BC            0x00008000  /**< input no. 0 for TURN_BC                @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_BACK           0x00010000  /**< input no. 0 for ACC_BACK               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_BACK_2         0x00020000  /**< input no. 0 for ACC_BACK_2             @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_FWD            0x00040000  /**< input no. 0 for ACC_FWD                @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_FWD_2          0x00080000  /**< input no. 0 for ACC_FWD_2              @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_UP             0x00100000  /**< input no. 0 for ACC_UP                 @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_DOWN           0x00200000  /**< input no. 0 for ACC_DOWN               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_ACC_SET            0x00400000  /**< input no. 0 for ACC_SET                @version 0x010B */
#define ASIM_MOCKUP_INPUT0_HORN               0x00800000  /**< input no. 0 for HORN                   @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_INTERVAL     0x03000000  /**< input no. 0 for WIPER_INTERVAL         @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_INTERVAL_1   0x01000000  /**< input no. 0 for WIPER_INTERVAL_1       @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_INTERVAL_2   0x02000000  /**< input no. 0 for WIPER_INTERVAL_2       @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_INTERVAL_3   0x03000000  /**< input no. 0 for WIPER_INTERVAL_3       @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_AUTO         0x04000000  /**< input no. 0 for WIPER_AUTO             @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_BACK         0x08000000  /**< input no. 0 for WIPER_BACK             @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_UP           0x10000000  /**< input no. 0 for WIPER_UP               @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_UP_2         0x20000000  /**< input no. 0 for WIPER_UP_2             @version 0x010B */
#define ASIM_MOCKUP_INPUT0_WIPER_DOWN         0x40000000  /**< input no. 0 for WIPER_DOWN             @version 0x010B */
/** @} */

/** @addtogroup ASIM_MOCKUP_INPUT1
 *  ------ mockup input flags, part 2 ------
 *  @{
 */
/* INPUT: ZBE and GWS bits */
#define ASIM_MOCKUP_INPUT1_ZBE_COUNTER      0x0000FFFF   /**< input no. 1 for ZBE_COUNTER            @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_FWD          0x00010000   /**< input no. 1 for ZBE_FWD                @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_BACK         0x00020000   /**< input no. 1 for ZBE_BACK               @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_LEFT         0x00040000   /**< input no. 1 for ZBE_LEFT               @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_RIGHT        0x00080000   /**< input no. 1 for ZBE_RIGHT              @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_PRESS        0x00100000   /**< input no. 1 for ZBE_PRESS              @version 0x010B */
#define ASIM_MOCKUP_INPUT1_ZBE_MENU         0x00200000   /**< input no. 1 for ZBE_MENU               @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_P            0x00400000   /**< input no. 1 for GWS_P                  @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_LOCK         0x00800000   /**< input no. 1 for GWS_LOCK               @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_FWD          0x01000000   /**< input no. 1 for GWS_FWD                @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_FWD_2        0x02000000   /**< input no. 1 for GWS_FWD_2              @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_BACK         0x04000000   /**< input no. 1 for GWS_BACK               @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_BACK_2       0x08000000   /**< input no. 1 for GWS_BACK_2             @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_AUTO_N       0x10000000   /**< input no. 1 for GWS_AUTO_N             @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_MAN_N        0x20000000   /**< input no. 1 for GWS_MAN_N              @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_MAN_PLUS     0x40000000   /**< input no. 1 for GWS_MAN_PLUS           @version 0x010B */
#define ASIM_MOCKUP_INPUT1_GWS_MAN_MINUS    0x80000000   /**< input no. 1 for GWS_MAN_MINUS          @version 0x010B */
/** @} */

/** @addtogroup ASIM_MOCKUP_INPUT2
 *  ------ mockup input flags, part 3 ------
 *  @{
 */
#define ASIM_MOCKUP_INPUT2_LSZ_POTI              0x000000FF /**< input no. 2 for LSZ_POTI                 @version 0x010B */
#define ASIM_MOCKUP_INPUT2_LSZ_PARKING           0x00000100 /**< input no. 2 for LSZ_PARKING              @version 0x010B */
#define ASIM_MOCKUP_INPUT2_LSZ_DRIVING           0x00000200 /**< input no. 2 for LSZ_DRIVING              @version 0x010B */
#define ASIM_MOCKUP_INPUT2_LSZ_AUTO              0x00000300 /**< input no. 2 for LSZ_AUTO                 @version 0x010B */
#define ASIM_MOCKUP_INPUT2_LSZ_FOG_FRONT         0x00000400 /**< input no. 2 for LSZ_FOG_FRONT            @version 0x010B */
#define ASIM_MOCKUP_INPUT2_LSZ_FOG_REAR          0x00000800 /**< input no. 2 for LSZ_FOG_REAR             @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_DTC                0x00001000 /**< input no. 2 for DB_DTC                   @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_PDC                0x00002000 /**< input no. 2 for DB_PDC                   @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_SEAT_HEAT_L        0x00004000 /**< input no. 2 for DB_SEAT_HEAT_L           @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_SEAT_HEAT_R        0x00008000 /**< input no. 2 for DB_SEAT_HEAT_R           @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_STARTER            0x00010000 /**< input no. 2 for DB_STARTER               @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_HAZARD_LIGHTS      0x00020000 /**< input no. 2 for DB_HAZARD_LIGHTS         @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_LOCK               0x00040000 /**< input no. 2 for DB_LOCK                  @version 0x010B */

#define ASIM_MOCKUP_INPUT2_DB_STEER_ADJUST_FWD   0x00100000 /**< input no. 2 for DB_STEER_ADJUST_FWD      @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_STEER_ADJUST_BACK  0x00200000 /**< input no. 2 for DB_STEER_ADJUST_BACK     @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_STEER_ADJUST_UP    0x00400000 /**< input no. 2 for DB_STEER_ADJUST_UP       @version 0x010B */
#define ASIM_MOCKUP_INPUT2_DB_STEER_ADJUST_DOWN  0x00800000 /**< input no. 2 for DB_STEER_ADJUST_DOWN     @version 0x010B */
/** @} */

/** @addtogroup ASIM_DRIVER_PERCEPTION_FLAG
 *  ------ driver persecption flags ------
 *  @{
 */
#define ASIM_DRIVER_PERCEPTION_FLAG_NONE          0x00000000  /**< default                                                 @version 0x0100 */
#define ASIM_DRIVER_PERCEPTION_FLAG_TURN_L        0x00000001  /**< turn left at next intersection                          @version 0x0100 */
#define ASIM_DRIVER_PERCEPTION_FLAG_TURN_R        0x00000002  /**< turn right at next intersection                         @version 0x0100 */
/** @} */

/** @addtogroup ASIM_DRIVER_INPUT_VALIDITY
 *  ------ dynamics input flags ------
 *  @{
 */
#define ASIM_DRIVER_INPUT_VALIDITY_NONE            0x00000000 /**< default                                                @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_STEERING_WHEEL  0x00000001 /**< steering wheel is valid                                @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_STEERING_SPEED  0x00000002 /**< steering speed is valid                                @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_THROTTLE        0x00000004 /**< throttle is valid                                      @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_BRAKE           0x00000008 /**< brake is valid                                         @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_CLUTCH          0x00000010 /**< clutch is valid                                        @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_TGT_ACCEL       0x00000020 /**< target acceleration is valid                           @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_TGT_STEERING    0x00000040 /**< target steering is valid                               @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_GEAR            0x00000080 /**< gear selection is valid                                @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_CURVATURE       0x00000100 /**< curvature is valid for lateral control                 @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_STEERING_TORQUE 0x00000200 /**< torque at steering wheel is valid                      @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_ENGINE_TORQUE   0x00000400 /**< target torque of engine is valid                       @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_TGT_SPEED       0x00000800 /**< target speed is valid                                  @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_INFO_ONLY       0x00001000 /**< consider the values for info only                      @version 0x0100 */
#define ASIM_DRIVER_INPUT_VALIDITY_ADD_ON          0x00002000 /**< consider the values as an addOn for existing values    @version 0x0104 */
#define ASIM_DRIVER_INPUT_VALIDITY_FLAGS           0x00004000 /**< member "flags" of ASIM_DRIVER_CTRL_t is valid           @version 0x0107 */
#define ASIM_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT0   0x00008000 /**< member "mockupInput0" of ASIM_DRIVER_CTRL_t is valid    @version 0x010A */
#define ASIM_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT1   0x00010000 /**< member "mockupInput1" of ASIM_DRIVER_CTRL_t is valid    @version 0x010A */
#define ASIM_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT2   0x00020000 /**< member "mockupInput2" of ASIM_DRIVER_CTRL_t is valid    @version 0x010A */
#define ASIM_DRIVER_INPUT_VALIDITY_STEERING_TPOS   0x00040000 /**< interpret steeringTgt as t position                    @version 0x0119 */
#define ASIM_DRIVER_INPUT_VALIDITY_MODIFIED        0x00080000 /**< set if driver ctrl command is combination of original command and add_on command    @version 0x011a */
/** @} */


/** @addtogroup ASIM_SCORING_FLAG
 *  ------ arbitrary flags influencing the scoring ------
 *  @{
 */
#define ASIM_SCORING_FLAG_NONE                     0x00000000  /**< default                                                @version 0x0100 */
#define ASIM_SCORING_FLAG_COLLISION                0x00000001  /**< driver caused collision                                @version 0x0100 */
#define ASIM_SCORING_FLAG_OFF_ROAD                 0x00000002  /**< driver went off road                                   @version 0x0100 */
/** @} */

/** @addtogroup ASIM_COORD_FLAG
 *  ------ co-ordinate flags ------
 *  @{
 */
#define ASIM_COORD_FLAG_NONE                       0x00        /**< co-ordinate has no flags (state unknown or invalid)    @version 0x0100 */
#define ASIM_COORD_FLAG_POINT_VALID                0x01        /**< point co-ordinate is valid                             @version 0x0100 */
#define ASIM_COORD_FLAG_ANGLES_VALID               0x02        /**< angles are valid                                       @version 0x0100 */
/** @} */

/** @addtogroup ASIM_LIGHT_SOURCE_FLAG
 *  ------ light source flags ------
 *  @{
 */
#define ASIM_LIGHT_SOURCE_FLAG_NONE                0x0000      /**< light source has no flags (state unknown)                  @version 0x0100 */
#define ASIM_LIGHT_SOURCE_FLAG_USE_FRUSTUM         0x0001      /**< use frustum information of light source                    @version 0x0100 */
#define ASIM_LIGHT_SOURCE_FLAG_PERSISTENT          0x0002      /**< keep the light source even after initialization            @version 0x0100 */
#define ASIM_LIGHT_SOURCE_FLAG_STENCIL             0x0004      /**< use this definition for the stencil mask of a light source @version 0x010C */
/** @} */

/** @addtogroup ASIM_SENSOR_OBJECT_FLAG
 *  ------ sensor object flags ------
 *  @{
 */
#define ASIM_SENSOR_OBJECT_FLAG_NONE               0x0000      /**< object has no flags                                    @version 0x0100 */
#define ASIM_SENSOR_OBJECT_FLAG_CRITICALITY_LOW    0x0001      /**< criticality of object is low                           @version 0x0100 */
#define ASIM_SENSOR_OBJECT_FLAG_CRITICALITY_MEDIUM 0x0002      /**< criticality of object is medium                        @version 0x0100 */
#define ASIM_SENSOR_OBJECT_FLAG_CRITICALITY_HIGH   0x0003      /**< criticality of object is high                          @version 0x0100 */
#define ASIM_SENSOR_OBJECT_FLAG_LANE_POS_VALID     0x0008      /**< lane pos information is valid                          @version 0x011F */
/** @} */

/** @addtogroup ASIM_ROAD_EVENT
 *  ------ road events ------
 *  @{
 */
#define ASIM_ROAD_EVENT_NONE                       0x00000000  /**< no event is triggered                                  @version 0x0100 */
#define ASIM_ROAD_EVENT_POTHOLE                    0x00000001  /**< contact point is in a pothole                          @version 0x0100 */
/** @} */

/** @addtogroup ASIM_ENV_FLAG
 *  ------ road events ------
 *  @{
 */
#define ASIM_ENV_FLAG_NONE                         0x0000  /**< no environment flag is set                                  @version 0x0100 */
#define ASIM_ENV_FLAG_PRECIPITATION_SNOW           0x0001  /**< precipitation is snow, not rain                             @version 0x0100 */
#define ASIM_ENV_FLAG_PRECIPITATION_HAIL           0x0002  /**< precipitation is hail, not rain                             @version 0x0100 */
#define ASIM_ENV_FLAG_ROAD_SURFACE_WET             0x0004  /**< wet road surface                                            @version 0x0100 */
#define ASIM_ENV_FLAG_STREET_LAMPS                 0x0008  /**< street lamps are ON                                         @version 0x0102 */
/** @} */

/** @addtogroup ASIM_SHM_ID
 *  ------ shared memory identifiers ------
 *  @{
 */
#define ASIM_SHM_ID_IMG_GENERATOR_OUT              0x0816a   /**< shared memory key of image generator                      @version 0x0100 */
#define ASIM_SHM_ID_IMG_GENERATOR_IN               0x0817a   /**< shared memory key for light maps                          @version 0x0100 */
#define ASIM_SHM_ID_CONTROL_GENERATOR_IN           0x0817b   /**< shared memory key commands                                @version 0x010E */
#define ASIM_SHM_ID_CUSTOM_01                      0x0818a   /**< shared memory key of custom data block                    @version 0x0100 */
#define ASIM_SHM_ID_TC_IN                          0x08200   /**< shared memory key of taskControl input                    @version 0x010F */
#define ASIM_SHM_ID_TC_OUT                         0x08201   /**< shared memory key of taskControl output                   @version 0x010F */
#define ASIM_SHM_ID_DYN_2_STEER                    0x08210   /**< shared memory key of dynamics to steering                 @version 0x0111 */
#define ASIM_SHM_ID_STEER_2_DYN                    0x08211   /**< shared memory key of steering to dynamics                 @version 0x0111 */
/** @} */

/** @addtogroup ASIM_SHM_BUFFER_FLAG
 *  ------ shared memory identifiers ------
 *  @{
 */
#define ASIM_SHM_BUFFER_FLAG_NONE                    0x00000000      /**< no bits set, buffer may be overwritten            @version 0x0100 */
#define ASIM_SHM_BUFFER_FLAG_LOCK                    0x00000001      /**< buffer is locked by producer                      @version 0x0100 */
#define ASIM_SHM_BUFFER_FLAG_TC                      0x00000002      /**< buffer is to be processed by TC                   @version 0x0100 */
#define ASIM_SHM_BUFFER_FLAG_IG                      0x00000004      /**< buffer is to be processed by IG                   @version 0x0100 */
/** @} */

/** @addtogroup ASIM_OBJECT_CFG_FLAG
 *  ------ object configuration flags ------
 *  @{
 */
#define ASIM_OBJECT_CFG_FLAG_NONE                  0x0000 /**< no configuration flag set                                             @version 0x0100 */
#define ASIM_OBJECT_CFG_FLAG_CTRL_EXTERN           0x0001 /**< object is controlled externally                                       @version 0x0100 */
#define ASIM_OBJECT_CFG_FLAG_MODEL_ID_VALID        0x0002 /**< model ID given in object state message is valid                       @version 0x0119 */
#define ASIM_OBJECT_CFG_FLAG_FOREIGNER             0x0004 /**< model is cotrolled by another simulation                              @version 0x011F */
#define ASIM_OBJECT_CFG_FLAG_AUTO_SCALE            0x0008 /**< automatically scale player according to dimensions in objec state     @version 0x011F */
/** @} */

/** @addtogroup ASIM_ROAD_POS_FLAG
 *  ------ road position flags ------
 *  @{
 */
#define ASIM_ROAD_POS_FLAG_NONE                    0x00 /**< no flag set                                                 @version 0x0100 */
#define ASIM_ROAD_POS_FLAG_DIR_FWD                 0x01 /**< player orientation is in forward road direction             @version 0x0100 */
#define ASIM_ROAD_POS_FLAG_DIR_REAR                0x02 /**< player orientation is in rearward road direction            @version 0x0100 */
#define ASIM_ROAD_POS_FLAG_OFFROAD                 0x04 /**< player is considered "offroad", i.e. not on a driving lane  @version 0x011B */
/** @} */

/** @addtogroup ASIM_CONTACT_POINT_FLAG
 *  ------ contact point flags ------
 *  @{
 */
#define ASIM_CONTACT_POINT_FLAG_NONE                0x0000      /**< contact point has no flags (state unknown)             @version 0x0102 */
#define ASIM_CONTACT_POINT_FLAG_PLAYER_VALID        0x0001      /**< player ID within CP structure is valid                 @version 0x0102 */
/** @} */

/** @addtogroup ASIM_SYNC_CMD
 *  ------ commands distributed with sync messages ------
 *  @{
 */
#define ASIM_SYNC_CMD_RENDER_CONTINUOUS          0x00000080      /**< target will render as usual                            @version 0x010E */
#define ASIM_SYNC_CMD_RENDER_PAUSE               0x00000100      /**< target will pause rendering completely                 @version 0x010E */
#define ASIM_SYNC_CMD_RENDER_SINGLE_FRAME        0x00000200      /**< target will render a single frame and pause then       @version 0x010E */
#define ASIM_SYNC_CMD_RENDER_TARGET_FRAME        0x00000400      /**< target will render a specific frame and pause then     @version 0x011E */
/** @} */

/** @addtogroup ASIM_TRAJECTORY_FLAG
 *  ------ details about a trajectory definiton  ------
 *  @{
 */
#define ASIM_TRAJECTORY_FLAG_NONE                0x0000          /**< no special settings                                    @version 0x0110 */
#define ASIM_TRAJECTORY_FLAG_TIME_DOMAIN         0x0001          /**< trajectory is in time domain                           @version 0x0110 */
/** @} */

/** @addtogroup ASIM_DYN_2_STEER_STATE
 *  ------ dynamics model state ------
 *  @{
 */
#define ASIM_DYN_2_STEER_STATE_NONE                  0x0000          /**< no bits set, STOP or not connected                     @version 0x0100 */
#define ASIM_DYN_2_STEER_STATE_PAUSE                 0x0001          /**< PAUSE                                                  @version 0x0100 */
#define ASIM_DYN_2_STEER_STATE_RUN                   0x0002          /**< RUN                                                    @version 0x0100 */
#define ASIM_DYN_2_STEER_STATE_ERROR                 0x0004          /**< ERROR                                                  @version 0x0100 */
/** @} */


/** @addtogroup ASIM_DYN_2_STEER_CMD
 *  ------ commands to the steering device ------
 *  @{
 */
#define ASIM_DYN_2_STEER_CMD_NONE                    0x0000          /**< no bits set, no command                                @version 0x0100 */
#define ASIM_DYN_2_STEER_CMD_RESET                   0x0001          /**< RESET steering device                                  @version 0x0100 */
/** @} */


/** @addtogroup ASIM_DYN_2_STEER_EFFECTS
 *  ------ steering device state ------
 *  @{
 */
#define ASIM_DYN_2_STEER_EFFECT_NONE                 0x00000000      /**< no bits set, no effect active                          @version 0x0100 */
#define ASIM_DYN_2_STEER_EFFECT_TIRE_MODEL           0x00000001      /**< steering device calculates own tire model              @version 0x0100 */
#define ASIM_DYN_2_STEER_EFFECT_VIBRATION_10HZ       0x00000002      /**< steering device is initializing                        @version 0x0100 */
/** @} */

/** @addtogroup ASIM_STEER_2_DYN_STATE
 *  ------ steering device state ------
 *  @{
 */
#define ASIM_STEER_2_DYN_STATE_OFF                   0x00000000      /**< no bits set, steering not connected or OFF     @version 0x0100 */
#define ASIM_STEER_2_DYN_STATE_INIT                  0x00000001      /**< steering device is initializing                @version 0x0100 */
#define ASIM_STEER_2_DYN_STATE_FAIL                  0x00000002      /**< steering device is failed                      @version 0x0100 */
#define ASIM_STEER_2_DYN_STATE_RUN                   0x00000004      /**< steering device is running                     @version 0x0100 */
#define ASIM_STEER_2_DYN_STATE_OVER_LIMITS           0x00000008      /**< input values out of limits                     @version 0x0100 */
/** @} */

/** @addtogroup ASIM_WHEEL_FLAG
 *  ------ wheel status flags ------
 *  @{
 */
#define ASIM_WHEEL_FLAG_NONE                         0x0000          /**< no bits set,                                   @version 0x0114 */
#define ASIM_WHEEL_FLAG_ON_ROADMARK                  0x0001          /**< wheel is on road mark                          @version 0x0114 */
/** @} */

/** @addtogroup ASIM_MOTION_SYSTEM_FLAG
 *  ------ commands distributed with sync messages ------
 *  @{
 */
#define ASIM_MOTION_SYSTEM_FLAG_NONE             0x0000          /**< no special settings                                    @version 0x0116 */
#define ASIM_MOTION_SYSTEM_FLAG_ACTIVE           0x0001          /**< motion system is active (ON)                           @version 0x0116 */
#define ASIM_MOTION_SYSTEM_FLAG_ERROR            0x0002          /**< motion system has errors                               @version 0x0116 */
/** @} */

/** @addtogroup ASIM_CUSTOM_TRACK_CTRL_FLAG
 *  ------ commands distributed with sync messages ------
 *  @{
 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_A  0x0001  /**< object is visible in sensor A                                   @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_B  0x0002  /**< object is visible in sensor B                                   @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_VIS_GFX       0x0004  /**< object is visible in Ig                                         @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_C  0x0008  /**< object is visible in sensor C                                   @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_D  0x0010  /**< object is visible in sensor D                                   @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_NAME_BY_ID    0x0100  /**< model name  is derived from ID and model is addressed via name  @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_PLAYER_ACTIVE 0x0200  /**< if set, player is active                                        @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_FLAG_DIRECT_MODE   0x0400  /**< if set, player is active                                        @version 0x0119 */
/** @} */

/** @addtogroup ASIM_CUSTOM_TRACK_CTRL_VALIDITY
 *  ------ dynamics input flags ------
 *  @{
 */
#define ASIM_CUSTOM_TRACK_CTRL_VALIDITY_DEFAULT         0x00000000 /**< default                                                @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_VALIDITY_TGT_ACCEL       0x00000001 /**< target acceleration is valid                           @version 0x0119 */
#define ASIM_CUSTOM_TRACK_CTRL_VALIDITY_STEERING_TPOS   0x00000002 /**< t-pos is valid                                         @version 0x0119 */
/** @} */

/** @addtogroup ASIM_ROAD_QUERY_FLAG
 *  ------ dynamics input flags ------
 *  @{
 */
#define ASIM_ROAD_QUERY_FLAG_NONE                       0x0000 /**< default                                                @version 0x011D */
#define ASIM_ROAD_QUERY_FLAG_RELATIVE_POS               0x0001 /**< use relative positioning                               @version 0x011D */
/** @} */

/** @} --END GROUP BITMASK_DEFINITIONS-- */

/** ------ generic point structure --- */
typedef struct
{
    double x;         /**< x position                                                @unit m                                @version 0x0100 */
    double y;         /**< y position                                                @unit m                                @version 0x0100 */
    double z;         /**< z position                                                @unit m                                @version 0x0100 */
    uint8_t  flags;   /**< co-ordinate flags                                         @unit @link ASIM_COORD_FLAG @endlink    @version 0x0100 */
    uint8_t  type;    /**< co-ordinate system type identifier                        @unit @link ASIM_COORD_TYPE @endlink    @version 0x0100 */
    uint16_t system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */
} ASIM_POINT_t;

/** ------ generic co-ordinate structure --- */
typedef struct
{
    double   x;       /**< x position                                                @unit m                                @version 0x0100 */
    double   y;       /**< y position                                                @unit m                                @version 0x0100 */
    double   z;       /**< z position                                                @unit m                                @version 0x0100 */
    float    h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
    float    p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
    float    r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
    uint8_t  flags;   /**< co-ordinate flags                                         @unit @link ASIM_COORD_FLAG @endlink    @version 0x0100 */
    uint8_t  type;    /**< co-ordinate system type identifier                        @unit @link ASIM_COORD_TYPE @endlink    @version 0x0100 */
    uint16_t system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */
} ASIM_COORD_t;

/** ------ definition / position of a user co-ordinate system --- */
typedef struct
{
    uint16_t     id;                     /**< unique ID of the co-ordinate system                                    @unit _                    @version 0x0100 */
    uint16_t     spare;                  /**< spare for future use                                                   @unit _                    @version 0x0100 */
    ASIM_COORD_t  pos;                    /**< origin and orientation of x axis of the co-ordinate system             @unit m,m,m,rad,rad,rad    @version 0x0100 */
} ASIM_COORD_SYSTEM_t;

/** ------ road position and associated properties ------ */
typedef struct
{
    uint32_t         playerId;           /**< id of the player to which road position belongs                        @unit _                                @version 0x0100 */
    uint16_t         spare0;             /**< for future use                                                         @unit _                                @version 0x010A */
    int8_t           laneId;             /**< lane ID                                                                @unit _                                @version 0x0100 */
    uint8_t          flags;              /**< road position flags, further info                                      @unit @link ASIM_ROAD_POS_FLAG @endlink @version 0x0100 */
    uint64_t         roadId;             /**< unique road ID                                                         @unit _                                @version 0x0100 */
    float            roadS;              /**< s-coordinate along road's reference line                               @unit m                                @version 0x0100 */
    float            roadT;              /**< t-coordinate perpendicular to road's reference line                    @unit m                                @version 0x0100 */
    float            laneOffset;         /**< offset from lane center in road co-ordinates                           @unit m                                @version 0x0100 */
    float            hdgRel;             /**< heading angle relative to lane tangent dir                             @unit rad                              @version 0x0100 */
    float            pitchRel;           /**< pitch angle relative to road tangent plane                             @unit rad                              @version 0x0100 */
    float            rollRel;            /**< roll angle relative to road tangent plane                              @unit rad                              @version 0x0100 */
    uint8_t          roadType;           /**< type of the road, corresponding to OpenDRIVE                           @unit @link ASIM_ROAD_TYPE @endlink     @version 0x010A */
    uint8_t          spare1;             /**< for future use                                                         @unit _                                @version 0x010A */
    uint16_t         spare2;             /**< for future use                                                         @unit _                                @version 0x010A */
    float            pathS;              /**< longitudinal path co-ordinate                                          @unit _                                @version 0x010E */
} ASIM_ROAD_POS_t;

/** ------ road mark information ------
 * @note this package is immediately followed by "noDataPoints" entries of type ASIM_POINT_t
 */
typedef struct
{
    uint32_t    playerId;                /**< id of the player to which roadmark belongs                             @unit _                                    @version 0x0100 */
    int8_t      id;                      /**< id of this road mark                                                   @unit [0..127]                             @version 0x010D */
    int8_t      prevId;                  /**< id of predecessor                                                      @unit [-1, 0..127]                         @version 0x010D */
    int8_t      nextId;                  /**< id of successor                                                        @unit [-1, 0..127]                         @version 0x010D */
    int8_t      laneId;                  /**< id of the lane to which the roadmark belongs                           @unit _                                    @version 0x011a */
    float       lateralDist;             /**< lateral distance to vehicle ref. point and dir                         @unit m                                    @version 0x0100 */
    float       yawRel;                  /**< yaw angle relative to vehicle dir                                      @unit rad [-PI;PI]                         @version 0x0100 */
    double      curvHor;                 /**< horizontal curvature                                                   @unit 1/m                                  @version 0x0100 */
    double      curvHorDot;              /**< change of horizontal curvature                                         @unit 1/m2                                 @version 0x0100 */
    float       startDx;                 /**< start of road mark in driving dir                                      @unit m                                    @version 0x0100 */
    float       previewDx;               /**< distance of last valid measurement                                     @unit m                                    @version 0x0100 */
    float       width;                   /**< width of road mark                                                     @unit m                                    @version 0x0100 */
    float       height;                  /**< height of road mark                                                    @unit m                                    @version 0x0100 */
    double      curvVert;                /**< vertical curvature                                                     @unit 1/m                                  @version 0x0100 */
    double      curvVertDot;             /**< change of vertical curvature                                           @unit 1/m2                                 @version 0x0100 */
    uint8_t     type;                    /**< type of road mark                                                      @unit @link ASIM_ROADMARK_TYPE  @endlink    @version 0x0100 */
    uint8_t     color;                   /**< color of road mark                                                     @unit @link ASIM_ROADMARK_COLOR @endlink    @version 0x0100 */
    uint16_t    noDataPoints;            /**< number of tesselation points following this package                    @unit _                                    @version 0x0100 */
    uint64_t    roadId;                  /**< id of the road to which the roadmark belongs                           @unit _                                    @version 0x011a */
    uint32_t    spare1;                  /**< for future use                                                         @unit _                                    @version 0x0100 */
} ASIM_ROADMARK_t;

/** ------ lane information ------ */
typedef struct
{
    uint64_t    roadId;                  /**< unique road ID                                                         @unit _                                @version 0x0100 */
    uint16_t    spare0;                  /**< for future use                                                         @unit _                                @version 0x0100 */
    int8_t      id;                      /**< lane ID according to OpenDRIVE                                         @unit [-127..127]                      @version 0x0100 */
    uint8_t     neighborMask;            /**< existence mask for adjacent lanes                                      @unit @link ASIM_LANE_EXISTS @endlink   @version 0x0100 */
    int8_t      leftLaneId;              /**< ID of lane left of current lane                                        @unit [-127..127]                      @version 0x0100 */
    int8_t      rightLaneId;             /**< ID of lane right of current lane                                       @unit [-127..127]                      @version 0x0100 */
    uint8_t     borderType;              /**< type of lane border                                                    @unit @link ASIM_LANE_BORDER @endlink   @version 0x0100 */
    uint8_t     material;                /**< type of lane material                                                  @unit [0..255]                         @version 0x0100 */
    uint16_t    status;                  /**< status mask of lane                                                    @unit @link ASIM_LANE_STATUS @endlink   @version 0x0100 */
    uint16_t    type;                    /**< enumerated lane type according to OpenDRIVE (0=none, 1=driving...)     @unit _                                @version 0x010D */
    float       width;                   /**< lane width                                                             @unit m                                @version 0x0100 */
    double      curvVert;                /**< vertical curvature in lane center                                      @unit 1/m                              @version 0x0100 */
    double      curvVertDot;             /**< change of vertical curvature in lane center                            @unit 1/m2                             @version 0x0100 */
    double      curvHor;                 /**< horizontal curvature in lane center                                    @unit 1/m                              @version 0x0100 */
    double      curvHorDot;              /**< change of horizontal curvature in lane center                          @unit 1/m2                             @version 0x0100 */
    uint32_t    playerId;                /**< id of the player to which this info belongs                            @unit _                                @version 0x0100 */
    uint32_t    spare1;                  /**< for future use                                                         @unit _                                @version 0x0100 */
} ASIM_LANE_INFO_t;

/** ------ configuration of an object (sent at start of sim and when triggered via SCP) ------ */
typedef struct
{
    uint32_t id;                                    /**< unique object ID                                              @unit _                                  @version 0x0100 */
    uint8_t  category;                              /**< object category                                               @unit @link ASIM_OBJECT_CATEGORY @endlink @version 0x0100 */
    uint8_t  type;                                  /**< object type                                                   @unit @link ASIM_OBJECT_TYPE     @endlink @version 0x0100 */
    int16_t  modelId;                               /**< visual model ID                                               @unit _                                  @version 0x0100 */
    char     name[ASIM_SIZE_OBJECT_NAME];            /**< symbolic name                                                 @unit _                                  @version 0x0100 */
    char     modelName[ASIM_SIZE_OBJECT_NAME];       /**< model name associated to an object                            @unit _                                  @version 0x0100 */
    char     fileName[ASIM_SIZE_FILENAME];           /**< filename associated to an object                              @unit _                                  @version 0x0100 */
    uint16_t flags;                                 /**< object configuration flags                                    @unit @link ASIM_OBJECT_CFG_FLAG @endlink @version 0x0100 */
    uint16_t spare0;                                /**< reserved for future use                                       @unit _                                  @version 0x0100 */
    uint32_t spare1;                                /**< reserved for future use                                       @unit _                                  @version 0x0100 */
} ASIM_OBJECT_CFG_t;

/** ------ geometry information for an object --- */
typedef struct
{
    float dimX;        /**< x dimension in object co-ordinates (length)                                               @unit m                                  @version 0x0100 */
    float dimY;        /**< y dimension in object co-ordinates (width)                                                @unit m                                  @version 0x0100 */
    float dimZ;        /**< z dimension in object co-ordinates (height)                                               @unit m                                  @version 0x0100 */
    float offX;        /**< x distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
    float offY;        /**< y distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
    float offZ;        /**< z distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
} ASIM_GEOMETRY_t;

/** ------ state of an object (may be extended by the next structure) ------- */
typedef struct
{
    uint32_t            id;                         /**< unique object ID                                              @unit _                                  @version 0x0100 */
    uint8_t             category;                   /**< object category                                               @unit @link ASIM_OBJECT_CATEGORY @endlink @version 0x0100 */
    uint8_t             type;                       /**< object type                                                   @unit @link ASIM_OBJECT_TYPE     @endlink @version 0x0100 */
    uint16_t            visMask;                    /**< visibility mask                                               @unit @link ASIM_OBJECT_VIS_FLAG @endlink @version 0x0100 */
    char                name[ASIM_SIZE_OBJECT_NAME]; /**< symbolic name                                                 @unit _                                  @version 0x0100 */
    ASIM_GEOMETRY_t      geo;                        /**< info about object's geometry                                  @unit m,m,m,m,m,m                        @version 0x0100 */
    ASIM_COORD_t         pos;                        /**< position and orientation of object's reference point          @unit m,m,m,rad,rad,rad                  @version 0x0100 */
    uint64_t            parent;                     /**< unique ID of parent object                                    @unit _                                  @version 0x0100 */
    uint16_t            cfgFlags;                   /**< configuration flags                                           @unit @link ASIM_OBJECT_CFG_FLAG @endlink @version 0x0100 */
    int16_t             cfgModelId;                 /**< visual model ID (configuration parameter)                     @unit _                                  @version 0x0100 */
    int8_t              laneId;
    uint8_t             dir;
    uint16_t            spare0;
    uint64_t            roadId;
    float               roadS;
    float               roadT;
    float               hdgRel;
    float               pitchRel;
    float               rollRel;
} ASIM_OBJECT_STATE_BASE_t;

/** ------ extended object data (e.g. for dynamic objects) ------- */
typedef struct
{
    ASIM_COORD_t         speed;                      /**< speed and rates                                               @unit m/s,m/s,m/s,rad/s,rad/s,rad/s          @version 0x0100 */
    ASIM_COORD_t         accel;                      /**< acceleration                                                  @unit m/s2,m/s2,m/s2,rad/s2,rad/s2/rad/s2    @version 0x0100 */
    float               traveledDist;               /**< traveled distance                                             @unit m                                      @version 0x011a */
    uint32_t            spare[4];                   /**< reserved for future use                                       @unit _                                      @version 0x0100 */
} ASIM_OBJECT_STATE_EXT_t;

/** ------ complete object data (basic and extended info) ------- */
typedef struct
{
    ASIM_OBJECT_STATE_BASE_t base;           /**< state of an object     @unit ASIM_OBJECT_STATE_BASE_t   @version 0x0100 */
    ASIM_OBJECT_STATE_EXT_t  ext;            /**< extended object data   @unit ASIM_OBJECT_STATE_EXT_t    @version 0x0100 */
} ASIM_OBJECT_STATE_t;

/** ------ standard engine information ------ */
typedef struct
{
    uint32_t playerId;                    /**< unique ID of the player                          @unit _                         @version 0x0100 */
    float    rps;                         /**< current rotation speed                           @unit 1/s                       @version 0x0100 */
    float    load;                        /**< engine load (throttle position)                  @unit [0.0..1.0]                @version 0x0100 */
    uint32_t spare1[2];                   /**< reserved for future use                          @unit _                         @version 0x0100 */
} ASIM_ENGINE_BASE_t;

/** ------ extension of standard engine information ------ */
typedef struct
{
    float    rpsStart;                    /**< start speed                                      @unit 1/s                       @version 0x0100 */
    float    torque;                      /**< torque                                           @unit Nm                        @version 0x0100 */
    float    torqueInner;                 /**< inner torque                                     @unit Nm                        @version 0x0100 */
    float    torqueMax;                   /**< maximum torque                                   @unit Nm                        @version 0x0100 */
    float    torqueFriction;              /**< friction torque                                  @unit Nm                        @version 0x0100 */
    float    fuelCurrent;                 /**< current fuel consumption                         @unit l/100km                   @version 0x0100 */
    float    fuelAverage;                 /**< average fuel consumption                         @unit l/100km                   @version 0x0100 */
    float    oilTemperature;              /**< oil temperature                                  @unit deg                       @version 0x0119 */
    float    temperature;                 /**< engine core temperature                          @unit deg                       @version 0x0119 */
} ASIM_ENGINE_EXT_t;

/** ------ complete engine data (basic and extended info) ------- */
typedef struct
{
    ASIM_ENGINE_BASE_t base;             /**< standard engine information                @unit ASIM_ENGINE_BASE_t @version 0x0100 */
    ASIM_ENGINE_EXT_t  ext;              /**< extension of standard engine information   @unit ASIM_ENGINE_EXT_t  @version 0x0100 */
} ASIM_ENGINE_t;

/** ------ standard drivetrain information ------ */
typedef struct
{
    uint32_t playerId;                    /**< unique ID of the player                          @unit _                                     @version 0x0100 */
    uint8_t  gearBoxType;                 /**< type of gear box                                 @unit @link ASIM_GEAR_BOX_TYPE   @endlink    @version 0x0100 */
    uint8_t  driveTrainType;              /**< type of drivetrain                               @unit @link ASIM_DRIVETRAIN_TYPE @endlink    @version 0x0100 */
    uint8_t  gear;                        /**< current gear position                            @unit @link ASIM_GEAR_BOX_POS    @endlink    @version 0x0100 */
    uint8_t  spare0;                      /**< reserved for future use                          @unit _                                     @version 0x0100 */
    uint32_t spare1[2];                   /**< reserved for future use                          @unit _                                     @version 0x0100 */
} ASIM_DRIVETRAIN_BASE_t;

/** ------ extension of standard drivetrain information ------ */
typedef struct
{
    float    torqueGearBoxIn;             /**< torque at entry of gearbox                       @unit Nm                        @version 0x0100 */
    float    torqueCenterDiffOut;         /**< torque at exit of center differential            @unit Nm                        @version 0x0100 */
    float    torqueShaft;                 /**< torque at shaft                                  @unit Nm                        @version 0x0100 */
    uint32_t spare1[2];                   /**< reserved for future use                          @unit _                         @version 0x0100 */
} ASIM_DRIVETRAIN_EXT_t;

/** ------ complete engine data (basic and extended info) ------- */
typedef struct
{
    ASIM_DRIVETRAIN_BASE_t base;             /**< standard drivetrain information                @unit ASIM_DRIVETRAIN_BASE_t @version 0x0100 */
    ASIM_DRIVETRAIN_EXT_t  ext;              /**< extension of standard drivetrain information   @unit ASIM_DRIVETRAIN_EXT_t  @version 0x0100 */
} ASIM_DRIVETRAIN_t;

/** ------ standard wheel information ------ */
typedef struct
{
    uint32_t playerId;                    /**< ID of the player to which the wheel belongs      @unit _                             @version 0x0100 */
    uint8_t  id;                          /**< ID of the wheel within the player                @unit @link ASIM_WHEEL_ID @endlink   @version 0x0100 */
    uint8_t  flags;                       /**< wheel status flags (e.g. for sound )             @unit @link ASIM_WHEEL_FLAG @endlink @version 0x0114 */
    uint8_t  spare0[2];                   /**< reserved for future use                          @unit _                             @version 0x0100 */
    float    radiusStatic;                /**< static tire radius                               @unit m                             @version 0x0100 */
    float    springCompression;           /**< compression of spring                            @unit m                             @version 0x0100 */
    float    rotAngle;                    /**< angle of rotation                                @unit rad                           @version 0x0100 */
    float    slip;                        /**< slip factor [0.0..1.0]                           @unit _                             @version 0x0100 */
    float    steeringAngle;               /**< steering angle                                   @unit rad                           @version 0x0100 */
    uint32_t spare1[4];                   /**< reserved for future use                          @unit _                             @version 0x0100 */
} ASIM_WHEEL_BASE_t;

/** ------ extension of standard wheel information ------ */
typedef struct
{
    float    vAngular;                    /**< angular velocity                                 @unit rad/s                     @version 0x0100 */
    float    forceZ;                      /**< wheel contact force                              @unit N                         @version 0x0100 */
    float    forceLat;                    /**< lateral force                                    @unit N                         @version 0x0100 */
    float    forceLong;                   /**< longitudinal force                               @unit N                         @version 0x0100 */
    float    forceTireWheelXYZ[3];        /**< force of tire on wheel                           @unit N                         @version 0x0100 */
    float    radiusDynamic;               /**< dynamic tire radius                              @unit m                         @version 0x0100 */
    float    brakePressure;               /**< brake pressure at wheel                          @unit Pa                        @version 0x0100 */
    float    torqueDriveShaft;            /**< torque at drive shaft                            @unit Nm                        @version 0x0100 */
    float    damperSpeed;                 /**< speed of damper                                  @unit m/s                       @version 0x0100 */
    uint32_t spare2[4];                   /**< reserved for future use                          @unit _                         @version 0x0100 */
} ASIM_WHEEL_EXT_t;

/** ------ complete wheel data (basic and extended info) ------- */
typedef struct
{
    ASIM_WHEEL_BASE_t base;              /**< standard wheel information                 @unit ASIM_WHEEL_BASE_t  @version 0x0100 */
    ASIM_WHEEL_EXT_t  ext;               /**< extension of standard wheel information    @unit ASIM_WHEEL_EXT_t   @version 0x0100 */
} ASIM_WHEEL_t;

/** ------ vehicle system information ------ */
typedef struct
{
    uint32_t playerId;                /**< ID of the player to which the data belongs                               @unit _                                        @version 0x0100 */
    uint32_t lightMask;               /**< mask of active light systems                                             @unit @link ASIM_VEHICLE_LIGHT @endlink         @version 0x0100 */
    float    steering;                /**< front wheel steering angle (NOT: steering wheel angle)                   @unit rad                                      @version 0x0100 */
    float    steeringWheelTorque;     /**< torque at the steering wheel                                             @unit Nm                                       @version 0x0100 */
    uint8_t  accMask;                 /**< acc state mask                                                           @unit @link ASIM_VEHICLE_ACC_FLAG @endlink      @version 0x010A */
    uint8_t  accSpeed;                /**< acc speed indication                                                     @unit km/h [0..255]                            @version 0x010A */
    uint8_t  batteryState;            /**< battery charge state                                                     @unit [0..255]                                 @version 0x010A */
    int8_t   batteryRate;             /**< battery discharge / charge rate                                          @unit [-127..127]                              @version 0x010A */
    uint16_t displayLightMask;        /**< lightmask for driver display (16 lights)                                 @unit @link ASIM_VEHICLE_DISPLAY_LIGHT @endlink @version 0x010A */
    uint16_t fuelGauge;               /**< fuel gauge [0.0..1.0]                                                    @unit [0..65535] = [0.0..1.0]                  @version 0x0119 */
    uint32_t spare[5];                /**< spares for future use                                                    @unit _                                        @version 0x0100 */
} ASIM_VEHICLE_SYSTEMS_t;

/** ------ vehicle setup information ------ */
typedef struct
{
    uint32_t playerId;       /**< ID of the player to which the data belongs                                       @unit _                     @version 0x0100 */
    float    mass;           /**< vehicle mass                                                                     @unit kg                    @version 0x0100 */
    float    wheelBase;      /**< wheel base                                                                       @unit m                     @version 0x0100 */
    int32_t  spare[4];       /**< for future use                                                                   @unit _                     @version 0x0100 */
} ASIM_VEHICLE_SETUP_t;

/** ------ image information ------
*   @note to be followed by actual image data
*/
typedef struct
{
    uint32_t id;                          /**< unique ID of the image (e.g. frame count)                            @unit _                             @version 0x0100 */
    uint16_t width;                       /**< width of the image                                                   @unit pixel                         @version 0x0100 */
    uint16_t height;                      /**< height of the image                                                  @unit pixel                         @version 0x0100 */
    uint8_t  pixelSize;                   /**< memory size of a pixel                                               @unit bit                           @version 0x0100 */
    uint8_t  pixelFormat;                 /**< format of a pixel                                                    @unit @link ASIM_PIX_FORMAT @endlink @version 0x0100 */
    uint16_t cameraId;                    /**< id of the camera which created the image (0=uninitialized)           @unit _                             @version 0x0115 */
    uint32_t imgSize;                     /**< total size of image                                                  @unit byte                          @version 0x0100 */
    uint8_t  color[4];                    /**< color for additional colorizing, if required                         @unit _                             @version 0x0100 */
    uint32_t spare1[3];                   /**< for future use                                                       @unit _                             @version 0x0100 */
} ASIM_IMAGE_t;

/** ------ custom light source information ------
*   @note to be followed by actual light source intensity data
*/
typedef struct
{
    uint16_t lightElementId;              /**< unique ID of the light element                                       @unit _                             @version 0x0119 */
    uint16_t width;                       /**< width of the light element control data                              @unit pixel                         @version 0x0119 */
    uint16_t height;                      /**< height of the light element control data                             @unit pixel                         @version 0x0119 */
    uint16_t spare0;                      /**< for future use                                                       @unit _                             @version 0x0119 */
    uint32_t dataSize;                    /**< size of intensity data                                               @unit byte                          @version 0x0119 */
    uint32_t spare1[3];                   /**< for future use                                                       @unit _                             @version 0x0119 */
} ASIM_CUSTOM_LIGHT_B_t;

/** ------ custom light source information for light groups ------
*/
typedef struct
{
    uint16_t lightElementId;              /**< unique ID of the light element                                       @unit _                             @version 0x011D */
    uint16_t groupId;                     /**< unique ID of the group within the light element                      @unit _                             @version 0x011D */
    float    intensity;                   /**< intensity scale for the whole group                                  @unit _                             @version 0x011D */
    float    hOffset;                     /**< heading offset of whole groups                                       @unit _                             @version 0x011D */
    float    pOffset;                     /**< pitch offset of whole groups                                         @unit _                             @version 0x011D */
    uint32_t spare[4];                    /**< for future use                                                       @unit _                             @version 0x011D */
} ASIM_CUSTOM_LIGHT_GROUP_B_t;


/** ------ arbitrary x/y function ------
*   @note to be followed by actual function points (each 2 or 3 doubles)
*/
typedef struct
{
    uint32_t id;                          /**< unique ID of the function                                            @unit _                                 @version 0x0100 */
    uint8_t  type;                        /**< type of the function                                                 @unit @link ASIM_FUNCTION_TYPE @endlink  @version 0x0100 */
    uint8_t  dimension;                   /**< dimension of the function (xy=2, xyz=3)                              @unit _                                 @version 0x0100 */
    uint16_t spare;                       /**< for future use                                                       @unit _                                 @version 0x0100 */
    uint32_t dataSize;                    /**< total size of following data                                         @unit byte                              @version 0x0100 */
    uint32_t spare1[4];                   /**< for future use                                                       @unit _                                 @version 0x0100 */
} ASIM_FUNCTION_t;

/** ------ sensor definition and state ------ */
typedef struct
{
    uint32_t    id;                          /**< id of the sensor                                      @unit _                                     @version 0x0100 */
    uint8_t     type;                        /**< type of the sensor                                    @unit @link ASIM_SENSOR_TYPE     @endlink    @version 0x0100 */
    uint8_t     hostCategory;                /**< category of the object hosting the sensor             @unit @link ASIM_OBJECT_CATEGORY @endlink    @version 0x0100 */
    uint16_t    spare0;                      /**< for future use                                        @unit _                                     @version 0x0100 */
    uint32_t    hostId;                      /**< unique id of the sensor's host                        @unit _                                     @version 0x0100 */
    char        name[ASIM_SIZE_OBJECT_NAME];  /**< name of the sensor                                    @unit _                                     @version 0x0100 */
    float       fovHV[2];                    /**< field-of-view (horizontal/vertical)                   @unit rad,rad                               @version 0x0100 */
    float       clipNF[2];                   /**< clipping ranges (near/far)                            @unit m,m                                   @version 0x0100 */
    ASIM_COORD_t pos;                         /**< position and orientation of sensor's reference point  @unit m,m,m,rad,rad,rad                     @version 0x0100 */
    ASIM_COORD_t originCoordSys;              /**< position and orientation of sensor's coord origin     @unit m,m,m,rad,rad,rad                     @version 0x0100 */
    float       fovOffHV[2];                 /**< field-of-view offset (horizontal/vertical)            @unit rad, rad                              @version 0x011B */
    int32_t     spare[2];                    /**< for future use                                        @unit _                                     @version 0x0100 */
} ASIM_SENSOR_STATE_t;

/** ------ information about an object registered within a sensor ------ */
typedef struct
{
    uint8_t     category;     /**< object category                                                                @unit @link ASIM_OBJECT_CATEGORY    @endlink  @version 0x0100 */
    uint8_t     type;         /**< object type                                                                    @unit @link ASIM_OBJECT_TYPE        @endlink  @version 0x0100 */
    uint16_t    flags;        /**< sensor object flags                                                            @unit @link ASIM_SENSOR_OBJECT_FLAG @endlink  @version 0x0100 */
    uint32_t    id;           /**< id of the object                                                               @unit _                                      @version 0x0100 */
    uint32_t    sensorId;     /**< id of the detecting sensor                                                     @unit _                                      @version 0x0100 */
    double      dist;         /**< distance between object and referring device                                   @unit m                                      @version 0x0100 */
    ASIM_COORD_t sensorPos;    /**< position and orientation of object in sensor coord                             @unit m,m,m,rad,rad,rad                      @version 0x0100 */
    int8_t      occlusion;    /**< degree of occlusion for viewer (-1 = not valid, 0..127 = 0..100% occlusion)    @unit [-1, 0..127]                           @version 0x0100 */
    int8_t      deltaLanePos; /**< for future use                                                                 @unit _                                      @version 0x011F */
    uint8_t     spare0[2];    /**< for future use                                                                 @unit _                                      @version 0x0100 */
    uint32_t    spare[3];     /**< for future use                                                                 @unit _                                      @version 0x0100 */
} ASIM_SENSOR_OBJECT_t;

/** ------ camera information ------ */
typedef struct
{
    uint16_t    id;                         /**< unique ID of the camera                                @unit _                        @version 0x0100 */
    uint16_t    width;                      /**< width of viewport                                      @unit pixel                    @version 0x0100 */
    uint16_t    height;                     /**< height of viewport                                     @unit pixel                    @version 0x0100 */
    uint16_t    spare0;                     /**< for future use                                         @unit _                        @version 0x0100 */
    float       clipNear;                   /**< near clipping plane                                    @unit m                        @version 0x0100 */
    float       clipFar;                    /**< far clipping plane                                     @unit m                        @version 0x0100 */
    float       focalX;                     /**< focal length in x direction                            @unit pixel                    @version 0x0100 */
    float       focalY;                     /**< focal length in y direction                            @unit pixel                    @version 0x0100 */
    float       principalX;                 /**< position of principal point in x direction             @unit pixel                    @version 0x0100 */
    float       principalY;                 /**< position of principal point in y direction             @unit pixel                    @version 0x0100 */
    ASIM_COORD_t pos;                        /**< position and orientation                               @unit m,m,m,rad,rad,rad        @version 0x0100 */
    uint32_t    spare1[4];                  /**< for future use                                         @unit _                        @version 0x0100 */
} ASIM_CAMERA_t;

/** ------ basic info about a light illuminating the scene ------ */
typedef struct
{
    uint16_t     id;                      /**< unique ID of the light source                                    @unit _                                     @version 0x0100 */
    int8_t       templateId;              /**< template definition of light source (-1 deletes light source)    @unit _                                     @version 0x0100 */
    uint8_t      state;                   /**< state of light source                                            @unit _                                     @version 0x0100 */
    int32_t      playerId;                /**< ID of the player to which light source shall be linked           @unit _                                     @version 0x0100 */
    ASIM_COORD_t  pos;                     /**< position and orientation of light source                         @unit m,m,m,rad,rad,rad                     @version 0x0100 */
    uint16_t     flags;                   /**< additional flags                                                 @unit @link ASIM_LIGHT_SOURCE_FLAG @endlink  @version 0x0100 */
    uint16_t     spare0;                  /**< just another spare                                               @unit _                                     @version 0x0100 */
    int32_t      spare1[2];               /**< yet another spare                                                @unit _                                     @version 0x0100 */
} ASIM_LIGHT_SOURCE_BASE_t;

/** ------ extended info about a light illuminating the scene ------ */
typedef struct
{
    float        nearFar[2];              /**< near and far clip of light soure                                   @unit m,m                          @version 0x0100 */
    float        frustumLRBT[4];          /**< frustum left / right / bottom / top                                @unit m,m,m,m                      @version 0x0100 */
    float        intensity[3];            /**< intensity of the light (ambient, diffuse, specular)                @unit _,_,_                        @version 0x0100 */
    float        atten[3];                /**< attenuation (constant, linear, quadratic)                          @unit _,_,_                        @version 0x0100 */
    int32_t      spare1[3];               /**< yet another spare                                                  @unit _                            @version 0x0100 */
} ASIM_LIGHT_SOURCE_EXT_t;

/** ------ complete light source data (basic and extended info) ------- */
typedef struct
{
    ASIM_LIGHT_SOURCE_BASE_t base;       /**< basic info about a light illuminating the scene    @unit ASIM_LIGHT_SOURCE_BASE_t   @version 0x0100 */
    ASIM_LIGHT_SOURCE_EXT_t  ext;        /**< extended info about a light illuminating the scene @unit ASIM_LIGHT_SOURCE_EXT_t    @version 0x0100 */
} ASIM_LIGHT_SOURCE_t;

/** ------ info about an arbitrary contact point ------ */
typedef struct
{
    uint16_t     id;             /**< unique ID of the contact point                                                                @unit _                                           @version 0x0100 */
    uint16_t     flags;          /**< various flags with contact point options                                                      @unit @link ASIM_CONTACT_POINT_FLAG @endlink       @version 0x0102 */
    ASIM_COORD_t  roadDataIn;     /**< inertial position of contact point; heading=0; pitch and roll relative to vehicle axis        @unit m,m,m,rad,rad,rad                           @version 0x0100 */
    float        friction;       /**< road friction at contact point                                                                @unit _                                           @version 0x0100 */
    int32_t      playerId;       /**< ID of the player to which CP belongs; only valid if corresponding flag is set                 @unit _                                           @version 0x0102 */
    int32_t      spare1;         /**< just another spare                                                                            @unit _                                           @version 0x0100 */
} ASIM_CONTACT_POINT_t;

/** ------ signal / sign info for a given vehicle ------ */
typedef struct
{
    uint32_t     id;              /**< ID of the signal                                                                     @unit _                                           @version 0x0100 */
    uint32_t     playerId;        /**< ID of the player who "detected" the signal                                           @unit _                                           @version 0x0100 */
    float        roadDist;        /**< distance to signal along road                                                        @unit m                                           @version 0x0100 */
    ASIM_COORD_t  pos;             /**< inertial position of signal                                                          @unit m,m,m,rad,rad,rad                           @version 0x0100 */
    int32_t      type;            /**< signal type according to OpenDRIVE                                                   @unit _                                           @version 0x0100 */
    int32_t      subType;         /**< signal sub-type according to OpenDRIVE                                               @unit _                                           @version 0x0100 */
    float        value;           /**< value associated with signal (e.g. speed, mass, validity)                            @unit depending on signal type, e.g. [m/s, kg, h] @version 0x0100 */
    uint32_t     state;           /**< traffic sign's state (if dynamic)                                                    @unit _                                           @version 0x0100 */
    int8_t       readability;     /**< sign's readability (-1 = not valid, 0..127 = 0..100% readability)                    @unit [-1, 0..127]                                @version 0x0100 */
    int8_t       occlusion;       /**< degree of occlusion for viewer (-1 = not valid, 0..127 = 0..100% occlusion)          @unit [-1, 0..127]                                @version 0x0100 */
    uint16_t     spare0;          /**< some more spare                                                                      @unit _                                           @version 0x0100 */
    uint32_t     addOnId;         /**< ID of additional sign which extends this sign                                        @unit _                                           @version 0x0100 */
    int8_t       minLane;         /**< ID minimum lane for which sign is valid                                              @unit [-127..127]                                 @version 0x0100 */
    int8_t       maxLane;         /**< ID maximum lane for which sign is valid                                              @unit [-127..127]                                 @version 0x0100 */
    uint16_t     spare;           /**< spare for upcoming info                                                              @unit _                                           @version 0x0100 */
} ASIM_TRAFFIC_SIGN_t;

/** ------ road state for a given vehicle ------ */
typedef struct
{
    uint32_t     playerId;        /**< ID of the player for which the state applies                            @unit _                              @version 0x0100 */
    int8_t       wheelId;         /**< unique ID of the player's wheel for which state is valid (-1 for all)   @unit @link ASIM_WHEEL_ID @endlink    @version 0x0100 */
    uint8_t      spare0;          /**< yet another spare                                                       @unit _                              @version 0x0100 */
    uint16_t     spare1;          /**< yet another spare                                                       @unit _                              @version 0x0100 */
    uint64_t     roadId;          /**< unique ID of the road                                                   @unit _                              @version 0x0100 */
    float        defaultSpeed;    /**< default speed of the road                                               @unit m/s                            @version 0x0100 */
    float        waterLevel;      /**< rain level on road                                                      @unit [0.0..1.0]                     @version 0x0100 */
    uint32_t     eventMask;       /**< road events                                                             @unit @link ASIM_ROAD_EVENT @endlink  @version 0x0100 */
    float        distToJunc;      /**< distance to next junction in driving direction                          @unit m                              @version 0x011F */
    int32_t      spare2[11];      /**< for future use                                                          @unit _                              @version 0x0100 */
} ASIM_ROAD_STATE_t;

/** ------ information about the environment state ------ */
typedef struct
{
    float          visibility;            /**< visibility range                                                        @unit m                                  @version 0x0100 */
    uint32_t       timeOfDay;             /**< time of day at sim start                                                @unit s                                  @version 0x0100 */
    float          brightness;            /**< brightness of ambient light                                             @unit [0.0..1.0]                         @version 0x0100 */
    uint8_t        precipitation;         /**< intensity of precipitation                                              @unit [0..255]                           @version 0x0100 */
    uint8_t        cloudState;            /**< cloud state                                                             @unit @link ASIM_ENV_CLOUD_STATE @endlink @version 0x0100 */
    uint16_t       flags;                 /**< a series of environment flags                                           @unit @link ASIM_ENV_FLAG        @endlink @version 0x0100 */
    float          temperature;           /**< ambient temperature                                                     @unit [deg]                              @version 0x0119 */
    uint8_t        day;                   /**< date - day                                                              @unit [-]                                @version 0x011F */
    uint8_t        month;                 /**< date - month                                                            @unit [-]                                @version 0x011F */
    uint16_t       year;                  /**< date - year                                                             @unit [-]                                @version 0x011F */
    int16_t        timeZoneMinutesWest;   /**< time zone, minutes west, relative to Greenwich                          @unit [-]                                @version 0x011F */
    uint16_t       spare2;                /**< yet another spare                                                       @unit _                                  @version 0x0100 */
    uint32_t       spare1[5];             /**< yet another spare                                                       @unit _                                  @version 0x0100 */
} ASIM_ENVIRONMENT_t;

/** ------ pedestrians animation data ------
* @note this package is followed immediately by "dataSize" bytes of data, containing hinge information etc.
*/
typedef struct
{
    uint32_t          playerId;   /**< unique player ID                                                        @unit _                          @version 0x0100 */
    ASIM_COORD_t       pos;        /**< real-world position and orientation of reference point32_t              @unit m,m,m,rad,rad,rad          @version 0x0100 */
    uint32_t          spare[4];   /**< some more spares                                                        @unit _                          @version 0x0100 */
    uint32_t          noCoords;   /**< number of valid co-ordinates in coord array                             @unit _                          @version 0x0100 */
    uint32_t          dataSize;   /**< size of the following data containing the actual co-ordinates           @unit byte                       @version 0x0100 */
} ASIM_PED_ANIMATION_t;

/** ------ scoring information (for racing applications) ------ */
typedef struct
{
    uint32_t playerId;         /**< unique player ID                                     @unit _                                    @version 0x0100 */
    float    pathS;            /**< path position (negative if no path is available)     @unit m                                    @version 0x0100 */
    float    roadS;            /**< road position (negative if no road is available)     @unit m                                    @version 0x0100 */
    float    fuelCurrent;      /**< current fuel consumption                             @unit l/100km                              @version 0x0100 */
    float    fuelAverage;      /**< average fuel consumption                             @unit l/100km                              @version 0x0100 */
    uint32_t stateFlags;       /**< arbitrary state information                          @unit @link ASIM_SCORING_FLAG @endlink      @version 0x0100 */
    float    slip;             /**< slip factor [0.0..1.0]                               @unit _                                    @version 0x0100 */
    uint32_t spare[4];         /**< we'll certainly have some more ideas....             @unit _                                    @version 0x0100 */
} ASIM_CUSTOM_SCORING_t;

/** ------ simulation frame trigger information ------ */
typedef struct
{
    float    deltaT;           /**< delta time by which to advance the simulation        @unit s                                    @version 0x0100 */
    uint32_t frameNo;          /**< number of the simulation frame which is triggered    @unit _                                    @version 0x0100 */
    uint16_t features;         /**< mask of features that shall be computed              @unit _                                    @version 0x011B */
    int16_t  spare0;           /**< spare for future use                                 @unit _                                    @version 0x011B */
} ASIM_TRIGGER_t;

/** ------ image generator trigger (live counter) information ------ */
typedef struct
{
    float    deltaT;           /**< delta time provided by IG                            @unit s                                    @version 0x011B */
    uint32_t frameNo;          /**< number of the IG frame which is triggering           @unit _                                    @version 0x011B */
    uint32_t spare[2];         /**< spares for future use                                @unit _                                    @version 0x011B */
} ASIM_IG_FRAME_t;

/** ------ information about driver control inputs (may be used e.g. for dynamics input) ------ */
typedef struct
{
    uint32_t playerId;         /**< unique player ID to which the controls apply         @unit _                                        @version 0x0100 */
    float    steeringWheel;    /**< steering wheel angle                                 @unit rad                                      @version 0x0100 */
    float    steeringSpeed;    /**< steering speed                                       @unit rad/s                                    @version 0x0100 */
    float    throttlePedal;    /**< throttle pedal position                              @unit [0.0..1.0]                               @version 0x0100 */
    float    brakePedal;       /**< brake pedal position                                 @unit [0.0..1.0]                               @version 0x0100 */
    float    clutchPedal;      /**< clutch pedal position                                @unit [0.0..1.0]                               @version 0x0100 */
    float    accelTgt;         /**< desired acceleration                                 @unit m/s2                                     @version 0x0100 */
    float    steeringTgt;      /**< desired steering angle at wheels                     @unit rad                                      @version 0x0100 */        /* TODO: maybe this should become the turn rate */
    double   curvatureTgt;     /**< desired resulting curvature of the lateral motion    @unit 1/m                                      @version 0x0100 */
    float    steeringTorque;   /**< torque at steering wheel                             @unit Nm                                       @version 0x0100 */
    float    engineTorqueTgt;  /**< target engine torque                                 @unit Nm                                       @version 0x0100 */
    float    speedTgt;         /**< target speed                                         @unit m/s                                      @version 0x0100 */
    uint8_t  gear;             /**< desired gear box position                            @unit @link ASIM_GEAR_BOX_POS          @endlink @version 0x0100 */
    uint8_t  sourceId;         /**< unique number of the source providing this input     @unit @link ASIM_DRIVER_SOURCE         @endlink @version 0x010E */
    uint8_t  spare0[2];        /**< some spares for future use                           @unit _                                        @version 0x0100 */
    uint32_t validityFlags;    /**< flags which of the above inputs are valid            @unit @link ASIM_DRIVER_INPUT_VALIDITY @endlink @version 0x0100 */
    uint32_t flags;            /**< input flags (indicator etc.)                         @unit @link ASIM_DRIVER_FLAG           @endlink @version 0x0100 */
    uint32_t mockupInput0;     /**< flags resulting from mockup buttons, part 1          @unit @link ASIM_MOCKUP_INPUT0         @endlink @version 0x010A */
    uint32_t mockupInput1;     /**< flags resulting from mockup buttons, part 2          @unit @link ASIM_MOCKUP_INPUT1         @endlink @version 0x010A */
    uint32_t mockupInput2;     /**< flags resulting from mockup buttons, part 3          @unit @link ASIM_MOCKUP_INPUT2         @endlink @version 0x010A */
    uint32_t spare;            /**< some spare  for future use                           @unit _                                        @version 0x010A */
} ASIM_DRIVER_CTRL_t;

/** ------ information about driver control inputs (may be used e.g. for dynamics input) ------ */
typedef struct
{
    uint32_t playerId;         /**< unique player ID to which the controls apply         @unit _                                            @version 0x0100 */
    float    speedFromRules;   /**< speed from rules (i.e. road, signs etc.)             @unit m/s                                          @version 0x0100 */
    float    distToSpeed;      /**< distance to next speed from rules (-1.0 to disable)  @unit m                                            @version 0x0100 */
    float    spare0[4];        /**< just some spares                                     @unit _                                            @version 0x0100 */
    uint32_t flags;            /**< input flags (turn dir etc.)                          @unit @link ASIM_DRIVER_PERCEPTION_FLAG @endlink    @version 0x0100 */
    uint32_t spare[4];         /**< some spares for future use                           @unit _                                            @version 0x0100 */
} ASIM_DRIVER_PERCEPTION_t;

/** ------ information about a traffic light (state) ------ */
typedef struct
{
    int32_t                   id;                             /**< unique ID of the traffic light                           @unit _                           @version 0x0100 */
    float                     state;                          /**< current state (normalized)                               @unit [0.0..1.0]                  @version 0x0100 */
    uint32_t                  stateMask;                      /**< current state mask (light mask, e.g. for gfx)            @unit _                           @version 0x0100 */
} ASIM_TRAFFIC_LIGHT_BASE_t;

/** ------ traffic light phase information entry ------ */
typedef struct
{
    float   duration;                        /**< normalized duration of the phase, invalid phases will have duration 0.0   @unit [0.0..1.0]                         @version 0x0100 */
    uint8_t type;                            /**< type of the phase                                                         @unit @link ASIM_TRLIGHT_PHASE @endlink   @version 0x0100 */
    uint8_t spare[3];                        /**< spares for future use                                                     @unit _                                  @version 0x0100 */
} ASIM_TRAFFIC_LIGHT_PHASE_t;

/** ------ extended information about a traffic light (phases, state details) ------
 * @note this package is followed immediately by "dataSize" bytes of data, containing "noPhases" phase information entries ASIM_TRAFFIC_LIGHT_PHASE_t */
typedef struct
{
    int32_t                   ctrlId;                         /**< ID of the traffic light's controller                     @unit _                           @version 0x0100 */
    float                     cycleTime;                      /**< duration of a complete cycle of all phases               @unit s                           @version 0x0100 */
    uint16_t                  noPhases;                       /**< number of phases provided by this traffic light          @unit _                           @version 0x0100 */
    uint32_t                  dataSize;                       /**< total size of phase data following the package           @unit _                           @version 0x0100 */
} ASIM_TRAFFIC_LIGHT_EXT_t;

/** ------ complete traffic light data (basic and extended info) ------- */
typedef struct
{
    ASIM_TRAFFIC_LIGHT_BASE_t base;          /**< information about a traffic light state    @unit ASIM_TRAFFIC_LIGHT_BASE_t  @version 0x0100 */
    ASIM_TRAFFIC_LIGHT_EXT_t  ext;           /**< extended information about a traffic light @unit ASIM_TRAFFIC_LIGHT_EXT_t   @version 0x0100 */
} ASIM_TRAFFIC_LIGHT_t;

/** ------ synchronization package ------- */
typedef struct
{
    uint32_t mask;          /**< mask of required sync sources which are fulfilled by this sender            @unit _                        @version 0x0100 */
    uint32_t cmdMask;       /**< mask of commands included in the sync message                               @unit ASIM_SYNC_CMD             @version 0x010E */
    double   systemTime;    /**< system time                                                                 @unit s                        @version 0x0118 */
} ASIM_SYNC_t;

/** ------ road query package ------- */
typedef struct
{
    uint16_t id;            /**< unique ID of the road query point (reflected in answer)                     @unit _                        @version 0x0107 */
    uint16_t flags;         /**< query flags                                                                 @unit ASIM_ROAD_QUERY_FLAG      @version 0x0107 */
    uint16_t spare[2];      /**< spare for future use                                                        @unit _                        @version 0x0107 */
    double   x;             /**< x co-ordinate (inertial) of query location                                  @unit m                        @version 0x0107 */
    double   y;             /**< y co-ordinate (inertial) of query location                                  @unit m                        @version 0x0107 */
} ASIM_ROAD_QUERY_t;

/** ------ wrapper for SCP messages -------
 * @note this package is followed immediately by "dataSize" bytes of data, containing the actual SCP command string */
typedef struct
{
    uint16_t  version;                     /**< upper byte = major, lower byte = minor                       @unit _                        @version 0x010C */
    uint16_t  spare;                       /**< just another spare                                           @unit _                        @version 0x010C */
    char      sender[ASIM_SIZE_SCP_NAME];   /**< name of the sender as text                                   @unit _                        @version 0x010C */
    char      receiver[ASIM_SIZE_SCP_NAME]; /**< name of the receiver as text                                 @unit _                        @version 0x010C */
    uint32_t  dataSize;                    /**< number of data bytes following this entry                    @unit _                        @version 0x010C */
} ASIM_SCP_t;

/** ------ wrapper for forwarded messages -------
 * @note this package is followed immediately by "dataSize" bytes of data, containing the actual forwarded message */
typedef struct
{
    uint16_t  protocol;                    /**< protocol identifier of the wrapped package                   @unit _                        @version 0x0112 */
    uint16_t  pkgId;                       /**< unique pkg id                                                @unit _                        @version 0x0112 */
    uint32_t  spare[6];                    /**< some spares                                                  @unit _                        @version 0x0112 */
    uint32_t  dataSize;                    /**< number of data bytes following this entry                    @unit _                        @version 0x0112 */
} ASIM_PROXY_t;

/** ------ trajectory planning points of a player -------
 * @note this package is immediately followed by "noDataPoints" entries of type ASIM_POINT_t
*/
typedef struct
{
    uint32_t  playerId;                    /**< unique player / object ID                                    @unit _                                       @version 0x0110 */
    double    spacing;                     /**< spacing of data points, either in space or time domain       @unit m, s                                    @version 0x0110 */
    uint16_t  flags;                       /**< flags for treatment of trajectory                            @unit @link ASIM_TRAJECTORY_FLAG @endlink      @version 0x0110 */
    uint16_t  noDataPoints;                /**< number of trajectory points following this package           @unit _                                       @version 0x0110 */
    uint32_t  spare[4];                    /**< some more spares                                             @unit _                                       @version 0x0110 */
} ASIM_TRAJECTORY_t;

/** ------ state of the motion system ------- */
typedef struct
{
    uint32_t            playerId;                   /**< unique player / object ID to which the information applies    @unit _                                      @version 0x0116 */
    uint32_t            flags;                      /**< flags for state monitoring etc.                               @unit @link ASIM_MOTION_SYSTEM_FLAG  @endlink @version 0x0116 */
    ASIM_COORD_t         pos;                        /**< position and orientation of eyepoint                          @unit m,m,m,rad,rad,rad                      @version 0x0116 */
    ASIM_COORD_t         speed;                      /**< transversal and angular speed of eyepoint                     @unit m,m,m,rad,rad,rad                      @version 0x0116 */
    uint8_t             subSystem;                  /**< subsystem identifier                                          @unit _                                      @version 0x011F */
    uint8_t             spare1[3];                  /**< reserved for future use                                       @unit _                                      @version 0x011F */
    uint32_t            spare[5];                   /**< reserved for future use                                       @unit _                                      @version 0x0116 */
} ASIM_MOTION_SYSTEM_t;

/** ------ state of a symbol ------- */
typedef struct
{
    uint32_t            id;                         /**< unique numeric id of the controlled symbol                    @unit _                                      @version 0x011F */
    ASIM_COORD_t         pos;                        /**< position and orientation of the symbol                        @unit m,m,m,rad,rad,rad                      @version 0x011F */
    ASIM_POINT_t         scale;                      /**< 3d scale  of the symbol                                       @unit -,-,-                                  @version 0x011F */
    uint32_t            spare[6];                   /**< reserved for future use                                       @unit _                                      @version 0x011F */
} ASIM_SYMBOL_STATE_t;

/** ------ custom object control package ------ */
typedef struct
{
    uint32_t playerId;              /**< unique player ID                                                             @unit _                                                        @version 0x0119 */
    uint16_t flags;                 /**< configuraton flags                                                           @unit @link ASIM_CUSTOM_TRACK_CTRL_FLAG  @endlink               @version 0x0119 */
    uint8_t  posType;               /**< player position type                                                         @unit 0 = default, 1 = rel. Ego, 2 = rel. path, 3 = rel. road  @version 0x0119 */
    int8_t   dir;                   /**< direction of driving (1=with track, -1=opposite track)                       @unit [-1,1]                                                   @version 0x0119 */
    uint32_t roadId;                /**< unique road ID                                                               @unit _                                                        @version 0x0119 */
    double   initialRoadDeltaS;     /**< initial road position relative to Ego (negative if no road is available)     @unit m                                                        @version 0x0119 */
    float    targetRoadT;           /**< target lateral road position; for first frame, it's the initial roadT        @unit m                                                        @version 0x0119 */
    float    speedTgtS;             /**< target speed along road                                                      @unit m/s                                                      @version 0x0119 */
    float    minAccelS;             /**< minimum acceleration along road                                              @unit m/s2                                                     @version 0x0119 */
    float    maxAccelS;             /**< maximum acceleration along road                                              @unit m/s2                                                     @version 0x0119 */
    float    accelTgt;              /**< target acceleration (vehicle system)                                         @unit m/s2                                                     @version 0x0119 */
    uint32_t validityFlags;         /**< flags which of the above inputs are valid                                    @unit @link ASIM_CUSTOM_TRACK_CTRL_VALIDITY @endlink            @version 0x0119 */
    uint8_t  canTimeStamp;          /**< time stamp on CAN bus                                                        @unit _                                                        @version 0x0119 */
    uint8_t  spare0[3];             /**< we'll certainly have some more ideas....                                     @unit _                                                        @version 0x0119 */
    uint32_t spare[3];              /**< we'll certainly have some more ideas....                                     @unit _                                                        @version 0x0119 */
} ASIM_CUSTOM_OBJECT_CTRL_TRACK_t;

/** ------ freespace description package ------ */
typedef struct
{
    uint32_t playerId;             /**< unique player ID                                                             @unit _                                                        @version 0x011A */
    float    distance;             /**< distance to closest object                                                   @unit m                                                        @version 0x011A */
    float    angleLeft;            /**< angle to left-most boundary of all objects forming the freespace             @unit rad                                                      @version 0x011A */
    float    angleRight;           /**< angle to right-most boundary of all objects forming the freespace            @unit rad                                                      @version 0x011A */
    float    distanceLeft;         /**< distance to item defining left angle                                         @unit m                                                        @version 0x011A */
    float    distanceRight;        /**< distance to item defining right angle                                        @unit m                                                        @version 0x011A */
    uint8_t  stateLeft;            /**< state of left boundary                                                       @unit @link ASIM_FREESPACE_STATE  @endlink                      @version 0x011A */
    uint8_t  stateRight;           /**< state of right boundary                                                      @unit @link ASIM_FREESPACE_STATE  @endlink                      @version 0x011A */
    uint8_t  stateDistance;        /**< state of distance information                                                @unit @link ASIM_FREESPACE_STATE  @endlink                      @version 0x011A */
    uint8_t  noVisibleObjects;     /**< number of visible objects in range                                           @unit _                                                        @version 0x011A */
    uint32_t spare1[3];            /**< we'll certainly have some more ideas....                                     @unit _                                                        @version 0x011A */
} ASIM_FREESPACE_t;

/** ------ generit switch description package ------ */
typedef struct
{
    uint32_t objectId;              /**< ID of the object which contains the switch                          @unit _                                @version 0x011B */
    uint32_t elementId;             /**< ID of the switch itself                                             @unit _                                @version 0x011B */
    uint8_t  scope;                 /**< scope of the dynamic element                                        @unit @link ASIM_DYN_EL_SCOPE  @endlink @version 0x011B */
    uint8_t  spare0[3];             /**< for future use                                                      @unit _                                @version 0x011B */
    uint32_t state;                 /**< state of the switch as bit mask                                     @unit _                                @version 0x011B */
    uint32_t spare1[2];             /**< for future use                                                      @unit _                                @version 0x011B */
} ASIM_DYN_EL_SWITCH_t;

/** ------ generic DOF description package ------
 * @note this package is immediately followed by "nValues" entries of type double
*/
typedef struct
{
    uint32_t objectId;              /**< ID of the object which contains the switch                          @unit _                                                @version 0x011B */
    uint32_t elementId;             /**< ID of the switch itself                                             @unit _                                                @version 0x011B */
    uint8_t  scope;                 /**< scope of the dynamic element                                        @unit @link ASIM_DYN_EL_SCOPE  @endlink                 @version 0x011B */
    uint8_t  validity;              /**< mask of elements controlled by the following double numbers         @unit [x=0x01, y=0x02, z=0x04, h=0x08, p=0x10, r=0x20] @version 0x011B */
    uint8_t  nValues;               /**< number of double values sent immediately after this structure       @unit _                                                @version 0x011B */
    uint8_t  spare0;                /**< for future use                                                      @unit _                                                @version 0x011B */
    uint32_t spare1[3];             /**< for future use                                                      @unit _                                                @version 0x011B */
} ASIM_DYN_EL_DOF_t;

#ifndef MATLAB_MEX_FILE
/** ------ empty structure for end-of-frame message (not to be used) -------  */
typedef struct
{
} ASIM_END_OF_FRAME_t;

/** ------ empty structure for start-of-frame message (not to be used) -------  */
typedef struct
{
} ASIM_START_OF_FRAME_t;
#endif

/** ------ structure for SHM interface from steering wheel control to dynamics -------  */
typedef struct
{
    uint32_t  playerId;     /**< unique player / object ID                           @unit _                                      @version 0x0111 */
    uint32_t  state;        /**< steering wheel state flags                          @unit @link ASIM_STEER_2_DYN_STATE @endlink   @version 0x0111 */
    float     angle;        /**< steering wheel angle                                @unit rad                                    @version 0x0111 */
    float     rev;          /**< steering wheel rot speed                            @unit rad/s                                  @version 0x0111 */
    float     torque;       /**< steering wheel current torque                       @unit Nm                                     @version 0x0111 */
    uint32_t  spare[8];     /**< some more spares                                    @unit _                                      @version 0x0111 */
} ASIM_STEER_2_DYN_t;

/** ------ structure for SHM interface from dynamics to steering wheel control -------  */
typedef struct
{
    uint32_t  playerId;         /**< unique player / object ID                            @unit _                                         @version 0x0111 */
    uint16_t  state;            /**< dynamics state.                                      @unit @link ASIM_DYN_2_STEER_STATE   @endlink    @version 0x0111 */
    uint16_t  cmd;              /**< command to the steering wheel                        @unit @link ASIM_DYN_2_STEER_CMD     @endlink    @version 0x0111 */
    uint32_t  effects;          /**< special effects flag.                                @unit @link ASIM_DYN_2_STEER_EFFECTS @endlink    @version 0x0111 */
    float     torque;           /**< desired torque                                       @unit Nm                                        @version 0x0111 */
    float     friction;         /**< friction                                             @unit Nm                                        @version 0x0111 */
    float     damping;          /**< damping                                              @unit Nm/rad/s                                  @version 0x0111 */
    float     stiffness;        /**< stiffness                                            @unit Nm/rad                                    @version 0x0111 */
    float     velocity;         /**< vehicle longitudinal velocity                        @unit m/s                                       @version 0x0111 */
    float     angle;            /**< resulting steering wheel angle (for passive mode)    @unit rad                                       @version 0x0111 */
    float     neutralPos;       /**< neutral position of steering wheel                   @unit rad                                       @version 0x0119 */
    float     dampingMaxTorque; /**< damping, maximum torque                              @unit Nm/                                       @version 0x0119 */
    uint32_t  spare[6];         /**< some more spares                                     @unit _                                         @version 0x0111 */
} ASIM_DYN_2_STEER_t;

/** ------ structure for ray casting -------  */
typedef struct
{
    uint32_t    id;               /**< unique ray ID                                        @unit _                                         @version 0x011C */
    uint32_t    emitterId;        /**< unique ID of the ray's emitter                       @unit _                                         @version 0x011C */
    uint8_t     type;             /**< type of the ray information                          @unit @link ASIM_RAY_TYPE @endlink               @version 0x011C */
    uint8_t     spare0;           /**< spare (to be used later on for emitter category etc. @unit _                                         @version 0x011C */
    uint16_t    spare2;           /**< spare (to be used later on for emitter category etc. @unit _                                         @version 0x011C */
    float       length;           /**< (maximum) length of the ray                          @unit _                                         @version 0x011C */
    uint32_t    spare1[3];        /**< some more spares                                     @unit _                                         @version 0x011C */
    ASIM_COORD_t ray;              /**< the ray itself (origin + direction)                  @unit m,m,m,rad,rad,rad                         @version 0x011C */
} ASIM_RAY_t;

/** ------ structure for performance monitoring -------  */
typedef struct
{
    uint32_t    noOverruns;       /**< number of real-time overruns                         @unit _                                         @version 0x011D */
    uint32_t    noUnderruns;      /**< number of real-time underruns                        @unit _                                         @version 0x011D */
    uint32_t    noMeasurements;   /**< number of measured frames                            @unit _                                         @version 0x011D */
    float       tolerance;        /**< tolerance of real-time watchdog                      @unit [s]                                       @version 0x011D */
    float       nominalFrameTime; /**< nominal duration of a frame                          @unit [s]                                       @version 0x011D */
    float       actualFrameTime;  /**< actual (measured) duration of last frame             @unit [s]                                       @version 0x011D */
    uint32_t    spare1[6];        /**< some more spares                                     @unit _                                         @version 0x011D */
} ASIM_RT_PERFORMANCE_t;

/** ------ custom look-ahead package ------ */
typedef struct
{
    uint32_t playerId;              /**< unique player ID                                                             @unit _                                                        @version 0x011E */
    float    distance;              /**< distance for which the look ahead is valid                                   @unit m or s                                                   @version 0x011E */
    uint8_t  distUnit;              /**< unit of the distance value                                                   @unit @link ASIM_UNIT @endlink                                  @version 0x011E */
    uint8_t  spare0[3];             /**< we'll certainly have some more ideas....                                     @unit _                                                        @version 0x011E */
    float    laneOffset;            /**< lane offset at given distance                                                @unit m                                                        @version 0x011E */
    float    hdgRel;                /**< relative heading at given distance                                           @unit rad                                                      @version 0x011E */
    float    curvHor;               /**< horizontal curvature at given distance                                       @unit 1/m                                                      @version 0x011E */
    float    curvHorDot;            /**< first derivative ofhorizontal curvature at given distance                    @unit 1/m                                                      @version 0x011F */
    uint32_t spare[7];              /**< we'll certainly have some more ideas....                                     @unit _                                                        @version 0x011E */
} ASIM_CUSTOM_LOOK_AHEAD_t;

/** ------ header of a complete message ------ */
typedef struct
{
    uint16_t  magicNo;      /**< must be ASIM_MAGIC_NO (35712)                                               @unit @link GENERAL_DEFINITIONS @endlink   @version 0x0100 */
    uint16_t  version;      /**< upper byte = major, lower byte = minor                                     @unit _                                    @version 0x0100 */
    uint32_t  headerSize;   /**< size of this header structure when transmitted                             @unit byte                                 @version 0x0100 */
    uint32_t  dataSize;     /**< size of data following the header                                          @unit byte                                 @version 0x0100 */
    uint32_t  frameNo;      /**< number of the simulation frame                                             @unit _                                    @version 0x0100 */
    double    simTime;      /**< simulation time                                                            @unit s                                    @version 0x0100 */
} ASIM_MSG_HDR_t;

/** ------ header of a package vector within a message ------ */
typedef struct
{
    uint32_t  headerSize;   /**< size of this header structure when transmitted                              @unit byte                     @version 0x0100 */
    uint32_t  dataSize;     /**< size of data following the header                                           @unit byte                     @version 0x0100 */
    uint32_t  elementSize;  /**< if data following the header contains an array of elements of equal size:
                                 size of one element in this data
                                 (elementSize is equivalent to dataSize if only one element is transmitted)  @unit byte                         @version 0x0100 */
    uint16_t  pkgId;        /**< package identifier                                                          @unit _                            @version 0x0100 */
    uint16_t  flags;        /**< various flags concerning the package's contents (e.g. extension)            @unit @link ASIM_PKG_FLAG @endlink  @version 0x0100 */
} ASIM_MSG_ENTRY_HDR_t;


/** ------ the message union (use for very simplistic casting only)------ */
typedef union
{
    ASIM_COORD_SYSTEM_t              coordSystem;                   /**< (custom) co-ordinate system                                         @msgid ASIM_PKG_ID_COORD_SYSTEM              */
    ASIM_COORD_t                     coord;                         /**< single co-ordinate extending previous object information            @msgid ASIM_PKG_ID_COORD                     */
    ASIM_ROAD_POS_t                  roadPos;                       /**< detailed road position of a given entity                            @msgid ASIM_PKG_ID_ROAD_POS                  */
    ASIM_LANE_INFO_t                 laneInfo;                      /**< lane information for a given entity                                 @msgid ASIM_PKG_ID_LANE_INFO                 */
    ASIM_ROADMARK_t                  roadMark;                      /**< road mark information for a player                                  @msgid ASIM_PKG_ID_ROADMARK                  */
    ASIM_OBJECT_CFG_t                objectCfg;                     /**< info about a (traffic) object configuration                         @msgid ASIM_PKG_ID_OBJECT_CFG                */
    ASIM_OBJECT_STATE_t              objectState;                   /**< info about an arbitrary object's state                              @msgid ASIM_PKG_ID_OBJECT_STATE              */
    ASIM_VEHICLE_SYSTEMS_t           vehicleSystems;                /**< vehicle systems' states (lights etc.)                               @msgid ASIM_PKG_ID_VEHICLE_SYSTEMS           */
    ASIM_VEHICLE_SETUP_t             vehicleSetup;                  /**< basic information about a vehicle (mass etc.)                       @msgid ASIM_PKG_ID_VEHICLE_SETUP             */
    ASIM_ENGINE_t                    engine;                        /**< info about a vehicle's engine                                       @msgid ASIM_PKG_ID_ENGINE                    */
    ASIM_DRIVETRAIN_t                drivetrain;                    /**< info about a vehicle's drivetrain                                   @msgid ASIM_PKG_ID_DRIVETRAIN                */
    ASIM_WHEEL_t                     wheel;                         /**< info about a wheel of a player                                      @msgid ASIM_PKG_ID_WHEEL                     */
    ASIM_PED_ANIMATION_t             pedAnimation;                  /**< pedestrian animation details (joint angles etc.)                    @msgid ASIM_PKG_ID_PED_ANIMATION             */
    ASIM_SENSOR_STATE_t              sensorState;                   /**< state of a sensor                                                   @msgid ASIM_PKG_ID_SENSOR_STATE              */
    ASIM_SENSOR_OBJECT_t             sensorObject;                  /**< state of an object detected by a sensor                             @msgid ASIM_PKG_ID_SENSOR_OBJECT             */
    ASIM_CAMERA_t                    camera;                        /**< camera settings used for video image                                @msgid ASIM_PKG_ID_CAMERA                    */
    ASIM_CONTACT_POINT_t             contactPoint;                  /**< info about contact points                                           @msgid ASIM_PKG_ID_CONTACT_POINT             */
    ASIM_TRAFFIC_SIGN_t              trafficSign;                   /**< info about traffic signs seen by a vehicle                          @msgid ASIM_PKG_ID_TRAFFIC_SIGN              */
    ASIM_ROAD_STATE_t                roadState;                     /**< road state informaton for a given player                            @msgid ASIM_PKG_ID_ROAD_STATE                */
    ASIM_IMAGE_t                     image;                         /**< video image (followed by data)                                      @msgid ASIM_PKG_ID_IMAGE                     */
    ASIM_LIGHT_SOURCE_t              lightSrc;                      /**< info about a light source                                           @msgid ASIM_PKG_ID_LIGHT_SOURCE              */
    ASIM_ENVIRONMENT_t               environment;                   /**< info about environment state                                        @msgid ASIM_PKG_ID_ENVIRONMENT               */
    ASIM_TRIGGER_t                   trigger;                       /**< trigger information                                                 @msgid ASIM_PKG_ID_TRIGGER                   */
    ASIM_DRIVER_CTRL_t               driverCtrl;                    /**< driver input (e.g. from mockup) - serves also as dynamics input     @msgid ASIM_PKG_ID_DRIVER_CTRL               */
    ASIM_TRAFFIC_LIGHT_t             trafficLight;                  /**< info about a traffic light                                          @msgid ASIM_PKG_ID_TRAFFIC_LIGHT             */
    ASIM_SYNC_t                      sync;                          /**< sync source message                                                 @msgid ASIM_PKG_ID_SYNC                      */
    ASIM_DRIVER_PERCEPTION_t         driverPerception;              /**< perception of road/rule environment by driver                       @msgid ASIM_PKG_ID_DRIVER_PERCEPTION         */
    ASIM_IMAGE_t                     lightMap;                      /**< light distribution image (followed by data)                         @msgid ASIM_PKG_ID_LIGHT_MAP                 */
    ASIM_FUNCTION_t                  toneMapping;                   /**< tone mapping function                                               @msgid ASIM_PKG_ID_TONE_MAPPING              */
    ASIM_PROXY_t                     proxy;                         /**< proxy package with payload                                          @msgid ASIM_PKG_ID_PROXY                     */
    ASIM_MOTION_SYSTEM_t             motionSystem;                  /**< information about motion system state                               @msgid ASIM_PKG_ID_MOTION_SYSTEM             */
    ASIM_IG_FRAME_t                  igFrame;                       /**< information about IG frame upon arrival                             @msgid ASIM_PKG_ID_IG_FRAME                  */
    /* custom packages here, please */
    ASIM_CUSTOM_SCORING_t            scoring;                       /**< scoring information                                                 @msgid ASIM_PKG_ID_CUSTOM_SCORING            */
} ASIM_MSG_UNION_t;


typedef struct
{
    ASIM_MSG_HDR_t       hdr;            /**< header of a complete message                   @unit ASIM_MSG_HDR_t         @version 0x0100 */
    ASIM_MSG_ENTRY_HDR_t entryHdr;       /**< header of a package vector within a message    @unit ASIM_MSG_ENTRY_HDR_t   @version 0x0100 */
    ASIM_MSG_UNION_t     u;              /**< the message union                              @unit ASIM_MSG_UNION_t       @version 0x0100 */
} ASIM_MSG_t;

/** ------ shared memory segment header, located of beginning of shared memory segment ------ */
typedef struct
{
    uint32_t  thisSize;   /**< size of this info structure                               @unit byte                                 @version 0x0100 */
    uint32_t  bufferSize; /**< size of the associated buffer                             @unit byte                                 @version 0x0100 */
    uint16_t  id;         /**< unique ID of the buffer                                   @unit _                                    @version 0x0100 */
    uint16_t  spare0;     /**< just some spare                                           @unit _                                    @version 0x0100 */
    uint32_t  flags;      /**< access flags etc.                                         @unit @link ASIM_SHM_BUFFER_FLAG @endlink   @version 0x0100 */
    uint32_t  offset;     /**< offset to start of buffer from start of shared memory     @unit byte                                 @version 0x0100 */
    uint32_t  spare1[4];  /**< just some spares                                          @unit _                                    @version 0x0100 */
} ASIM_SHM_BUFFER_INFO_t;

/** ------ shared memory management header, located of beginning of shared memory ------
* @note this entry is followed immediately by "noBuffers" bytes of type ASIM_SHM_BUFFER_INFO_t, containing "noBuffers" buffer information entries
*/
typedef struct
{
    uint32_t  headerSize;     /**< size of this header structure                               @unit byte                     @version 0x0100 */
    uint32_t  dataSize;       /**< size of data following this header                          @unit byte                     @version 0x0100 */
    uint8_t   noBuffers;      /**< number of data buffers in the shared memory                 @unit _                        @version 0x0100 */
} ASIM_SHM_HDR_t;




















#endif //ASIM_COMMUNICATION_ASIMTYPE_H
