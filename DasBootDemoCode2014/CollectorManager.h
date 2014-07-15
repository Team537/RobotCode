#ifndef COLLECTOR_H
#define COLLECTOR_H
#include "Schematic.h"
#include "WPILib.h"

class CollectorManager
{
	Victor CollectorMotor;

public:
	CollectorManager(void):
		CollectorMotor (COLLECTOR_MOTOR)
		
		{
		
		}
	void runCollector(int btnOn);
private:
	
};
#endif
