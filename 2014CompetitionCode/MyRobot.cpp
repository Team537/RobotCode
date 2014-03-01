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
#include "AutoChoice.h"
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
	AutonomousStraight AutoStraight;
	AutonomousLow AutoLow;
	AutonomousSide AutoSide;
	AutonomousMiddle AutoMiddle;
	
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
		AutoChooser.AddDefault("Side lineup, High goal", &AutoSide);
		AutoChooser.AddObject("Side lineup, Low goal", &AutoLow);
		AutoChooser.AddObject("Middle Lineup, High goal", &AutoMiddle);
		AutoChooser.AddObject("Drive straight, No goal", &AutoStraight);
		SmartDashboard::PutData("Chooser", &AutoChooser);

		DriveTrain.DashboardInitialize();
		Shooter.DashboardInitialize();
	}
	
	void Autonomous()
	{
		AutoChoice* autonmousChoice = (AutoChoice*)AutoChooser.GetSelected();
		autonmousChoice->Initialize(&DriveTrain, &Collector, &Shooter);

		//AutoStraight.Initialize(&DriveTrain, &Collector, &Shooter);
				
		while (IsAutonomous())
		{			
			comp.checkCompressor();
			autonmousChoice->Run(&DriveTrain, &Collector, &Shooter);
			//AutoStraight.Run(&DriveTrain, &Collector, &Shooter);	
			DriveTrain.DashboardLoop();		
			Shooter.DashboardLoop();
		}
	}
	
	void OperatorControl(void)
	{
		PrintTime.Start();
		Collector.StartCollectorTeleop();
		DriveTrain.StartDriveTrain();
		Shooter.StartShooterTeleop();
		
		while (IsOperatorControl())
		{
			comp.checkCompressor();
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), PrimaryController.GetRawButton(BUTTON_COLLECTOR_RETRACT), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
			Shooter.ManualShooter(SecondaryController.GetRawAxis(RIGHT_JOYSTICK), SecondaryController.GetRawButton(BUTTON_LATCH_ON), SecondaryController.GetRawButton(BUTTON_LATCH_OFF), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT));
			//Shooter.StateMachine(Collector.SafeToShoot(), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT));
			Shooter.ChargeShooter(SecondaryController.GetRawButton(BUTTON_CHARGE_SHOOTER));
			DriveTrain.DashboardLoop();
			Shooter.DashboardLoop();
			Print();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
