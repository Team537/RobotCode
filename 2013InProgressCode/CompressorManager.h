#ifndef COMPRESSOR_MANAGER_H_
#define COMPRESSOR_MANAGER_H_

#include "WPILib.h"

class CompressorManager
{
public:
	CompressorManager(int switchSlot, int switchChannel, int relaySlot, int relayChannel); 
	~CompressorManager();
private:
	int relaySlot, relayChannel, switchSlot, switchChannel;
	
	Task ourTask;
	
	static void runCompressor(int relaySlot, int relayChannel, int switchSlot, int switchChannel);
};

#endif
