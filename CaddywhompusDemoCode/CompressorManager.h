#ifndef COMPRESSOR_MANAGER_H_
#define COMPRESSOR_MANAGER_H_
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
	bool Switch();
	
private:
	
};

#endif
