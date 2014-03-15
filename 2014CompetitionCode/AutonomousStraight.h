#ifndef AUTOSTRAIGHT_H
#define AUTOSTRAIGHT_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CameraManager.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "AutoChoice.h"

class AutonomousStraight : public AutoChoice{
	Timer AutoTimer;
public:		
	void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
	void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
	int Test();
	void Finished(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
private:
	int State;
};

#endif
