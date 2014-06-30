#ifndef SCHEMATIC_H
#define SCHEMATIC_H

// Primary Controller
#define PRIMARY_CONTROLLER 1
#define LEFT_JOYSTICK 2
#define RIGHT_JOYSTICK 4
#define BUTTON_LOW_DRIVE_SHIFT 7
#define BUTTON_HIGH_DRIVE_SHIFT 8

// Robot Victors
#define LEFT_DRIVE_MOTOR 1,1
#define RIGHT_DRIVE_MOTOR 1,2

// Robot Compressor
#define COMPRESSOR_SWITCH 1,2
#define COMPRESSOR_RELAY 1,1

// Robot Digital Inputs
#define RIGHT_DRIVE_ENCODER 1,3,1,4
#define LEFT_DRIVE_ENCODER 1,5,1,6

// Robot Digital Outputs
#define DRIVE_SHIFT 1,1

#define LEFT_DRIVE_DIRECTION 1
#define RIGHT_DRIVE_DIRECTION -1

#endif
