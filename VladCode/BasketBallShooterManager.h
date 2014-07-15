/*
 * #ifndef BASKETBALLSHOOTERMANAGER_H
#define BASKETBALLSHOOTERMANAGER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class BasketBallShooterManager
{
	Victor Shooter, Shooter2, Shroud, Feeder;
	bool FlyWheelToggle;
	int PressedLast;
	
public:
	BasketBallShooterManager(void):
	Shooter(BASKETBALL_FLY_WHEEL_VICTOR),
	Shooter2(BASKETBALL_FLY_WHEEL_VICTOR2),
	Shroud(SHROUD_ADJUST),
	Feeder(FEEDER)
	{
		FlyWheelToggle = true;
	}
	void RunBasketBallShooterManager(int ButtonFlyWheel, int ButtonShroudUp, int ButtonShroudDown, int ButtonFeed);
private:
	void ToggleFlyWheel(int btnToggle);
	void AdjustShroud(int btnShroudUp, int btnShroudDown);
	void Feed(int btnFeed);
};
#endif
