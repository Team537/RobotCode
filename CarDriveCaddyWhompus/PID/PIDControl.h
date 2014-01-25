//Header guard definitions
#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include "WPILib.h"
#include "../dashData/dashData.h"
//Positional PID class
class PosPID
{
private:
	bool invert;
	float pGain;
	float iGain;
	float dGain;
	float totalError;
	float previousError;
	float maxError;
	dashData* debug;


public:

	float maxOut;
	float errorToTarget;

	void adjustPGain(float newPGain);
	void adjustIGain(float newIGain);
	void adjustDGain(float newDGain);
	float getPGain(void);
	float getIGain(void);
	float getDGain(void);
	float Update(float distanceToTarget);
	float Update(float currentLocation, float target);
	void Reset(void);
	void setDebug(dashData* dbg);

//Constructor
	PosPID(float pGain, float iGain, float dGain, float maxError, float maxOutput, bool invert = false)
	{
		this->pGain = pGain;
		this->iGain = iGain;
		this->dGain = dGain;
		this->maxError = maxError;
		previousError = 0;
		totalError = 0;
		this->invert = invert;
		maxOut = maxOutput;
		debug = NULL;
	}

};

#endif
