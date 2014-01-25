#include "WPILib.h"
#include "math.h"
#include "PID/PIDControl.h"
#include "kicker.h"
#include "Schematic.h"
#include "Compressor.h"

double sign (double num)
{
	int sign;
	if (num == 0)
		sign = 0;
	if (num > 0)
		sign = 1;
	if (num < 0)
		sign = -1;
	return sign;
}
double lstk = 0;
double rstk = 0;
double lspd = 0;
double rspd = 0;
double deadband = 0.15;
double spdmax = 0.75;
double kick = 0;
class RobotDemo : public SimpleRobot
{
	Joystick cont;
	Victor left, right, ball;
	Solenoid reset, hook;
	Timer latchTimer;
	
	Victor springTension;
	
	Solenoid kickReset, kickHook, breaker, armRelease;
	
	// kicker stuff
	AnalogChannel pot;
	DigitalInput cockerLimit;
	Kicker kicker;
	CompressorManager compressor;
	
public:
	RobotDemo(void):
		cont (1),
		left (1, 1),
		right (1, 2),
		ball (1, 5),
		reset (1, 1),
		hook (1, 2),
		springTension(1,3),
		kickReset(1,1),
		kickHook(1,2),
		breaker(1,4),
		armRelease(1,6),
		cockerLimit (1,7),
		pot(1,5),
		kicker(&kickReset, &kickHook, &cockerLimit, &pot, &springTension)
	{
	}
	void Autonomous(void)
	{
	}
	void OperatorControl(void)
	{
		compressor.checkCompressor();
		left.SetSpeed(0);
		right.SetSpeed(0);
		while (IsOperatorControl())
		{
			if (cont.GetRawButton(8) == true)
				spdmax = 1;
			else if (cont.GetRawButton(7) == true)
				spdmax = 0.5;
			else
				spdmax = 0.75;
			if (cont.GetRawButton(5) == true)
				ball.SetSpeed(1);
			else
				ball.SetSpeed(0);
			if (kick == 1)
				kick = 0;
			if (kick = 0 && cont.GetRawButton(6) == true)
				kick = 1;
			lstk = cont.GetRawAxis(2);
			rstk = cont.GetRawAxis(4);
			if (fabs(lstk) < deadband)
				lstk = 0;
			if (fabs(rstk) < deadband)
				rstk = 0;
			if (lstk == 0)
				lspd -= (deadband * sign(lspd));
			else if ((lstk - lspd) > deadband)
				lspd += (deadband * sign(lstk));
			else
				lspd = lstk;
			if (rstk == 0)
				rspd -= (deadband * sign(rspd));
			else if ((rstk - rspd) > deadband)
				rspd += (deadband * sign(rstk));
			else
				rspd = rstk;
			lspd = min(spdmax, lspd);
			lspd = max(-spdmax, lspd);
			rspd = min(spdmax, rspd);
			rspd = max(-spdmax, rspd);
			if (lstk == 0 && lspd != 0)
				lspd = 0;
			if (rstk == 0 && rspd != 0)
				rspd = 0;
			left.SetSpeed(-lspd);
			right.SetSpeed(rspd);
			
			if (cont.GetRawButton(6) == true)
				kicker.kick(true);
			
			kicker.setTension(.85);
		}
	}
};
START_ROBOT_CLASS(RobotDemo);
