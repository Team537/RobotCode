#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
#include "Swerve.h"

class RobotDemo : public SimpleRobot
{
private:
	Joystick Controller;
	CompressorManager Comp;
	Swerve Sdrive;
	
public:
	RobotDemo(void):
		Controller(CONTROLLER)
	{
	
	}

	void Autonomous()
	{
		
	}

	void OperatorControl()
	{
		while (IsOperatorControl())
		{
			//Comp.checkCompressor();
			Sdrive.SetVariables( Controller.GetMagnitude(),  Controller.GetDirectionRadians(),  Controller.GetTwist());
		}
	}
	
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

