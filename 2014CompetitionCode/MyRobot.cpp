#include "WPILib.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "AutonomousLow.h"
#include "AutonomousSide.h"
#include "AutonomousMiddle.h"
#include "AutonomousStraight.h"
#include "AutonomousChooser.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	bool HotGoal;
	int WhichHotGoal; //1 = right, 0 = left
	int BallShot;
	int AutoMode;
	int LowGoal;
	int HighSide;
	int HighMiddle;
	
	Joystick PrimaryController, SecondaryController;
	CompressorManager comp;
	DriveTrainManager DriveTrain;
	CollectorManager Collector;
	ShooterManager Shooter;
	DriverStationLCD* lcd;
	Timer PrintTime, AutoTimer, AutoTimeDrive;
	SendableChooser AutoChooser;
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		SecondaryController(SECONDARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{
		
	}
	void Print ()
			{
				if (PrintTime.Get() > PRINT_TIME)
				{
					lcd->Clear();
					lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Shooter Axis = %5.4f", SecondaryController.GetRawAxis(LEFT_JOYSTICK));
					lcd->UpdateLCD();
					PrintTime.Reset();
					PrintTime.Start();
				}
			}
	void RobotInit()
	{ 	
		AutonomousLow AutoLow;
		AutonomousSide AutoSide;
		AutonomousMiddle AutoMiddle;
		AutonomousStraight AutoStraight;
	
		AutoChooser.AddDefault("Side lineup, High goal", &AutoSide);
		AutoChooser.AddObject("Side lineup, Low goal", &AutoLow);
		AutoChooser.AddObject("Middle Lineup, High goal", &AutoMiddle);
		AutoChooser.AddObject("Drive straight, No goal", &AutoStraight);
		SmartDashboard::PutData("Chooser", &AutoChooser);
	}
	
	void Autonomous()
	{
		AutoChoice* autonmousChoice = (AutoChoice*)AutoChooser.GetSelected();
		autonmousChoice->Initialize(&DriveTrain, &Collector, &Shooter);
		
		while (IsAutonomous())
		{
			SmartDashboard::PutNumber("Auto Mode", AutoMode);

			/*--SETTING THE AUTONOMOUS MODE--
			 * -1 = Low Goal, Side Lineup
			 * 0 = One Ball, High Goal, Side Lineup
			 * 1 = One Ball, High Goal, Middle Lineup
			 * 2 = Drive Straight
			 * */
			autonmousChoice->Run(&DriveTrain, &Collector, &Shooter);
		}
	}
	
	void OperatorControl(void)
	{
		PrintTime.Start();
		DriveTrain.StartDriveTrain();
		Shooter.StartShooterTeleop();
		Collector.StartCollectorTeleop();
		
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), PrimaryController.GetRawButton(BUTTON_COLLECTOR_RETRACT), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
			Shooter.ManualShooter(SecondaryController.GetRawAxis(RIGHT_JOYSTICK), SecondaryController.GetRawButton(BUTTON_LATCH_ON), SecondaryController.GetRawButton(BUTTON_LATCH_OFF));
			Shooter.StateMachine(Collector.SafeToShoot(), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT));
			Print();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
