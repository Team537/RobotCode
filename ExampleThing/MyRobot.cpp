#include "WPILib.h"
#include "Schematic.h"
class RobotDemo : public SimpleRobot
{
private:
	
	float x;
	float y;
	Joystick controller;
	DriverStationLCD* lcd;
	Timer printtime;
	
public:

	RobotDemo(void):
		
		controller(CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	
	{
		
	}

	void Autonomous(void)
	{	
		while (IsAutonomous())
		{
			fjdalfjalfj
		}
	}

	void OperatorControl(void)
	{
		
		while (IsOperatorControl())
		{	
			x = controller.GetRawAxis(XAXIS);
			y = controller.GetRawAxis(YAXIS);
			if (printtime.Get() > PRINT_TIME)
			{
				lcd->Clear();
				lcd->Printf(DriverStationLCD::kUser_Line1, 1, "X Axis = %5.4f", x);
				lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Y Axis = %5.4f", y);
				lcd->UpdateLCD();
				printtime.Reset();
				printtime.Start();
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
