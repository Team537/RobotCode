#ifndef SWERVE_H
#define SWERVE_H
#include "Schematic.h"
#include "cmath"
#include "WPILib.h"

class Swerve
{
	
	Victor SFR, SFL, SBR, SBL, AFR, AFL, ABR, ABL;
	double A, B, C, D, Ratio;
	float deadband, deadbandrad;
	
private:
	void SetSpeed();
	void Sort();
public:
	void SetVariables(float Magnitude, float DirectionRadians, float Twist);
	Swerve(void):
		SFR(FR_DRIVE_VICTOR),
		SFL(FL_DRIVE_VICTOR),
		SBR(BR_DRIVE_VICTOR),
		SBL(BL_DRIVE_VICTOR),
		AFR(FR_ANGLE_VICTOR),
		AFL(FL_ANGLE_VICTOR),
		ABR(BR_ANGLE_VICTOR),
		ABL(BL_ANGLE_VICTOR)
	{
		deadband = .05;
		deadbandrad = (PI / 15);
	}
};

#endif
