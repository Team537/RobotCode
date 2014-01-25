#ifndef SCHEMATIC_H
#define SCHEMATIC_H

// Controllers
// Primary Controller
#define PRIMARY_CONTROLLER 1
#define LEFT_DRIVE_JOY 2
#define RIGHT_DRIVE_JOY 4
#define BTN_DRIVE 2
#define BTN_CLIMB 1
#define BTN_HARD_STOP_TOGGLE 5
#define BTN_TURTLE_MODE 6 // change turbo to slow mode
#define BTN_LOW_SHIFT 7
#define BTN_HIGH_SHIFT 8
#define BTN_UH_OH 10 // stop button

// always false climb is true disable is false
// Secondary Controller
#define SECONDARY_CONTROLLER 2
#define FINE_ANGLE_JOY 2
#define ROUGH_ANGLE_JOY 4
#define BTN_SHOOT 6
#define BTN_SHOOT_MODE 8

// Pot values for shooter
#define PITCH_AUTO 112
#define PITCH_LOAD 185
#define PITCH_3PT 112
#define PITCH_START 87
#define PITCH_BOTTOM_LIMIT 200
#define PITCH_TOP_LIMIT 84
#define PITCH_TRAVEL 135

//Autonomous
#define DRIVEANDANGLE 0
#define DRIVEANDANGLEISDONE 1
#define LOADSHOOTER 2
#define SHOOTSHOOTER 3
#define DRIVEBACK 4
#define ENDAUTONOMOUS 5

// Robot
#define CLIMBER_ENCODER_A 1,5
#define CLIMBER_ENCODER_B 1,6
#define LEFT_MOTOR 1,2
#define RIGHT_MOTOR 1,1
#define SHIFT_LOW 1,1
#define SHIFT_HIGH 1,2
#define AUTO_SWITCH_ONE 1,12
#define AUTO_SWITCH_TWO 1,13
#define AUTO_SWITCH_THREE 1,14
#define COMPRESSOR 1,11, 1,1
#define CLIMB 1,3
#define DRIVE 1,4
#define SPIN_MOTOR_1 1,7
#define PUSH_FRISBEE 1,5
#define HEIGHT_ADJUSTMENT 1,6
#define FRISBEE_DETECTOR 1,15
#define SHOOTER_POT 1,2
// #define TOP_SWITCH 1,8
#define BOT_SWITCH 1,7
#define LOAD true
#define SHOOT false
#define CLIMBER_DEPLOY 1,6
#define PNEUMATIC_BUMPER_EXTEND 2,3
#define PNEUMATIC_BUMPER_RETRACT 2,4

#define CLIMBER_BRAKE_RELEASE 1,7 // always 0, when climbing it's 1, when disabled automatically goes to 0
#define HARD_STOP_DEPLOY 1,8 // always 0, button(toggle) makes 1

#define PRINT_TIME 0.05

#define PACKET_GEAR 15
#define PACKET_ANGLE 16
#define PACKET_CLIMB 17

#define SHOOTER_MOTOR 25

enum eRobotMode {eTank, eTurtle};
enum eGear {eLow, eHigh, eClimb, eDrive};
enum eShooterMode {eShoot, eReload};
enum eMode {dDrive, cClimb};
enum eShootPreset {Reload, pt3, None, Auto, Start, Travel};

#endif
