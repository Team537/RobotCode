#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "AutonomousSide.h"
#include "DriveTrainManager.h"

void AutonomousSide::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	SmartDashboard::PutString("Auto Selected", "Auto Side");
	AutoState = 1;
	Shooter->ChargeShooter(1);
}

void AutonomousSide::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	SmartDashboard::PutNumber("Side State", AutoState);
	switch(AutoState)
	{
			case 1: //move forward
				DriveTrain->ShiftLow();
				DriveTrain->SetDistance(120, 120);
				if (DriveTrain->AtDistance())
				{
					AutoTimer.Start();
					AutoState = 2;
				}
				break;
				
			case 2: //Deploy Collector
				DriveTrain->DisablePIDControl();
				Collector->RunCollector(1, 0, 0, 0, 0, 0);
				if (AutoTimer.Get() > .5)
				{
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 3;
				}
				break;
				
			case 3: //Wait for hot (only with side)
				if (HotGoal || true)
				{
					AutoState = 4;
				}
				break;
				
			case 4: //Checks if shooter is locked
				if (Shooter->IsShooterLocked())
				{
					AutoState = 5;
					AutoTimer.Start();
				}
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 0);
				break;
			
			case 5: //Shoot, also brings back to shooter state 3
				if (!Shooter->IsShooterLocked() && AutoTimer.Get() > 2)
				{
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 6;
				}
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 1);
				break;

			case 6: //Auto Done
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 0);
				break;
	}
}
