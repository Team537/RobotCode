#ifndef FRISBEESHOOTER_H
#define FRISBEESHOOTER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class FrisbeeShooter
{
	Victor FlyWheel, FlyWheel2, AngleAdjust,Feeder;
	Solenoid FireOn, FireOff;
	bool FlyWheelSwitch;
	Timer ShootTime;
	int LastPressed;
	
public:
	FrisbeeShooter(void):
	//FlyWheel (FLY_WHEEL_VICTOR),
	FlyWheel (BASKETBALL_FLY_WHEEL_VICTOR),
	//FlyWheel2 (FLY_WHEEL_VICTOR2),
	FlyWheel2 (BASKETBALL_FLY_WHEEL_VICTOR2),
	//AngleAdjust (ADJUST_MOTOR),
	AngleAdjust(SHROUD_ADJUST),
	Feeder(FEEDER),
	FireOn (PISTON_ON),
	FireOff (PISTON_OFF)
	{
		FlyWheelSwitch = 0;
	}
	void runFrisbeeShooter (int ButtonShoot, int ButtonFlywheel, int ButtonAngleUp, int ButtonAngleDown);
	
	
private:
	void AdjustAngle(int btnAngleUp, int btnAngleDown);
	void StartFlyWheel(int btnFlyWheel);
	void FireFrisbee(int btnShoot);
};

#endif
