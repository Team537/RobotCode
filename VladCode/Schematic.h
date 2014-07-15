#ifndef SCHEMATIC_H
#define SCHEMATIC_H

//Drivetrain 
#define LEFT_DRIVE_MOTOR 1, 1
#define RIGHT_DRIVE_MOTOR 1, 2
#define RIGHT_DRIVE_ENCODER 1,3,1,4
#define LEFT_DRIVE_ENCODER 1,5,1,6
#define LEFT_DRIVE_DIRECTION 1
#define RIGHT_DRIVE_DIRECTION -1
#define DRIVE_SHIFT 1, 1

//Robot Drive Directions
#define LEFT_DRIVE_PID 0.015
#define RIGHT_DRIVE_PID -0.02
#define LEFT_PID_ADJUST -1
#define RIGHT_PID_ADJUST -1

//Compressor
#define COMPRESSOR_SWITCH 1,2
#define COMPRESSOR_RELAY 1,1

//Frisbee Shooter
#define FRISBEE_FLY_WHEEL_VICTOR 1, 3	
#define FRISBEE_FLY_WHEEL_VICTOR2 1,4
#define ADJUST_MOTOR 1, 5
#define PISTON_ON 1, 3
#define PISTON_OFF 1,6

//Basketball Shooter
#define BASKETBALL_FLY_WHEEL_VICTOR 1,5
#define BASKETBALL_FLY_WHEEL_VICTOR2 1,6
#define SHROUD_ADJUST 1,4
#define FEEDER 1,3

//Candy Shooter
#define CANDY_PISTON_ON 1,3
#define CANDY_PISTON_OFF 1,6

//Controller All
#define PRIMARY_CONTROLLER 1
#define HALF_SPEED_BUTTON 5                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
#define LEFT_JOYSTICK 2
#define RIGHT_JOYSTICK 4
#define SHIFT_HIGH 7
#define SHIFT_LOW 8

//Basketball buttons
#define BUTTON_FEEDER 6
#define SHROUD_UP 2A
#define SHROUD_DOWN 3
#define TOGGLE_FLY_WHEEL 5

//Frisbee Buttons
#define FLY_WHEEL_TOGGLE 5
#define SHOOT_BUTTON 6
#define ANGLE_UP 2
#define ANGLE_DOWN 3

//Candy Butons
#define RIGHT_SHOOT_BTN 6
#define LEFT_SHOOT_BTN 5

//Bot Settings
#define SHOOT_TYPE 1,9
#define PRESSED 1
#define NOT_PRESSED 0

#endif
