#include "WPILib.h"
#include "Schematic.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	bool stop;
	bool spin;
	float newleft;
	float newright;
	float lspd;
	float rspd;
	Joystick stick;
	Victor left, right, flywheel;
	Solenoid high, low, drive, climb, shootpiston;
public:
	RobotDemo(void):
		stick(STICK),
		left(LEFT_MOTOR),
		right(RIGHT_MOTOR),
		flywheel(SPIN_MOTOR),
		high(HIGH_SHIFT),
		low(LOW_SHIFT),
		drive(DRIVE_SHIFT),
		climb(CLIMB_SHIFT),
		shootpiston(SHOOT_PISTON)
	{
		stop = false;
		spin = false;
		newleft = 0;
		newright = 0;
		lspd = 0;
		rspd = 0;
	}
	void Drive()
	{
		newleft = stick.GetRawAxis(LEFT_JOY);
		newright = stick.GetRawAxis(RIGHT_JOY);
		if (fabs(newleft) < .1)
			newleft = 0;
		if (fabs(newright) < .1)
			newright = 0;
		if ((newleft-lspd) > .1)
			lspd += .1;
		else if ((lspd-newleft) > .1)
			lspd -= .1;
		if ((newright-rspd) > .1)
			rspd += .1;
		else if ((rspd-newright) > .1)
			rspd -= .1;
		lspd = min(lspd, 1);
		lspd = max(lspd, -1);
		rspd = min(rspd, 1);
		rspd = max(rspd, -1);
		left.SetSpeed(-lspd);
		right.SetSpeed(rspd);
	}
	void Flywheel()
	{
		if (spin == false and stick.GetRawButton(SPINSTICK) == 1)
		{
			flywheel.SetSpeed(-1);
			spin = true;
		}
		if (spin == true and stick.GetRawButton(SPINSTICK) == 1)
		{
			flywheel.SetSpeed(0);
			spin = false;
		}
	}
	void Shifting()
	{
		if (stick.GetRawButton(CLIMB) == 1)
		{
			drive.Set(0);
			climb.Set(1);
		}
		if (stick.GetRawButton(DRIVE) == 1)
		{
			climb.Set(0);
			drive.Set(1);
		}
		if (stick.GetRawButton(LOW) == 1)
		{
			high.Set(0);
			low.Set(1);
		}
		if (stick.GetRawButton(HIGH) == 1)
		{
			low.Set(0);
			high.Set(1);	
		}
	}
	/*void Shoot()
	{
		if (spin == true and stick.GetRawButton(SHOOT) == 1)
			
	}*/
	void Stop()
	{
		if (stick.GetRawButton(STOP) == 1)
			stop = true;
	}
	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			Stop();
			if (stop == false)
			{
				Drive();
				Shifting();
				Flywheel();
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

