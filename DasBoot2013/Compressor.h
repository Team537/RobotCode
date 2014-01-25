#include "Schematic.h"
#include "WPILib.h"

class CompressorManager
{
Compressor comp;
public:
	CompressorManager():
		
		comp(COMPRESSOR)
		{
		}
	
	void checkCompressor();
	
private:
	
};
