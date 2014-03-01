#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "AutoChoice.h"

void AutoChoice::Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
	SmartDashboard::PutString("Auto Selected", "No Choice");
}

void AutoChoice::Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter)
{
}

AutoChoice::~AutoChoice()
{
}
