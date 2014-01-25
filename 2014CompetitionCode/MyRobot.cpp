#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	float deadband;
	float rampspd;
	float lspd, rspd;
	float prevl, prevr;
	float lenc, renc;
	float spdmax;
	
	Joystick PrimaryController;
	Victor MotorL, MotorR;
	DigitalOutput Shift;
	CompressorManager comp;
	Encoder LEnc, REnc;
	
public:
	RobotDemo(void):
		PrimaryController(CONTROLLER),
		MotorL(VICTL),
		MotorR(VICTR),
		Shift(SHIFT),
		LEnc(LEFT_ENCODER),
		REnc(RIGHT_ENCODER)
	{
		deadband = 0.1;
		rampspd = 0.1;
		spdmax = 1;
	}
	
	float ApplyDeadband (float stick)
	{
		float newvalue = stick;
		if (fabs(newvalue) <= deadband)
		{
			newvalue = 0;
		}
		return newvalue;
	}
	void Clamping (void)
	{
		lspd = min(lspd, spdmax);
		lspd = max(lspd, -spdmax);
		rspd = min(rspd, spdmax);
		rspd = max(rspd, -spdmax);
	}
	void Encoders (void)
	{
		lenc = LEnc.Get()/prevl;
		renc = REnc.Get()/prevr;
		if (lenc > renc)
		{
			lspd *= (renc / lenc);
		}
		else if (renc > lenc)
		{
			rspd *= (lenc / renc);
		}
	}
	void RampSpeed (float LNewSpeed, float RNewSpeed)
	{
		LNewSpeed = ApplyDeadband(LNewSpeed);
		RNewSpeed = -1 * ApplyDeadband(RNewSpeed);
		float LDifference = LNewSpeed - lspd;
		float RDifference = RNewSpeed - rspd;
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
	void SetMotors (void)
	{
		MotorL.SetSpeed(lspd);
		MotorR.SetSpeed(rspd);
		prevl = lspd;
		prevr = rspd;
	}
	void Shifting (void)
	{
		if (PrimaryController.GetRawButton(BUTTON_HIGH) == true)
		{
			Shift.Set(HIGH);
		}
		else if (PrimaryController.GetRawButton(BUTTON_LOW) == true)
		{
			Shift.Set(LOW);
		}
	}
	float Sign (float inputsign)
	{
		if (inputsign > 0)
		{
			inputsign = 1;
		}
		if (inputsign < 0)
		{
			inputsign = -1;
		}
		if (inputsign = 0)
		{
			inputsign = 0;
		}
		return inputsign;
	}
	
	void OperatorControl(void)
	{
		
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			Shifting();
			RampSpeed(PrimaryController.GetRawAxis(LEFT_JOY), PrimaryController.GetRawAxis(RIGHT_JOY));
			//Encoders();
			Clamping();
			SetMotors();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
