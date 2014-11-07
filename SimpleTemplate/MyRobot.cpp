#incl=ude "WPILib.h"
#include "Schematic.h"
#include "smethin.h"
#include "CompressorManager.h"

class RobotDemo : public SimpleRobot
{
private:
	Joystick controller;
	piston pist;
	CompressorManager comp;
	
public:
	RobotDemo():
	controller(CONTROLLER)
	{
		
	}

	
	void Autonomous()
	{
	
	}

	void OperatorControl()
	{
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			pist.fire(controller.GetRawButton(1), controller.GetRawButton(2));
		}
	}

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

