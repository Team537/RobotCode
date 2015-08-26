#ifndef AUTOCHOOSER_H
#define AUTOCHOOSER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "CameraManager.h"
#include "WPILib.h"
#include "CompressorManager.h"
#include "DriveTrainManager.h"
#include "CollectorManager.h"
#include "ShooterManager.h"

class AutoChoice{
public: 
	void Initialize(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
	void Run(DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
	void Finished (DriveTrainManager *DriveTrain, CollectorManager *Collector, ShooterManager *Shooter, CameraManager *Camera);
};
#endif
