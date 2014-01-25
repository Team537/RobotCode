#include "Ramping.h"

//TODO: put this in the drivetrain class
static const float DRIVE_DEADBAND =  .1;

float CubicRamp(float current, float input, float dx)
{
	// Give a small value if we are currently at zero and want to start moving.
	if(current < DRIVE_DEADBAND && current > -DRIVE_DEADBAND)
	{
		if(input < -DRIVE_DEADBAND)
			current = -DRIVE_DEADBAND;
		else if(input > DRIVE_DEADBAND)
			current = DRIVE_DEADBAND;
		else
			current = 0;
		
		return current;
	}
	
	// Find the slope of y = x^3 at current state.
	float dy = 3 * pow(current, 2) * dx;
	
	// Add or Subtract the speed differences
	if(input > current)
		current += dy;
	else if(input < current)
		current -= dy;
	
	return current;
}
