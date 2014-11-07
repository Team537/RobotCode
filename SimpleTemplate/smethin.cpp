#include "smethin.h"
#include "Schematic.h"

void piston::fire(int btnfire, int btnretract){
	if (btnfire == 1)
	{
		thing.Set(1);
	}
	if (btnretract == 1)
	{
		thing.Set(0);
	}
}
