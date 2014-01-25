#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
class RobotDemo : public SimpleRobot
{
	Joystick stick;
	Victor flywheel;
	Solenoid piston;
	Timer clock;
	CompressorManager comp;
public:
	RobotDemo(void):
		stick(1),
		flywheel(FLYWHEEL),
		piston(PISTON)
	{	}
	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			if (stick.GetRawButton(1) == true)
				flywheel.SetSpeed(1);
			if (stick.GetRawButton(2) == true)
				flywheel.SetSpeed(0);
			if (stick.GetRawButton(3) == true and piston.Get() == false)
			{
				clock.Reset();
				piston.Set(true);
				clock.Start();
			}
			if (piston.Get() == true and clock.Get() > .25)
			{
				clock.Stop();
				piston.Set(false);
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

