#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "DriveTrainManager.h"
#include "AutonomousStraight.h"

void AutonomousStraight::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	SmartDashboard::PutString("Auto Selected", "Auto Straight");
	DriveTrain->ResetPIDs();
	DriveTrain->ShiftLow();
	State = 1;
}

void AutonomousStraight::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	switch(State)
	{
		case 1:
			DriveTrain->SetDistance(-60, -60);
			if (DriveTrain->AtDistance())
			{
				State = 2;
			}
			break;
		case 2:
			DriveTrain->DisablePIDControl();
			break;
	}
}
