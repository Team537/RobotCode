#include "kicker.h"

Kicker::Kicker(Solenoid *resetKick, Solenoid *hookKick, DigitalInput *cockerLimit, AnalogChannel *poten, Victor *tensioner):
	cocked(cockerLimit),
	kickReset(resetKick),
	kickHook(hookKick),
	pot(poten),	
	tension(tensioner),
	PID(P_GAIN, I_GAIN, D_GAIN, MAX_ERROR, MAX_OUTPUT, false)
{
	if(cocked->Get())
		curState = E_COCKED;	
	else
		curState = E_IDLE;
	
	oldState = false;
	
	latchTimer.Start();
	
	
}
//weiners
void Kicker::kick(bool kicking)
{
	if(oldState == true && kicking == false)
	{
		oldState = false;
		kicking = false;
	}
	else if(oldState == false && kicking == true)
	{
		oldState = true;
	}
	else if(oldState == kicking)
	{
		kicking = false;
	}
	
	if(curState == E_IDLE && latchTimer.Get() > 0.50)
	{
		kickReset->Set(false);
		curState = E_COCKING;
		latchTimer.Reset();
	}
	else if(curState == E_COCKING && cocked->Get())
	{
		curState = E_LATCHING;
		latchTimer.Reset();
	}
	else if(curState == E_LATCHING && latchTimer.Get() > 0.75)
	{
		kickHook->Set(false);
		curState = E_COCKED;
		latchTimer.Reset();
	}
	else if(curState == E_COCKED && latchTimer.Get() > 0.25 /*&& kicking*/)
	{
		kickReset->Set(true);
		curState = E_READY;
		latchTimer.Reset();
	}
	else if(curState == E_READY && latchTimer.Get() > 0.50 && kicking)
	{
		kickHook->Set(true);
		curState = E_IDLE;
		latchTimer.Reset();
	}
}

void Kicker::print()
{
	printf("Current State: ");
	
	switch(curState)
	{
	case E_IDLE:
		printf("Idle ");
		break;
	case E_COCKING:
		printf("Cocking ");
		break;
	case E_COCKED:
		printf("Ready to FIRE MAH LAZERS!!! ");
		break;
	case E_LATCHED:
		printf("Latched ");
		break;
	case E_READY:
		printf("Ready to FIRE MAH LAZERS!!! ");
		break;
	case E_LATCHING:
		printf("Latching...");
		break;
	default:
		printf("Undefined ");
		break;
	}
	
	// Add some limit switch checks at some point
	printf("Cocker Limit: ");
	if(cocked->Get())
		printf("Tripped ");
	else
		printf("Un-Tripped ");
	
	printf("Pot: %f\n", curTension);
}


void Kicker::setTension(float newTension)
{
	// PID tension
	curTension = ((float)(pot->GetValue() - ((MAX_TENSION + MIN_TENSION) / 2)) /  ((MIN_TENSION - MAX_TENSION) / 2));
	//newTension = (newTension - ((MAX_TENSION + MIN_TENSION) / 2)) /  ((MIN_TENSION - MAX_TENSION) / 2);
	
	//printf("current: %f    ||   new: %f\n", curTension, newTension);
	
	if(curTension < newTension + DEADBAND && curTension > newTension - DEADBAND)
	{
		tension->Set(0);
		return;
	}
		
	// Set the motor
	tension->Set(PID.Update(curTension, newTension));
}

float Kicker::getTension()
{
	return curTension;
}
