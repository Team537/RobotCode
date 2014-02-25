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
		LeftDrivePID (0.1, 0, 0, &LeftDriveEncoder, &LeftDriveMotor),
		RightDrivePID (0.1, 0, 0, &RightDriveEncoder, &RightDriveMotor)
		{
					LeftDriveEncoder.SetPIDSourceParameter(PIDSource::kDistance);
					LeftDriveEncoder.Start();
					LeftDrivePID.SetAbsoluteTolerance(10);
					LeftDriveEncoder.SetDistancePerPulse(0.05026548);
					RightDriveEncoder.SetPIDSourceParameter(PIDSource::kDistance);
					RightDriveEncoder.Start();
					RightDrivePID.SetAbsoluteTolerance(10);
					RightDriveEncoder.SetDistancePerPulse(0.05026548);
		}
	void RunDriveTrain (float Left, float Right, int High, int Low);
	void StartDriveTrain ();
	float LeftSpeed, RightSpeed, LeftRatio, RightRatio;
	int LeftEncTotal, RightEncTotal;
	void SetDistance(int leftdistance, int rightdistance);	
	bool AtDistance();
	void ResetPIDs ();
	
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
