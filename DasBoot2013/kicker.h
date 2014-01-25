#ifndef _KICKER_H_
#define _KICKER_H_

#include "WPILib.h"
#include "PID/PIDControl.h"

#define P_GAIN 2.80
#define I_GAIN 0.01
#define D_GAIN 0.00
#define MAX_ERROR 2.00
#define MAX_OUTPUT 1.00

#define DEADBAND 0.10

#define MAX_TENSION	637
#define MIN_TENSION 725

class Kicker
{
private:
	enum State {E_IDLE, E_COCKING, E_LATCHING, E_COCKED, E_LATCHED, E_READY};
	
	State curState;
	
	DigitalInput *cocked;
	
	Solenoid *kickReset, *kickHook;
	
	Timer latchTimer;
	
	AnalogChannel *pot;
	
	Victor *tension;
	
	bool oldState;
	float curTension;
	
	PosPID PID;
	
public:
	Kicker(Solenoid *resetKick, Solenoid *hookKick, DigitalInput *cockerLimit, AnalogChannel *poten, Victor *tensioner);
	
	void setTension(float tension);
	float getTension();
	
	void kick(bool kicking);
	
	void print();
};

#endif
