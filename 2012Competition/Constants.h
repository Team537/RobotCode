#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define RAMP_SPD .1

#define FW_P_GAIN        2.1
#define FW_I_GAIN        0
#define FW_D_GAIN    	 27
#define FW_MAX_ERROR  250
#define FW_MAX_OUTPUT 250

#define YAW_P_GAIN 0.05
#define YAW_I_GAIN 0
#define YAW_D_GAIN 0
#define YAW_MAX_ERROR 2
#define YAW_MAX_OUTPUT .5

#define PCH_P_GAIN 0.05
#define PCH_I_GAIN 0
#define PCH_D_GAIN 0
#define PCH_MAX_ERROR 2
#define PCH_MAX_OUTPUT .5

#define PITCH_MAX 800
#define PITCH_MIN 265
#define PITCH_DEAD 0.05

#define YAW_MAX 880
#define YAW_MIN 330
#define YAW_DEAD 0.05

#define FLY_MAX
#define FLY_MIN

#define GEAR 15 // high = 1, low = 0
#define PUSHER 16 //down = 1, up = 0
#define BALL_COUNT 17 //0,1,2,3
#define CLCT 18  // down = 0, stop  = 1, up = 2
#define CENTER_BAR 21 // 0 <---> 640
#define ACTUAL 2
#define WANTED 4
#define CURR_ANGLE 23 //the val
#define CURR_PRESET 22 //manual=0 bridge=1 back=2 front=3 fender=4

#endif
