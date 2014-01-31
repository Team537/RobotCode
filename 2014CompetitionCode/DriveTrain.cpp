#include "DriveTrain.h"
#include "Schematic.h"
#include <cmath>

void DriveTrain::StartDrive()
{
	LEnc.SetDistancePerPulse(0.45);
	REnc.SetDistancePerPulse(0.45);
	LEnc.Start();
	REnc.Start();
	Shift.Set(LOW);
}
void DriveTrain::Drive(float Left, float Right, int High, int Low)
{
	Shifting(High, Low);
	RampSpeed(Left, Right);
	Encoders();
	Clamping();
	SetMotors();
}
float DriveTrain::LSpeed()
{
	return lspd;
}
float DriveTrain::RSpeed()
{
	return rspd;
}
float DriveTrain::ApplyDeadband (float stick)
	{
		float newvalue = stick;
		if (fabs(newvalue) <= deadband)
		{
			newvalue = 0;
		}
		return newvalue;
	}
void DriveTrain::Clamping (void)
	{
		lspd = min(lspd, spdmax);
		lspd = max(lspd, -spdmax);
		rspd = min(rspd, spdmax);
		rspd = max(rspd, -spdmax);
	}
void DriveTrain::Encoders ()
	{
		lenc = LEnc.Get() / prevl;
		renc = REnc.Get() / prevr;
		
		if (lenc > renc)
		{
			lspd *= (renc / lenc);
		}
		else if (renc > lenc)
		{
			rspd *= (lenc / renc);
		}
		LEnc.Reset();
		REnc.Reset();
	}
void DriveTrain::RampSpeed (float LNewSpeed, float RNewSpeed)
	{
		LNewSpeed = LEFT_DIRECTION * ApplyDeadband(LNewSpeed);
		RNewSpeed = RIGHT_DIRECTION * ApplyDeadband(RNewSpeed);
		LDifference = LNewSpeed - lspd;
		RDifference = RNewSpeed - rspd;
		if (fabs(LDifference) >= rampspd)
		{
			lspd += rampspd * Sign(LDifference);
		}
		if (fabs(RDifference) >= rampspd)
		{
			rspd += rampspd * Sign(RDifference);
		}
		if (LNewSpeed == 0)
		{
			lspd = 0;
		}
		if (RNewSpeed == 0)
		{
			rspd = 0;
		}
	}
void DriveTrain::SetMotors (void)
	{
		MotorL.SetSpeed(lspd);
		MotorR.SetSpeed(rspd);
		prevl = lspd;
		prevr = rspd;
	}
void DriveTrain::Shifting (int BTNHigh, int BTNLow)
	{
		if (BTNHigh == 1)
		{
			Shift.Set(HIGH);
		}
		else if (BTNLow == 1)
		{
			Shift.Set(LOW);
		}
	}
float DriveTrain::Sign (float inputsign)
	{
		if (inputsign > 0)
		{
			return 1;
		}
		if (inputsign < 0)
		{
			return -1;
		}
		return 0;
	}
