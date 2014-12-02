#include "CompressorManager.h"
#include "Schematic.h"

void CompressorManager::checkCompressor()
{
	if (comp.GetPressureSwitchValue() == 1)
		comp.Stop();
	else
		comp.Start();
	SmartDashboard::PutData("compressor", &comp);
	SmartDashboard::PutNumber("compressor2", comp.Enabled());
}

int CompressorManager::getPressureSwitch()
{
	return comp.GetPressureSwitchValue();	
}
