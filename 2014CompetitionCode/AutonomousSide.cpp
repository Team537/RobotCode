#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "AutonomousSide.h"
#include "DriveTrainManager.h"

void AutonomousSide::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera)
{
	SmartDashboard::PutString("Auto Selected", "Auto Side");
	AutoState = 1;
	Shooter->ChargeShooter();
	TotalAutoTime.Start();
	DriveTrain->EncoderReset();
	Camera->CameraStart();
}

void AutonomousSide::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera)
{
	SmartDashboard::PutNumber("Side State", AutoState);
	
	switch(AutoState)
	{
			case 1: //move forward
				DriveTrain->ShiftHigh();
				DriveTrain->SetDistance(-116, -116);
				if (DriveTrain->AtDistance())
				{
					AutoTimer.Start();
					AutoState = 2;
				}
				break;
				
			case 2: //Deploy Collector
				DriveTrain->DisablePIDControl();
				HotGoal = Camera->IsHotGoal();
				if (AutoTimer.Get() > .5)
				{
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 3;
				}
				break;
				
			case 3: //Wait for hot (only with side)
				HotGoal = Camera->IsHotGoal();
				if ((HotGoal) || (TotalAutoTime.Get() >= 6)) 
				{
					TotalAutoTime.Stop();
					TotalAutoTime.Reset();
					AutoState = 4;
				}
				break;
				
			case 4: //Checks if shooter is locked
				if (Shooter->IsShooterLocked())
				{
					AutoState = 5;
					AutoTimer.Start();
				}
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 0, Collector);
				break;
			
			case 5: //Shoot, also brings back to shooter state 3
				if (AutoTimer.Get() > 1)
				{
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 6;
				}
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 1, Collector);
				break;

			case 6: //Auto Done
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 0, Collector);
				Collector->RunCollector(0,0,0,0,1,0);
				break;
	}
}
void AutonomousSide::Finished(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera){
	Camera->CameraStop();
}
