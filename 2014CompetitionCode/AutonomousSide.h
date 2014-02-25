#ifndef AUTOSIDE_H
#define AUTOSIDE_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"

class AutonomousSide
{
	Timer AutoTimer;
public:		
	void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	int HotGoal;
private:
	int AutoState;
	int BallShot;
};

#endif
