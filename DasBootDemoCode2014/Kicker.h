#ifndef KICKER_H
#define KICKER_H
#include "Schematic.h"
#include "WPILib.h"

class Kicker
{
	Solenoid  Prime, Lock;
	Timer KickTime;
	
public:
	Kicker(void):
		Prime(PRIME),
		Lock(FIRE)
		{
			KickerState = 0;
		}
		void StartKicker();
		void StateMachine(int btnKick);
		void Manual(int Pon,int Poff, int Lon, int Loff);
private:
	int KickerState;
};
#endif
