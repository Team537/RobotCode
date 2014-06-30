#include "WPILib.h"
#include "DriveTrainManager.h"
#include "CompressorManager.h"
#include "Kicker.h"
#include "CollectorManager.h"
#include "Schematic.h"


class RobotDemo : public SimpleRobot
{
private:
		Joystick PrimaryController;
		DriverStationLCD* lcd;
		CompressorManager comp;
		DriveTrain tank;
		CollectorManager collect;
		Kicker kick;
		Timer PrintTime;


public:
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{

	}

	void Autonomous()
	{

	}

	void OperatorControl()
	{
		tank.StartDrive();
		kick.StartKicker();
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			tank.Drive(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			kick.StateMachine(PrimaryController.GetRawButton(BUTTON_KICK));
			collect.runCollector(PrimaryController.GetRawButton(BUTTON_ROLLER_ON), PrimaryController.GetRawButton(BUTTON_ROLLER_OFF));
		}
	}
	

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

