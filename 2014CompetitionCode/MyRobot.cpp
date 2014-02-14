#include "WPILib.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	bool HotGoal;
	int WhichHotGoal;
	int AutonomousState;
	
	Joystick PrimaryController, SecondaryController;
	CompressorManager comp;
	DriveTrainManager DriveTrain;
	CollectorManager Collector;
	ShooterManager Shooter;
	DriverStationLCD* lcd;
	Timer PrintTime, AutoTime;
	DigitalInput AutonomousSwitch;
	
public:

	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		SecondaryController(SECONDARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance()),
		AutonomousSwitch(AUTONOMOUS_SWITCH)
	{
		
	}
	
	void Autonomous ()
	{
		DriveTrain.StartDriveTrain();
		Collector.StartCollector();
		//Shooter.StartShooterAuto();
		AutonomousState = 1;
		while(IsAutonomous())
		{
			if (AutonomousSwitch.Get() == 0)
			{
				if (AutonomousState == 1)
				{
					DriveTrain.RunDriveTrain(1, 1, 0, 0);
					if ((DriveTrain.LeftEncTotal >= 2400) || (DriveTrain.RightEncTotal >= 2400))
					{
						AutonomousState = 2;
					}
				}
				else if ((AutonomousState == 2) && (HotGoal == true))
				{
					Shooter.RunShooter(0, 1, 0);
				}
			}
			else if (AutonomousSwitch.Get() == 1)
			{
				if (AutonomousState == 1)
				{
					DriveTrain.RunDriveTrain(1, 1, 0, 0);
					if ((DriveTrain.LeftEncTotal >= 2400) || (DriveTrain.RightEncTotal >= 2400))
					{
						AutonomousState = 2;
					}
				}
				else if ((AutonomousState == 2) && (WhichHotGoal != 0))
				{
					DriveTrain.RunDriveTrain(WhichHotGoal, -WhichHotGoal, 0, 0);
					if (((WhichHotGoal == 1) && ((DriveTrain.LeftEncTotal >= 2800) || (DriveTrain.RightEncTotal <= 2000))) || ((WhichHotGoal == -1) && ((DriveTrain.LeftEncTotal <= 2000) || (DriveTrain.RightEncTotal >= 2800))))
					{
						AutonomousState = 3;
					}
				}
				else if (AutonomousState == 3)
				{
					Shooter.RunShooter(0, 1, 0);
					AutonomousState = 4;
				}
				else if (AutonomousState == 4)
				{
					DriveTrain.RunDriveTrain(-WhichHotGoal, WhichHotGoal, 0, 0);
					if (((WhichHotGoal == 1) && ((DriveTrain.LeftEncTotal <= 2400) || (DriveTrain.RightEncTotal >= 2400))) || ((WhichHotGoal == -1) && ((DriveTrain.LeftEncTotal >= 2400) || (DriveTrain.RightEncTotal <= 2400))))
					{
						AutonomousState = 5;
					}
				}
			}
		}
	}
	void Print ()
		{
			if (PrintTime.Get() > PRINT_TIME)
			{
				lcd->Clear();
				lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Left Speed = %5.4f", PrimaryController.GetRawAxis(LEFT_JOYSTICK));
				lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Right Speed = %5.4f", PrimaryController.GetRawAxis(RIGHT_JOYSTICK));
				lcd->Printf(DriverStationLCD::kUser_Line3, 1, "Pressure Switch = %d", comp.getPressureSwitch());
				lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Collector speed= %d", Collector.CollectorSpeed());
				lcd->UpdateLCD();
				PrintTime.Reset();
				PrintTime.Start();
			}
		}
	
	void OperatorControl(void)
	{
		PrintTime.Start();
		DriveTrain.StartDriveTrain();
		Collector.StartCollector();
		//Shooter.StartShooterTeleop();
		while (IsOperatorControl())
		{
			Shooter.Safe = Collector.SafeToShoot();
			comp.checkCompressor();
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), PrimaryController.GetRawButton(BUTTON_COLLECTOR_RETRACT), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP));
			//Shooter.RunShooter(SecondaryController.GetRawButton(BUTTON_PRIME_SHOOTER), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT));
			Shooter.PracticeShooter(SecondaryController.GetRawAxis(RIGHT_JOYSTICK), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT));
			Print();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
