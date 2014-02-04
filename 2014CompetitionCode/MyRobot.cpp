#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
#include "DriveTrain.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	float timeprint;
	
	Joystick PrimaryController;
	CompressorManager comp;
	DriveTrain tank;
	DriverStationLCD* lcd;
	Timer PrintTime;
	
public:
	RobotDemo(void):
		PrimaryController(CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{
		timeprint = 0.1;
	}
	
	void Print ()
		{
			if (PrintTime.Get() > timeprint)
			{
				lcd->Clear();
				lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Left Joy = %5.4f", PrimaryController.GetRawAxis(LEFT_JOY));
				lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Right Joy = %5.4f", PrimaryController.GetRawAxis(RIGHT_JOY));
				lcd->Printf(DriverStationLCD::kUser_Line3, 1, "Left Speed = %5.4f", tank.LSpeed());
				lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Right Speed = %5.4f", tank.RSpeed());
				lcd->UpdateLCD();
				PrintTime.Reset();
				PrintTime.Start();
			}
		}
	
	void OperatorControl(void)
	{
		PrintTime.Start();
		tank.StartDrive();
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			tank.Drive(PrimaryController.GetRawAxis(LEFT_JOY), PrimaryController.GetRawAxis(RIGHT_JOY), (int)PrimaryController.GetRawButton(BUTTON_HIGH), (int)PrimaryController.GetRawButton(BUTTON_LOW));
			Print();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
