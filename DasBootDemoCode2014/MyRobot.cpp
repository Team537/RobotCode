#include "WPILib.h"
#include "DriveTrainManager.h"
#include "CompressorManager.h"
#include "Schematic.h"


class RobotDemo : public SimpleRobot
{
private:
		Joystick PrimaryController;
		Victor RollorMotor;
		DriverStationLCD* lcd;
		CompressorManager comp;
		DriveTrain tank;
		Timer PrintTime;


public:
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		RollorMotor (VICTROLL),
		lcd(DriverStationLCD::GetInstance())
	{

	}
	void rollers ()
	{
		if (PrimaryController.GetRawButton(BUTTON_ROLLER_ON) == true)
			{
				RollorMotor.Set(1);
			}
		else if (PrimaryController.GetRawButton(BUTTON_ROLLER_ON) == false)
		{
			RollorMotor.Set(0);
		}
	}
	void Autonomous()
	{

	}

	void OperatorControl()
	{
		tank.StartDrive();
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			tank.Drive(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
		}
	}
	

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

