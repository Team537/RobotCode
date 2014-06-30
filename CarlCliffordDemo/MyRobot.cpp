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
	
	Joystick PrimaryController;
	CompressorManager comp;
	DriveTrainManager DriveTrain;
	CollectorManager Collector;
	ShooterManager Shooter;
	DriverStationLCD* lcd;
	Timer PrintTime, AutoTimer, AutoTimeDrive;
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance())
	{
		ShooterMode = SHOOTER_AUTO;
	}
	void Print ()
	{
		if (PrintTime.Get() > PRINT_TIME)
		{
			lcd->Clear();
			lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Shooter Axis = %5.4f", PrimaryController.GetRawAxis(LEFT_JOYSTICK));
			lcd->UpdateLCD();
			PrintTime.Reset();
			PrintTime.Start();
		}
	}
	void UpdateShooterMode()
	{
		if (PrimaryController.GetRawButton(BUTTON_MANUAL) == PRESSED)
		{
			ShooterMode = SHOOTER_MANUAL;
			Shooter.DisablePIDControl();
		}
		if (PrimaryController.GetRawButton(BUTTON_AUTO) == PRESSED)
		{
			ShooterMode = SHOOTER_AUTO;
			Shooter.ResetShooterState();
		}
		SmartDashboard::PutNumber("Shooter Mode", ShooterMode);
	}
	void RobotInit()
	{
		SmartDashboard::PutNumber("Yellow Count", 0);
	}
	
	void Autonomous()
	{
	
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
			Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_TOGGLE), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT) || PrimaryController.GetRawButton(BUTTON_COLLECT_OUT2), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
			if (ShooterMode == SHOOTER_AUTO)
			{
				Shooter.StateMachine(Collector.SafeToShoot(), PrimaryController.GetRawButton(BUTTON_RESET_SHOT), PrimaryController.GetRawButton(BUTTON_COLLECTOR_TOGGLE), &Collector);
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
