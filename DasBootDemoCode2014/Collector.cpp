#include "CollectorManager.h"
#include "Schematic.h"

void CollectorManager::runCollector(int btnOn, int btnOff)
{
	if (btnOn == 1)
	{
		CollectorMotor.Set(1);
	}
	if (btnOff == 1)
	{
		CollectorMotor.Set(0);
	}
}
