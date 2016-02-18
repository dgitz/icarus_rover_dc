#include "Arduino.h"

//Diagnostic Definitions

//Field 1: System
#define ROVER 1
#define GROUND_STATION 5
#define REMOTE_CONTROL 7

//Field 2: Subsystem
#define ENTIRE_SYSTEM 0
#define ROBOT_CONTROLLER 1
#define MOTION_CONTROLLER 2
#define SONIC_CONTROLLER 3

//Field 3: Component
#define ENTIRE_SUBSYSTEM 0
#define DIAGNOSTIC_NODE 1
#define NAVIGATION_NODE 2
#define MOTION_CONTROLLER_NODE 3
#define SONIC_CONTROLLER_NODE 4
#define EVOLUTION_NODE 5
#define TARGETING_NODE 6
#define MAPPING_NODE 7
#define POSE_NODE 8

//Field 4: Diagnostic Type
#define NO_ERROR 0
#define ELECTRICAL 1
#define SOFTWARE 2
#define COMMUNICATIONS 3
#define SENSORS 4
#define ACTUATORS 5
#define DATA_STORAGE 6
#define REMOTE_CONTROL 7
#define GENERAL_ERROR 9

//Field 5: Level
//#define NO_ERROR 0  Already defined above, just leaving here for completeness.
#define DEBUG 1
#define INFORMATION 2
#define MINIMAL 3
#define CAUTION 4
#define SEVERE 5
#define FATAL 6

//Field 6: Diagnostic_Message
//#define NO_ERROR 0  Already defined above, just leaving here for completeness.
#define INITIALIZING 1
#define INITIALIZING_ERROR 2
#define DROPPING_PACKETS 4
#define MISSING_HEARTBEATS 5
#define DEVICE_NOT_AVAILABLE 6
#define ROVER_ARMED 7
#define ROVER_DISARMED 8
//#define GENERAL_ERROR 9  Already defined above, just leaving here for completeness.

#define MC_NODE_UNKNOWN 0
#define MC_NODE_NOT_AVAILABLE 1
#define MC_NODE_READY 2
#define MC_NODE_ARMED 3
#define MC_NODE_DISARMED 4




