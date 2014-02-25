#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "AutonomousMiddle.h"

void AutonomousMiddle::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	AutoState = 1;
}

void AutonomousMiddle::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
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
		case 3: //Detect hot goal
			//Have fun Mr. Coe
			if (WhichHotGoal == 0)
			{
				AutoState = 4;
			}
			else if (WhichHotGoal = 1)
			{
				AutoState = 5;
			}
			break;
			
		case 4: //Turn to hot goal (only for middle)
			DriveTrain->RunDriveTrain(-.5, -.5, 0, 0); //turn left
			if ((BallShot == 0) && (DriveTrain->LeftEncTotal >= 100) || (DriveTrain->RightEncTotal >= 100))
			{
				DriveTrain->RunDriveTrain(0, 0, 0, 0);
				AutoState = 7;
			}
			else if ((DriveTrain->LeftEncTotal >= 100) || (DriveTrain->RightEncTotal >= 100))
			{
				DriveTrain->RunDriveTrain(0, 0, 0, 0);
				AutoState = 8;
			}
			break;
		
		case 5: //Turn to hot goal
			DriveTrain->RunDriveTrain(.5, .5, 0, 0); //turn right
			if ((BallShot == 0) && (DriveTrain->LeftEncTotal >= 100) || (DriveTrain->RightEncTotal >= 100))
			{
				DriveTrain->RunDriveTrain(0, 0, 0, 0);
				AutoState = 7;
			}
			else if ((DriveTrain->LeftEncTotal >= 100) || (DriveTrain->RightEncTotal >= 100))
			{
				DriveTrain->RunDriveTrain(0, 0, 0, 0);
				AutoState = 8;
			}
			break;
		case 6: //Shoot, also brings back to shooter state 3		
			Shooter->StateMachine(Collector->SafeToShoot(), 0, 1);
			BallShot = 1;
			AutoTimer.Start();
			if (AutoTimer.Get() > 2) 
			{
				AutoTimer.Stop();
				AutoTimer.Reset();
				AutoState = 7;
			}
			break;
			
		case 7: //Turn to parallel
			if (WhichHotGoal == 1) //turn left
			{
				AutoState = 4;
			}
			else if (WhichHotGoal == 0) //turn right
			{
				AutoState = 5;
			}
			break;
		case 8: //Auto Done
			break;
	}
}
