#ifndef CANDY_H
#define CANDY_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class CandyShooter
{
	Solenoid CandyOn, CandyOff;
	bool Toggle1, Toggle2, LastPressedRight, LastPressedLeft;
public:
	CandyShooter(void):
	CandyOn(CANDY_PISTON_ON),
	CandyOff(CANDY_PISTON_OFF)
	{
		Toggle1 = 0;
		Toggle2 = 0;
	}
	void FireCandy(int btnRightShoot, int btnLeftShoot);
private:
	
};

#endif
