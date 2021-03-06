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
	
	int BallShot;
	int ShooterMode;
	
	Joystick PrimaryController
	CompressorManager comp;
	DriveTrainManager DriveTrain;
	CollectorManager Collector;
	ShooterManager Shooter;
	DriverStationLCD* lcd;
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{
		ShooterMode = SHOOTER_AUTO;
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
				Shooter.StateMachine(Collector.SafeToShoot(), SecondaryController.GetRawButton(BUTTON_RESET_SHOT), PrimaryController.GetRawButton(BUTTON_COLLECTOR_DEPLOY), &Collector);
			}
			else if (ShooterMode == SHOOTER_MANUAL)
			{
				Shooter.ManualShooter(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawButton(BUTTON_LATCH_ON), PrimaryController.GetRawButton(BUTTON_LATCH_OFF), PrimaryController.GetRawButton(8), PrimaryController.GetRawButton(BUTTON_GOAL_SHOT), PrimaryController.GetRawButton(BUTTON_PID_DISABLE), Collector.SafeToShoot());
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
