#ifndef SMETHIN_H
#define SMETHIN_H

#include "Schematic.h"
#include "WPILib.h"

class piston
{
	Solenoid thing;
	
public:
	piston (void):
	thing (PISTON)
	{
		
	}
	void fire(int btnfire, int btnretract);
private:
	

};
#endif
