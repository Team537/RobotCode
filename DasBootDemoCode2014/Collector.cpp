#include "CollectorManager.h"
#include "Schematic.h"

void CollectorManager::runCollector(int btnOn)
{
	if (btnOn == 1)
	{
		CollectorMotor.Set(1);
	}
	else
	{
		CollectorMotor.Set(0);
	}
}
