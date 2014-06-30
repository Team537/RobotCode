
#ifndef COLLECTOR_H
#define COLLECTOR_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class CollectorManager
{
	Solenoid CollectorRetract, CollectorDeploy;
	Victor CollectorMotor;
	Timer CollectorTimer;
	bool CollectorToggle;
public:
	CollectorManager(void):
		CollectorRetract (COLLECTOR_RETRACT),
		CollectorDeploy (COLLECTOR_DEPLOY),
		CollectorMotor (COLLECTOR_MOTOR)
		
		{
		CollectorToggle = true;
		}
	void RunCollector (int ButtonToggle, int ButtonCollectOut, int ButtonCollectIn, int ButtonCollectStop, bool IsShooterLocked);
	void StartCollector ();
	void StartCollectorTeleop ();
	int CollectorSpeed ();
	bool RunCollectorToggle (int BtnToggle);
	bool SafeToShoot();
	
private:
	int CollectorMotorDirection;
	
	
	void RunCollectorMotor (int SpitOut, int PullIn, int Sit);
	
};

#endif
