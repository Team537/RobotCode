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
void CollectorManager::RunCollector (int ButtonDeploy, int ButtonRetract, int ButtonCollectOut, int ButtonCollectIn, int ButtonCollectStop, bool IsShooterLocked)
{
	RunCollectorDeploy (ButtonDeploy);
	if (IsShooterLocked)
	{
		RunCollectorRetract (ButtonRetract);
		RunCollectorMotor (ButtonCollectOut, ButtonCollectIn, ButtonCollectStop);
	}
}
void CollectorManager::RunCollectorRetract (int BtnRetract)
{
	if (BtnRetract == PRESSED)
	{
		CollectorDeploy.Set(OFF);
		CollectorRetract.Set(ON);
	}
}
void CollectorManager::RunCollectorDeploy (int BtnDeploy)
{
	if (BtnDeploy == PRESSED)
	{
		CollectorRetract.Set(OFF);
		CollectorDeploy.Set(ON);
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
	if ((CollectorDeploy.Get() == ON) && (CollectorRetract.Get() == OFF))
	{
		return true;
	}
	else
	{
		return false;
	}
}
int CollectorManager::CollectorSpeed()
{
	return (int)CollectorMotor.Get();
}
