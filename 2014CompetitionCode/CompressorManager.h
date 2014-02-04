#ifndef COMPRESSOR_MANAGER_H
#define COMPRESSOR_MANAGER_H
#include "Schematic.h"
#include "WPILib.h"

class CompressorManager
{
Compressor comp;
public:
	CompressorManager(void):
		comp(COMPRESSOR)
		{
		}
	void checkCompressor();
	int getPressureSwitch();
	
private:
	
};

#endif
