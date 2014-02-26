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
			DriveTrain->SetDistance(153, 153);
			if (DriveTrain->AtDistance())
			{
				AutoState = 2;
			}
			break;
			
		case 2: //Run collector out
			Collector->RunCollector(0,0,1,0,0,1);
			AutoTimer.Start();
			if (AutoTimer.Get() > .75) 
			{
				AutoTimer.Stop();
				AutoTimer.Reset();
				Collector->RunCollector(0,0,0,0,1,1);
				AutoState = 3;
			}
			break;
			
		case 3: //Push ball into low
			DriveTrain->SetDistance(29, 29);
			if (DriveTrain->AtDistance())
			{
				AutoState = 4;
			}
			break;
			
		case 4: //Back up
			DriveTrain->SetDistance(-20, -20);
			if (DriveTrain->AtDistance())
			{
				DriveTrain->RunDriveTrain (0, 0, 0, 0);
				AutoState = 5;
			}
			break;
	
		case 5: //Auto Done
			break;		
	}
}
