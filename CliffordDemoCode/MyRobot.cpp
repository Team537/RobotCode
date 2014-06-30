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
	int WhichHotGoal; //1 = right, 0 = left
	int BallShot;
	int AutoMode;
	int LowGoal;
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
	
	}
	void UpdateShooterMode()
	{
		if (PrimaryController.GetRawButton(BUTTON_BACK) == PRESSED)
		{
			ShooterMode = SHOOTER_MANUAL;
			Shooter.DisablePIDControl();
		}
		if (PrimaryController.GetRawButton(BUTTON_START) == PRESSED)
		{
			ShooterMode = SHOOTER_AUTO;
			Shooter.ResetShooterState();
		}
		SmartDashboard::PutNumber("Shooter Mode", ShooterMode);
	}
	void RobotInit()
	{
	
	}
	
	void Autonomous()
	{
		
		while (IsAutonomous() && IsEnabled())
		{			
			/*comp.checkCompressor();
			autonomousChoice->Run(&DriveTrain, &Collector, &Shooter, &Camera2);
			DriveTrain.DashboardLoop();
			Shooter.DashboardLoop();*/
		}
	
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
			UpdateShooterMode();
			comp.checkCompressor();
			
			if (ShooterMode == SHOOTER_AUTO)
			{
				Collector.RunCollector(PrimaryController.GetRawButton(BUTTON_COLLECTOR_TOGGLE), PrimaryController.GetRawButton(BUTTON_COLLECT_OUT) || PrimaryController.GetRawButton(BUTTON_COLLECT_OUT2), PrimaryController.GetRawButton(BUTTON_COLLECT_IN), PrimaryController.GetRawButton(BUTTON_COLLECT_STOP), Shooter.IsShooterLocked());
				DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT));
				Shooter.StateMachine(Collector.SafeToShoot(), PrimaryController.GetRawButton(BUTTON_GOAL_SHOT), &Collector);
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
