#ifndef AUTOMIDDLE_H
#define AUTOMIDDLE_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"
#include "AutonomousChooser.h"

class AutonomousMiddle : public AutoChoice
{
	Timer AutoTimer;
public:		
	void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	int WhichHotGoal;
private:
	int AutoState;
	int BallShot;
	
};

#endif
