#include "Ramping.h"

static const float DRIVE_DEADBAND =  .1;

float RampFN(float current, float input)
{
	if (current < DRIVE_DEADBAND && current > -DRIVE_DEADBAND)
	{
		if (input < -DRIVE_DEADBAND)
			current = -DRIVE_DEADBAND;
		else if (input > DRIVE_DEADBAND)
			current = DRIVE_DEADBAND;
		else
			current = 0;

		return current;
	}

	const float tiny = 0.04f;
	
	float out = 3 * pow(input, 2);
	if (out < tiny && out >= 0.0f)
		out = tiny;
	else if (out > tiny && out <= 0.0f)
		out = -tiny;
	
	return current + out;
		
}
