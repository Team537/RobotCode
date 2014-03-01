#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class DriveTrainManager
{
	Victor LeftDriveMotor, RightDriveMotor;
	Solenoid DriveShift;
	Encoder LeftDriveEncoder, RightDriveEncoder;
	Timer EncoderTimer;
	PIDController LeftDrivePID, RightDrivePID;
public:
	DriveTrainManager(void):
		LeftDriveMotor(LEFT_DRIVE_MOTOR),
		RightDriveMotor(RIGHT_DRIVE_MOTOR),
		DriveShift(DRIVE_SHIFT),
		LeftDriveEncoder(LEFT_DRIVE_ENCODER,true,CounterBase::k4X),
		RightDriveEncoder(RIGHT_DRIVE_ENCODER,true,CounterBase::k4X),
		LeftDrivePID (0.015, 0, 0.0, &LeftDriveEncoder, &LeftDriveMotor),
		RightDrivePID (-0.015, 0, 0.0, &RightDriveEncoder, &RightDriveMotor)
		{
			LeftDriveEncoder.SetPIDSourceParameter(PIDSource::kDistance);
			LeftDriveEncoder.SetDistancePerPulse(0.05026548);
			LeftDriveEncoder.Start();
			LeftDrivePID.SetAbsoluteTolerance(5);
			
			RightDriveEncoder.SetPIDSourceParameter(PIDSource::kDistance);
			RightDriveEncoder.SetDistancePerPulse(0.05026548);
			RightDriveEncoder.Start();
			RightDrivePID.SetAbsoluteTolerance(5);
		}
	void RunDriveTrain (float Left, float Right, int High, int Low);
	void StartDriveTrain ();
	float LeftSpeed, RightSpeed, LeftRatio, RightRatio;
	int LeftEncTotal, RightEncTotal;
	void SetDistance(int leftdistance, int rightdistance);	
	bool AtDistance();
	void DisablePIDControl();
	void ResetPIDs ();
	void DashboardInitialize();
	void DashboardLoop();
	void ShiftHigh();
	void ShiftLow();
	
private:
	float LeftDifference, RightDifference;
	float OldLeftSpeed, OldRightSpeed;
	
	float ApplyDeadband (float JoystickValue);
	void RunClamping ();
	void RunEncoders ();
	void RunRampSpeed (float LeftNewSpeed, float RightNewSpeed);
	void RunDriveMotors ();
	void RunShifting (int BTNHigh, int BTNLow);
	float Sign (float InputSign);
};

#endif
