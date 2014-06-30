#include "CollectorManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include <cmath>

void CollectorManager::StartCollector ()
{
	Toggle = 1;
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
	RunCollectorDeploy (ButtonToggle);
	if (IsShooterLocked)
	{
		RunCollectorRetract (ButtonToggle); //1 is retract, 0 is deploy
		RunCollectorMotor (ButtonCollectOut, ButtonCollectIn, ButtonCollectStop);
	}
}
void CollectorManager::RunCollectorRetract (int ButtonToggle)
{
	if ((ButtonToggle == PRESSED) && (CollectorDeploy.Get() == ON) && (Toggle == 1))
	{
		CollectorDeploy.Set(OFF);
		CollectorRetract.Set(ON);
		if (ButtonToggle != PRESSED)
		{
			Toggle = 0;
		}
	}
	/*if ((BtnRetract == PRESSED) && (CollectorDeploy.Get() == OFF))
	{
		CollectorRetract.Set(OFF);
		CollectorDeploy.Set(ON);
		CollectorMotor.Set(.5);
	}*/
}
void CollectorManager::RunCollectorDeploy (int ButtonToggle)
{
	if ((ButtonToggle == PRESSED) && (CollectorDeploy.Get() == ON) && (Toggle == 0))
	{
		CollectorRetract.Set(OFF);
		CollectorDeploy.Set(ON);
		CollectorMotor.Set(.5);
		if (ButtonToggle != PRESSED)
		{
			Toggle = 1;
		}
	}
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
