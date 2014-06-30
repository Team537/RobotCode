#include "FrisbeeShooter.h"
#include "NameSchematic.h"
#include "Schematic.h"

void FrisbeeShooter::runFrisbeeShooter (int ButtonShoot, int ButtonFlywheel, int ButtonAngleUp, int ButtonAngleDown)
{
	AdjustAngle (ButtonAngleUp, ButtonAngleDown);
	StartFlyWheel (ButtonFlywheel);
	FireFrisbee (ButtonShoot);
	
}
void FrisbeeShooter::AdjustAngle(int btnAngleUp, int btnAngleDown)
{
	if ((btnAngleUp == 1 && btnAngleDown == 0)){
		AngleAdjust.Set(1);
	}
	if ((btnAngleDown == 1) && (btnAngleUp == 0)){
			AngleAdjust.Set(-1);
	}
	if ((btnAngleUp == 0) && (btnAngleDown == 0)){
		AngleAdjust.Set(0);
	}
	if ((btnAngleDown == 0) && (btnAngleUp == 0)){
			AngleAdjust.Set(0);
	}
}
void FrisbeeShooter::StartFlyWheel(int btnFlyWheel)
{
	/*if ((btnFlyWheel == PRESSED) && FlyWheelSwitch == 1)
	{
		FlyWheel.Set(.3);
		FlyWheel2.Set(.3);
	}
	if ((btnFlyWheel == PRESSED) && FlyWheelSwitch == 0)
	{
		FlyWheel.Set(0);
		FlyWheel2.Set(0);
	}
	if ((btnFlyWheel == NOT_PRESSED) && FlyWheel.Get() == .3)
	{
		FlyWheelSwitch = 0;
	}
	if ((btnFlyWheel == NOT_PRESSED) && FlyWheel2.Get() == .3)
	{
			FlyWheelSwitch = 0;
	}
	if ((btnFlyWheel == NOT_PRESSED) && FlyWheel.Get() == 0)
	{
		FlyWheelSwitch = 1;
	}*/
	if((btnFlyWheel == PRESSED) && (LastPressed == NOT_PRESSED))
	{
		if(FlyWheelSwitch == 1)
		{
			FlyWheelSwitch = 0;
		}
		else if (FlyWheelSwitch == 0)
		{
			FlyWheelSwitch = 1;
		}
	}
	if (FlyWheelSwitch == 1)
	{
		FlyWheel.Set(-.3);
		FlyWheel2.Set(-.3);
	}
	if (FlyWheelSwitch == 0)
	{
		FlyWheel.Set(0);
		FlyWheel2.Set(0);
	}
	LastPressed = btnFlyWheel;
}
void FrisbeeShooter::FireFrisbee(int btnShoot)
{
	/*if((btnShoot == 1) && (FireOn.Get() == 0))
	{
		ShootTime.Start();
		if (ShootTime.Get() > 1)
		
		ShootTime.Stop();
		ShootTime.Reset();
		FireOn.Set(1);
		FireOff.Set(0);
		ShootTime.Start();
	}
	if ((ShootTime.Get() >= .5) && FireOn.Get() == 1)
	{
		FireOn.Set(0);
		FireOff.Set(1);
		ShootTime.Stop();
		ShootTime.Reset();
		
	}*/
	if(btnShoot == 1)
	{
		Feeder.Set(-1);
	}
	else
	{
		Feeder.Set(0);
	}
}
