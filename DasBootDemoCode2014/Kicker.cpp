#include "Kicker.h"
#include "Schematic.h"

void Kicker::StartKicker()
{
	if (KickerState == 0)
	KickerState == 1;
}

void Kicker::StateMachine(int btnKick)
{
	switch (KickerState){
	case 0:
		KickerState = 1;
		break;
	case 1:
		Prime.Set(1);
		KickTime.Start();
		if(KickTime.Get() >= .25)
		{
			KickTime.Stop();
			KickTime.Reset();
			Lock.Set(1);
			KickerState = 2;
		}
		break;
	case 2:
		KickTime.Start();
		if (KickTime.Get() >=.25)
		{
			KickTime.Stop();
			KickTime.Reset();
			Prime.Set(0);
			KickerState = 3;
		}
		break;
	case 3:
		if(btnKick == 1)
		{
			Lock.Set(0);
			KickTime.Start();
			if (KickTime.Get() >=.25)
			{
				KickerState = 1;
				KickTime.Stop();
				KickTime.Reset();
			}
		}
		break;
	}
}
