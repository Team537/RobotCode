#include "CompressorManager.h"
#include "Schematic.h"

void CompressorManager::checkCompressor()
{
	if (comp.GetPressureSwitchValue() == 1)
		comp.Stop();
	else
		comp.Start();
}
