#include "CollectorManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include <cmath>

void CollectorManager::StartCollector ()
{
	CollectorRetract.Set(ON);
	CollectorDeploy.Set(OFF);
	CollectorMotorDirection = COLLECTOR_MOTOR_STOP;
}
void CollectorManager::StartCollectorTeleop ()
{
	CollectorMotorDirection = COLLECTOR_MOTOR_STOP;
}
void CollectorManager::RunCollector (int ButtonToggle, int ButtonCollectOut, int ButtonCollectIn, int ButtonCollectStop, bool IsShooterLocked)
{
	if (IsShooterLocked)
	{
		RunCollectorToggle (ButtonToggle);
		RunCollectorMotor (ButtonCollectOut, ButtonCollectIn, ButtonCollectStop);
	}
}
bool CollectorManager::RunCollectorToggle (int BtnToggle)
{
	if ((BtnToggle == PRESSED) && (CollectorToggle == false))
	{
		CollectorRetract.Set(ON);
		CollectorDeploy.Set(OFF);
	}
	if ((BtnToggle == PRESSED) && (CollectorToggle == true))
	{
		CollectorDeploy.Set(ON);
		CollectorRetract.Set(OFF);
	}
	if ((BtnToggle != PRESSED) && (CollectorDeploy.Get() == ON))
	{
		CollectorToggle = false;
	}
	if ((BtnToggle != PRESSED) && (CollectorRetract.Get() == ON))
	{
		CollectorToggle = true;
	}
	return CollectorToggle;
	/*if((BtnToggle == PRESSED) && (LastPressed == NOT_PRESSED))
	{
		if(CollectorToggle == true)
		{
			CollectorToggle = false;
		}
		else if (CollectorToggle == false)
		{
			CollectorToggle = true;
		}
	}
	if (CollectorToggle == true)
	{
		CollectorDeploy.Set(ON);
		CollectorRetract.Set(OFF);
	}
	if (CollectorToggle == false)
	{
		CollectorDeploy.Set(OFF);
		CollectorRetract.Set(ON);
	}
	LastPressed = BtnToggle;*/
}

void CollectorManager::RunCollectorMotor (int BtnOut, int BtnIn, int BtnStop)
{
	if (BtnOut != PRESSED)
	{
		if (BtnStop == PRESSED)
		{
			CollectorMotorDirection = 0;
		}
		else if ((BtnIn == PRESSED) && (CollectorMotor.Get() == 0))
		{
			CollectorMotorDirection = 1;
		}
		CollectorMotor.Set(CollectorMotorDirection);
	}
	else if ((BtnOut == PRESSED) && (CollectorMotor.Get() == 0))
	{
		CollectorMotor.Set(-BtnOut);
	}
}
bool CollectorManager::SafeToShoot()
{
	return ((CollectorDeploy.Get() == ON) && (CollectorRetract.Get() == OFF));
}
int CollectorManager::CollectorSpeed()
{
	return (int)CollectorMotor.Get();
}
