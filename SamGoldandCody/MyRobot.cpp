#include "WPILib.h"
 
class RobotDemo : public SimpleRobot
{
private:
	Joystick controller;
	Solenoid Number1, Number2;
	bool solFired;
public:
	RobotDemo(void):
		controller(1), Number1(1,1), Number2 (1,2)	
	{
		solFired = false;
	}

	void Autonomous(void)
	{
		
	}

//comments yay
	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			if(controller.GetRawButton(2) && solFired == false)
			{
				solFired = true;
				Number1.Set(true);
				Number2.Set(false);
			}
			else if (controller.GetRawButton(2) == false)
			{
				solFired = false;
				Number1.Set(false);
				Number2.Set(true);
			}
		}
		
	}
	
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

