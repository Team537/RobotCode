#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "DriveTrainManager.h"
#include "AutonomousStraight.h"

void AutonomousStraight::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	DriveTrain->ResetPIDs();
}

void AutonomousStraight::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	DriveTrain->SetDistance(60, 60);
	if (DriveTrain->AtDistance())
	{

	}
}
