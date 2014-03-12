#include "WPILib.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "CameraManager.h"
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
	int ShooterMode;
	
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
	CameraManager Camera2;
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		SecondaryController(SECONDARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{
		ShooterMode = SHOOTER_AUTO;
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
	void UpdateShooterMode()
	{
		if (SecondaryController.GetRawButton(BUTTON_BACK) == PRESSED)
		{
			ShooterMode = SHOOTER_MANUAL;
			Shooter.DisablePIDControl();
		}
		if (SecondaryController.GetRawButton(BUTTON_START) == PRESSED)
		{
			ShooterMode = SHOOTER_AUTO;
			Shooter.ResetShooterState();
		}
		SmartDashboard::PutNumber("Shooter Mode", ShooterMode);
	}
	void RobotInit()
	{
		AutoChooser.AddDefault("Side lineup, High goal", &AutoSide);
		AutoChooser.AddObject("Side lineup, Low goal", &AutoLow);
		AutoChooser.AddObject("Middle Lineup, High goal", &AutoMiddle);
		AutoChooser.AddObject("Drive straight, No goal", &AutoStraight);
		SmartDashboard::PutData("Chooser", &AutoChooser);
	}
	
	void Autonomous()
	{
		DriveTrain.DashboardInitialize();
		Shooter.DashboardInitialize();
		Shooter.StartShooterAuto();
		
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
		DriveTrain.DashboardInitialize();
		Shooter.DashboardInitialize();
		Camera2.CameraStart();
		PrintTime.Start();
		Collector.StartCollectorTeleop();
		DriveTrain.StartDriveTrain();
		Shooter.StartShooterTeleop();
		
		while (IsOperatorControl())
		{
			bool hot = Camera2.IsHotGoal();
			//ACamera2.IsHotGoal();
			UpdateShooterMode();
			comp.checkCompressor();
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), PrimaryController.GetRawButton(BUTTON_COLLECTOR_RETRACT), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT) || PrimaryController.GetRawButton(BUTTON_COLLECT_OUT2), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
			if (ShooterMode == SHOOTER_AUTO)
			{
				Shooter.StateMachine(Collector.SafeToShoot(), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT), &Collector);
			}
			else if (ShooterMode == SHOOTER_MANUAL)
			{
				Shooter.ManualShooter(SecondaryController.GetRawAxis(LEFT_JOYSTICK), SecondaryController.GetRawButton(BUTTON_LATCH_ON), SecondaryController.GetRawButton(BUTTON_LATCH_OFF), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_TRUSS_SHOT), SecondaryController.GetRawButton(BUTTON_PID_DISABLE), Collector.SafeToShoot());
			}
			Shooter.ChargeShooter(SecondaryController.GetRawButton(BUTTON_CHARGE_SHOOTER));
			DriveTrain.DashboardLoop();
			Shooter.DashboardLoop();
			Print();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
