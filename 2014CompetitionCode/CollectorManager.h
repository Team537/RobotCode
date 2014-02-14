#ifndef COLLECTOR_H
#define COLLECTOR_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class CollectorManager
{
	Solenoid CollectorRetract, CollectorDeploy;
	Victor CollectorMotor;
public:
	CollectorManager(void):
		CollectorRetract (COLLECTOR_RETRACT),
		CollectorDeploy (COLLECTOR_DEPLOY),
		CollectorMotor (COLLECTOR_MOTOR)
		
		{
		
		}
	void RunCollector (int ButtonDeploy, int ButtonRetract, int ButtonCollectOut, int ButtonCollectIn, int ButtonCollectStop);
	void StartCollector ();
	int CollectorSpeed ();
	bool SafeToShoot ();
	
private:
	int CollectorMotorDirection;
	
	void RunCollectorRetract (int BtnRetract);
	void RunCollectorDeploy (int BtnDeploy);
	void RunCollectorMotor (int SpitOut, int PullIn, int Sit);
	
};

#endif
