#ifndef AUTOSTRAIGHT_H
#define AUTOSTRAIGHT_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "AutoChoice.h"

class AutonomousStraight : public AutoChoice
{
	Timer AutoTimer;
public:		
	void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	int Test();
private:
	int State;
};

#endif
