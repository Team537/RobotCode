#include "WPILib.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "CameraManager.h"
#include "AutonomousSide.h"
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
	AutonomousSide AutoSide;
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
		SmartDashboard::PutNumber("Yellow Count", 0);
		Camera2.CameraInitialize();
		AutoChooser.AddDefault("Side lineup, High goal", &AutoSide);
		AutoChooser.AddObject("Drive straight, No goal", &AutoStraight);
		SmartDashboard::PutData("Chooser", &AutoChooser);
	}
	
	void Autonomous()
	{
		DriveTrain.DashboardInitialize();
		Shooter.DashboardInitialize();
		Shooter.StartShooterAuto();
		
		AutoChoice* autonomousChoice = (AutoChoice*)AutoChooser.GetSelected();
		autonomousChoice->Initialize(&DriveTrain, &Collector, &Shooter, &Camera2);
		
		//AutoStraight.Initialize(&DriveTrain, &Collector, &Shooter);
		while (IsAutonomous() && IsEnabled())
		{			
			comp.checkCompressor();
			autonomousChoice->Run(&DriveTrain, &Collector, &Shooter, &Camera2);
			DriveTrain.DashboardLoop();		
			Shooter.DashboardLoop();
		}
		autonomousChoice->Finished(&DriveTrain, &Collector, &Shooter, &Camera2);
	}
	void OperatorControl(void)
	{
		DriveTrain.DashboardInitialize();
		Shooter.DashboardInitialize();
		PrintTime.Start();
		Collector.StartCollectorTeleop();
		DriveTrain.StartDriveTrain();
		Shooter.StartShooterTeleop();
		
		while (IsOperatorControl() && IsEnabled())
		{
			//ACamera2.IsHotGoal();
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
			UpdateShooterMode();
			comp.checkCompressor();
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), PrimaryController.GetRawButton(BUTTON_COLLECTOR_RETRACT), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT) || PrimaryController.GetRawButton(BUTTON_COLLECT_OUT2), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
			if (ShooterMode == SHOOTER_AUTO)
			{
				Shooter.StateMachine(Collector.SafeToShoot(), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_RESET_SHOT), &Collector);
			}
			else if (ShooterMode == SHOOTER_MANUAL)
			{
				Shooter.ManualShooter(SecondaryController.GetRawAxis(LEFT_JOYSTICK), SecondaryController.GetRawButton(BUTTON_LATCH_ON), SecondaryController.GetRawButton(BUTTON_LATCH_OFF), SecondaryController.GetRawButton(8), SecondaryController.GetRawButton(BUTTON_GOAL_SHOT), SecondaryController.GetRawButton(BUTTON_PID_DISABLE), Collector.SafeToShoot());
			}
			Shooter.ChargeShooter();
			DriveTrain.DashboardLoop();
			Shooter.DashboardLoop();
			Print();
		}
		SmartDashboard::PutBoolean("Disabled", IsEnabled());
		
	}
};

START_ROBOT_CLASS(RobotDemo);
