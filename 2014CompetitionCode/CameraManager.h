#ifndef CameraManager_h
#define CameraManager_h
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class CameraManager
{
	Timer CameraTimer;
	bool LastValue;
	double Rate;
	int Counter;
	
	
public:

	CameraManager(void)
	{
		Rate = .25;
		Counter = 1;
		
	}
	void CameraInitialize();
	void CameraStop();
	void CameraStart();
	bool IsHotGoal();
private:
	
};
#endif
