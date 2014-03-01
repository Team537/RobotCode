#ifndef AUTOCHOOSER_H
#define AUTOCHOOSER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"

class AutoChoice
{
public: 
	virtual void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	virtual void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter);
	virtual ~AutoChoice() = 0;
};
#endif
