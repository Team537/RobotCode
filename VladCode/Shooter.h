#ifndef SHOOTER_H
#define SHOOTER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class Shooter
{
	Victor /*FrisbeeFlyWheel, FrisbeeFlyWheel2,*/ BasketballFlyWheel, BasketballFlyWheel2, AngleAdjust, Feeder;
	//Solenoid FireOn, FireOff;
	bool FlyWheelSwitch;
	Timer ShootTime;
	int LastPressed;
	
public:
	Shooter(void):
	//FrisbeeFlyWheel (FRISBEE_FLY_WHEEL_VICTOR),
	BasketballFlyWheel (BASKETBALL_FLY_WHEEL_VICTOR),
	//FrisbeeFlyWheel2 (FRISBEE_FLY_WHEEL_VICTOR2),
	BasketballFlyWheel2 (BASKETBALL_FLY_WHEEL_VICTOR2),
	//AngleAdjust (ADJUST_MOTOR),
	AngleAdjust(SHROUD_ADJUST),
	Feeder(FEEDER)
	//FireOn (PISTON_ON),
	//FireOff (PISTON_OFF)
	{
		FlyWheelSwitch = 0;
	}
	void runShooter (int ButtonShoot, int ButtonFlywheel, int ButtonAngleUp, int ButtonAngleDown);
	
	
private:
	void AdjustAngle(int btnAngleUp, int btnAngleDown);
	void StartFlyWheel(int btnFlyWheel,int ButtonShoot);
	void FireObject(int ButtonShoot);
};

#endif
