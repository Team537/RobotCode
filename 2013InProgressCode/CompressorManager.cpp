#include "CompressorManager.h"

CompressorManager::CompressorManager(int switchSlot, int switchChannel, int relaySlot, int relayChannel)
 : ourTask("Compressor", (FUNCPTR)runCompressor)
{
	this->relaySlot = relaySlot;
	this->relayChannel = relayChannel;
	this->switchSlot = switchSlot;
	this->switchChannel = switchChannel;

	ourTask.Start(switchSlot, switchChannel, relaySlot, relayChannel);
}

CompressorManager::~CompressorManager()
{
	ourTask.Stop();
}
void CompressorManager::runCompressor(int relaySlot, int relayChannel, int switchSlot, int switchChannel)
{
	Relay relay(relaySlot, relayChannel, Relay::kForwardOnly);
	DigitalInput pSwitch(switchSlot, switchChannel);
	
	while(1)
	{
		if(!pSwitch.Get())
		{
			relay.Set(Relay::kOn);
		}
		else
		{
			relay.Set(Relay::kOff);
		}
	}
}
