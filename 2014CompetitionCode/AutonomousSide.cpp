#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "AutonomousSide.h"

void AutonomousSide::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	AutoState = 1;
}

void AutonomousSide::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	switch(AutoState)
	{
			case 1: //move forward
				DriveTrain->RunDriveTrain(.5, -.5, 0, 0);
				if ((DriveTrain->LeftEncTotal >= 800) || (DriveTrain->RightEncTotal >= 800))
				{
					DriveTrain->RunDriveTrain (0, 0, 0, 0);
					AutoState = 2;
					break;
				}
			case 2: //Deploy Collector
				AutoTimer.Start();
				if (AutoTimer.Get() > .5)
				{
					Collector->RunCollector(1, 0, 0, 0, 0, 0);
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 3;
					break;
				}
			case 3: //Wait for hot (only with side)
				if (HotGoal == true)
				{
					AutoState = 4;
					break;
				}
			case 4: //Shoot, also brings back to shooter state 3		
				Shooter->StateMachine(Collector->SafeToShoot(), 0, 1);
				BallShot = 1;
				AutoTimer.Start();
				if (AutoTimer.Get() > 2) 
				{
					AutoTimer.Stop();
					AutoTimer.Reset();
					AutoState = 5;
				}
				break;
			case 5: //Auto Done
				break;
	}
}
