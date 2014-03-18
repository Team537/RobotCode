#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "DriveTrainManager.h"
#include "AutonomousStraight.h"

void AutonomousStraight::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera)
{
	SmartDashboard::PutString("Auto Selected", "Auto Straight");
	DriveTrain->ResetPIDs();
	DriveTrain->EncoderReset();
	DriveTrain->ShiftLow();
	State = 1;
}

void AutonomousStraight::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera)
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
void AutonomousStraight::Finished(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera)
{
}
