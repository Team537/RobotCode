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
	int AutoState;
	
	Joystick PrimaryController, SecondaryController;
	CompressorManager comp;
	DriveTrainManager DriveTrain;
	CollectorManager Collector;
	ShooterManager Shooter;
	DriverStationLCD* lcd;
	Timer PrintTime, AutoTimer, AutoTimeDrive;
	DigitalInput AutonomousSwitch;
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER),
		SecondaryController(SECONDARY_CONTROLLER),
		lcd(DriverStationLCD::GetInstance()),
		AutonomousSwitch(AUTONOMOUS_SWITCH)
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
	}
	
	void Autonomous ()
	{
		SmartDashboard::PutNumber("Auto State", AutoState);
		
		/*--SETTING THE AUTONOMOUS MODE--
		 * -1 = Low Goal, Side Lineup
		 * 0 = One Ball, High Goal, Side Lineup
		 * 1 = One Ball, High Goal, Middle Lineup
		 * */
		
		switch(AutoState)
			{
				case 0: //Auto start
					BallShot = 0;
					if (AutoMode != -1)//high goal
					{
						AutoState = 1;
					}
					else if (AutoMode == -1)//low goal
					{
						AutoState = 9;
					}
					break;
					
				case 1: //move forward
					DriveTrain.RunDriveTrain(.5, -.5, 0, 0);
					if ((DriveTrain.LeftEncTotal >= 800) || (DriveTrain.RightEncTotal >= 800))
					{
						DriveTrain.RunDriveTrain (0, 0, 0, 0);
						AutoState = 2;
						break;
					}
					
				case 2: //Deploy Collector
					AutoTimer.Start();
					if (AutoTimer.Get() > .5)
					{
						Collector.RunCollector(1, 0, 0, 0, 0, 0);
						AutoTimer.Stop();
						AutoTimer.Reset();
						if (AutoMode == 0)//high, side
						{
							AutoState = 4;
						}
						else if (AutoMode == -1)//low goal
						{
							AutoState = 12;
						}
						else if (AutoMode == 1)//high goal, middle
						{
							AutoState = 3;
						}
						break;
					}
						
				case 3: //Detect hot goal
					//Have fun Mr. Coe
					if (WhichHotGoal == 0)
					{
						AutoState = 5;
					}
					else if (WhichHotGoal = 1)
					{
						AutoState = 6;
					}
					break;

				case 4: //Wait for hot (only with side)
					if (HotGoal == true)
					{
						AutoState = 7;
						break;
					}
					
				case 5: //Turn to hot goal (only for middle)
					DriveTrain.RunDriveTrain(-.5, -.5, 0, 0); //turn left
					if ((BallShot == 0) && (DriveTrain.LeftEncTotal >= 100) || (DriveTrain.RightEncTotal >= 100))
					{
						DriveTrain.RunDriveTrain(0, 0, 0, 0);
						AutoState = 7;
					}
					else if ((DriveTrain.LeftEncTotal >= 100) || (DriveTrain.RightEncTotal >= 100))
					{
						DriveTrain.RunDriveTrain(0, 0, 0, 0);
						AutoState = 12;
					}
					break;					
					
				case 6: //Turn to hot goal
					DriveTrain.RunDriveTrain(.5, .5, 0, 0); //turn right
					if ((BallShot == 0) && (DriveTrain.LeftEncTotal >= 100) || (DriveTrain.RightEncTotal >= 100))
					{
						DriveTrain.RunDriveTrain(0, 0, 0, 0);
						AutoState = 7;
					}
					else if ((DriveTrain.LeftEncTotal >= 100) || (DriveTrain.RightEncTotal >= 100))
					{
						DriveTrain.RunDriveTrain(0, 0, 0, 0);
						AutoState = 12;
					}
					break;
					
				case 7: //Shoot, also brings back to shooter state 3		
					Shooter.StateMachine(Collector.SafeToShoot(), 0, 1);
					BallShot = 1;
					AutoTimer.Start();
					if (AutoTimer.Get() > 2) 
					{
						AutoTimer.Stop();
						AutoTimer.Reset();
						if (AutoMode == 0)//high, side
						{
							AutoState = 12;
						}
						else if (AutoMode == 1)//high, middle
						{
							AutoState = 8;
						}
					}
					break;
					
				case 8: //Turn to parallel
					if (WhichHotGoal == 1) //turn left
					{
						AutoState = 5;
					}
					else if (WhichHotGoal == 0) //turn right
					{
						AutoState = 6;
					}
					break;
					
				case 9: //Move forward to low
					DriveTrain.RunDriveTrain(-.5, .5, 0, 0);
					if ((DriveTrain.LeftEncTotal > 1500) || (DriveTrain.RightEncTotal > 1500))
					{
						AutoState = 10;
						break;
					}
					
				case 10: //Run collector out
					
					DriveTrain.RunDriveTrain (-.25, .25, 0, 0);
					Collector.RunCollector(0,0,1,0,0,1);
					AutoTimer.Start();
					if (AutoTimer.Get() > .75) 
					{
						AutoTimer.Stop();
						AutoTimer.Reset();
						Collector.RunCollector(0,0,0,0,1,1);
						AutoState = 13;
						BallShot = 1;
						break;
					}
					
				case 13: //Push ball into low
					DriveTrain.RunDriveTrain (-.5, .5, 0, 0);
					if ((DriveTrain.LeftEncTotal >= 100) || (DriveTrain.RightEncTotal >= 100))	
					{
						AutoState = 11;
						break;
					}
					
				case 11: //Back up
					DriveTrain.RunDriveTrain(.5, -.5, 0, 0);
					if ((DriveTrain.LeftEncTotal >= -400) || (DriveTrain.RightEncTotal >= -400))
					{
						DriveTrain.RunDriveTrain (0, 0, 0, 0);
						AutoState = 2;
						break;
					}
					
				case 12: //Auto Done
					break;
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
