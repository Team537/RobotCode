#ifndef SCHEMATIC_H
#define SCHEMATIC_H

//Constants
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164
#define RAMP_SPEED .1
#define LEFT_DRIVE_DIRECTION 1
#define RIGHT_DRIVE_DIRECTION -1

//Compressor
#define COMPRESSOR_SWITCH 1,2
#define COMPRESSOR_RELAY 1,1

//Victors
#define FL_DRIVE_VICTOR 1,3
#define FR_DRIVE_VICTOR 1,4
#define BL_DRIVE_VICTOR 1,5
#define BR_DRIVE_VICTOR 1,6
#define FL_ANGLE_VICTOR 1,7
#define FR_ANGLE_VICTOR 1,8
#define BL_ANGLE_VICTOR 1,9
#define BR_ANGLE_VICTOR 1,10

//Kintroller
#define CONTROLLER 1

//Frame
#define LENGTH 24
#define WIDTH 26

//Digital Inputs
#define FL_DRIVE_ENCODER 1,11
#define FR_DRIVE_ENCODER 1,12
#define BL_DRIVE_ENCODER 1,13
#define BR_DRIVE_ENCODER 1,14

//Digital Outputs


//Analog Inputs
#define FL_ANGLE_POT 1,15
#define FR_ANGLE_POT 1,16
#define BL_ANGLE_POT 1,17
#define BR_ANGLE_POT 1,18

//Anolog Outputs


//PID
#define AFL_P .01
#define AFR_P .01
#define ABL_P .01
#define ABR_P .01
#define SFL_P .01
#define SFR_P .01
#define SBL_P .01
#define SBR_P .01

#endif
