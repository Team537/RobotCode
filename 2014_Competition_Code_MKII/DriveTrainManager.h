#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "Schematic.h"
//#include "NameSchematic.h"

class DriveTrainManager
{
	Victor LeftDriveMotor, RightDriveMotor;
	Solenoid DriveShift;
	Encoder LeftDriveEncoder, RightDriveEncoder;
	Timer EncoderTimer;
public:
	DriveTrainManager(void):
		LeftDriveMotor(LEFT_DRIVE_MOTOR),
		RightDriveMotor(RIGHT_DRIVE_MOTOR),
		DriveShift(DRIVE_SHIFT),
		LeftDriveEncoder(LEFT_DRIVE_ENCODER,true,CounterBase::k4X),
		RightDriveEncoder(RIGHT_DRIVE_ENCODER,true,CounterBase::k4X)
		{
	
		}
	void RunDriveTrain (float Left, float Right, int High, int Low);
	void StartDriveTrain ();
	float LeftSpeed, RightSpeed, LeftRatio, RightRatio;
	int LeftEncTotal, RightEncTotal;
	
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
