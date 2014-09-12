#include "CandyShooter.h"
#include "NameSchematic.h"
#include "Schematic.h"

void CandyShooter::FireCandy(int btnRightShoot, int btnLeftShoot){
	if (btnRightShoot == 1 && LastPressedRight == NOT_PRESSED){
		if (Toggle1 == 1){
			Toggle1 = 0;
		}
		else if (Toggle1 == 0){
			Toggle1 = 1;
		}
	}
	LastPressedRight = btnRightShoot;
	if (Toggle1 == 1)
	{
		CandyOn.Set(1);
		CandyOff.Set(0);
	}
	if(Toggle1 == 0)
	{
		CandyOn.Set(0);
		CandyOff.Set(1);
	}
}


