#include "WPILib.h"
#include "PID/PIDControl.h"
#include "Schematic.h"
 
class RobotDemo : public SimpleRobot
{
	Joystick cont;
	Victor left, right;
	PosPID drive;

public:
	RobotDemo(void):
		cont(1),
		left(LEFT),
		right(RIGHT)
	{
	}
	
	void Autonomous(void)
	{
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			left.Set(cont.GetRawAxis(2));
			right.Set(cont.GetRawAxis(4));
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

