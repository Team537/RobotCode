#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "DriveTrainManager.h"
#include "AutonomousLow.h"

void AutonomousLow::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	AutoState = 1;
}

void AutonomousLow::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	switch(AutoState)
	{
		case 1: //Move forward to low
			DriveTrain->RunDriveTrain(-.5, .5, 0, 0);
			if ((DriveTrain->LeftEncTotal > 1500) || (DriveTrain->RightEncTotal > 1500))
			{
				AutoState = 2;
				break;
			}
			
		case 2: //Run collector out	
			DriveTrain->RunDriveTrain (-.25, .25, 0, 0);
			Collector->RunCollector(0,0,1,0,0,1);
			AutoTimer.Start();
			if (AutoTimer.Get() > .75) 
			{
				AutoTimer.Stop();
				AutoTimer.Reset();
				Collector->RunCollector(0,0,0,0,1,1);
				AutoState = 3;
				break;
			}
		case 3: //Push ball into low
			DriveTrain->RunDriveTrain (-.5, .5, 0, 0);
			if ((DriveTrain->LeftEncTotal >= 100) || (DriveTrain->RightEncTotal >= 100))	
			{
				AutoState = 11;
				break;
			}
			
		case 4: //Back up
			DriveTrain->RunDriveTrain(.5, -.5, 0, 0);
			if ((DriveTrain->LeftEncTotal >= -400) || (DriveTrain->RightEncTotal >= -400))
			{
				DriveTrain->RunDriveTrain (0, 0, 0, 0);
				AutoState = 5;
				break;
			}
		case 5: //Deploy Collector
			AutoTimer.Start();
			if (AutoTimer.Get() > .5)
			{
				Collector->RunCollector(1, 0, 0, 0, 0, 0);
				AutoTimer.Stop();
				AutoTimer.Reset();
				AutoState = 6;
			}
		case 6: //Auto Done
			break;		
	}
}
