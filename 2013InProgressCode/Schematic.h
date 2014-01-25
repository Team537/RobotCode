#ifndef SCHEMATIC_H_ // Fancy version of pragma
#define SCHEMATIC_H_ // Fancy version of pragma

// Controller
#define PRIMCONT 1 // Primary controller
#define SECCONT 2 // Secondary controller
#define LEFTSTICK 2 // Left joystick
#define RIGHTSTICK 4 // Right joystick

// Controller Buttons
#define BTN_L1 5 // Button L1
#define BTN_R1 6 // Button R1
#define BTN_L2 7 // Button L2
#define BTN_R2 8 // Button R2
#define POSSIBLE_LOW_GOAL_AIM 1 // Button for autoaiming low
#define POSSIBLE_MID_GOAL_AIM 2 // Button for autoaiming mid
#define POSSIBLE_HIGH_GOAL_AIM 3 // Button for autoaiming high
#define POSSIBLE_PYRAMID_GOAL_AIM 4 // 

// Drive Train
#define LEFT_MOTOR 1,2 // Left motor
#define RIGHT_MOTOR 1,1 // Right motor
//#define SHIFT_HI 1,1 // High gear
//#define SHIFT_LOW 1,2 // Low gear
#define SHIFT_LEFT 3,1
#define SHIFT_RIGHT 3,2
//#define LEFT_ENCODER 1,1, 1,2 // Left motor encoder
//#define RIGHT_ENCODER 1,3, 1,4 // Right motor encoder
#define LEFT_ENCODER 1,1, 1,2
#define RIGHT_ENCODER 1,3, 1,4

#define SHOOT_POT 5,3 // Random numbers

#define AUTO_SWITCH_ONE 1,13
#define AUTO_SWITCH_TWO 1,14

/*
// Climber
#define CLIMB_DRIVE_MOTOR 2,3
#define CLIMBER 2,4
#define CLIMBER_ENCODER 2,5, 2,6

// Collector
#define COLLECTOR_DRIVE 2,5

// Shooter
#define HEIGHT 2,6
#define SHOOT_MOTOR_ONE 2,7
#define SHOOT_MOTOR_TWO 2,8
#define SHOOTER_FEED_PISTON 2,9

// Sorter
#define SORTING_MOTOR 2,10

// Other Stuff
#define HIGH_LIMIT_SENSOR 2,7
#define LOW_LIMIT_SENSOR 2,8
#define AIR_PRESSURE_SWITCH 2,11
#define AUTONOMOUS_SWITCH 2,12, 2,13
#define FRISBEE_ORIENTATION 2,14
#define SHOOTER_HEIGHT_POT 1,1
#define FRISBEE_ORIENTATION_IR 1,3
#define SORTING_SENSOR 1,4
*/

// Compressor
#define COMPRESSOR 1,11, 1,1 // Compressor

// Drive Modes
#define TANK 0 // Tank mode value
#define TURBO 1 // Turbo mode value
#define STRAIGHT 2 // Straight mode value
#define STRAIGHT_TURBO 3 // Straight turbo mode value

// Magic Numbers
#define NO 0 // Turns stuff off
#define YES 1 // Turns stuff on
#define PRINT_TIME 0. // Printing timer print time
#define AUTONOMOUS_LENGTH 15 // Length of autonomous mode
#define LEFT_PYRAMID_FRONT_ENCODER_VALUE 100
#define RIGHT_PYRAMID_FRONT_ENCODER_VALUE 100
#define LEFT_AUTONOMOUS_TURN_VALUE 25
#define RIGHT_AUTONOMOUS_TURN_VALUE 25
#define AUTONOMOUS_HEIGHT_VALUE 25

#endif // End of fancy version of pragma
