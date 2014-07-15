/*#include "BasketBallShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"

void BasketBallShooterManager::RunBasketBallShooterManager(int ButtonFlyWheel, int ButtonShroudUp, int ButtonShroudDown, int ButtonFeed)
{
	ToggleFlyWheel(ButtonFlyWheel);
	AdjustShroud(ButtonShroudUp, ButtonShroudDown);
	Feed(ButtonFeed);
}

void BasketBallShooterManager::ToggleFlyWheel(int btnToggle)
{
	if((btnToggle == PRESSED) && (PressedLast == NOT_PRESSED))
	{
		if(FlyWheelToggle == 1)
		{
			FlyWheelToggle = 0;
		}
		else if (FlyWheelToggle == 0)
		{
			FlyWheelToggle = 1;
		}
	}
	if (FlyWheelToggle == 1)
	{
		Shooter.Set(.3);
		Shooter2.Set(.3);
	}
	if (FlyWheelToggle == 0)
	{
		Shooter.Set(0);
		Shooter2.Set(0);
	}
	PressedLast = btnToggle;
}

void BasketBallShooterManager::AdjustShroud(int btnShroudUp, int btnShroudDown)
{
	if (btnShroudUp == PRESSED && btnShroudDown == NOT_PRESSED)
	{
		Shroud.Set(1);
	}
	if (btnShroudUp == NOT_PRESSED && btnShroudDown == PRESSED)
	{
		Shroud.Set(1);
	}
}

void BasketBallShooterManager::Feed(int btnFeed)
{
	if (btnFeed == PRESSED)
	{
		Feeder.Set(1);
	}
}*/
