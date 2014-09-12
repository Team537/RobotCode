#include "DriveTrainManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include <cmath>

void DriveTrainManager::StartDriveTrain() {
	LeftDriveEncoder.SetDistancePerPulse(0.45);
	RightDriveEncoder.SetDistancePerPulse(0.45);
	LeftDriveEncoder.Start();
	RightDriveEncoder.Start();
	EncoderTimer.Start();
	DriveShift.Set(LOW_GEAR);
	LeftEncTotal = 0;
	RightEncTotal = 0;
}
void DriveTrainManager::ResetPIDs() {
	LeftDrivePID.Reset();
	RightDrivePID.Reset();
}
void DriveTrainManager::RunDriveTrain(float JoystickForward, float JoystickTwist, int ButtonHighShift, int ButtonLowShift) {
	RunShifting(ButtonHighShift, ButtonLowShift);
	RunRampSpeed(JoystickForward, JoystickTwist);
	//RunEncoders();
	RunClamping();
	RunDriveMotors();
}
float DriveTrainManager::ApplyDeadband(float JoystickValue) {
	if (fabs(JoystickValue) <= DEADBAND) {
		JoystickValue = 0;
	}
	return JoystickValue;
}
void DriveTrainManager::RunClamping(void) {
	LeftSpeed = min(LeftSpeed, MAX_SPEED);
	LeftSpeed = max(LeftSpeed, -MAX_SPEED);
	RightSpeed = min(RightSpeed, MAX_SPEED);
	RightSpeed = max(RightSpeed, -MAX_SPEED);
}
void DriveTrainManager::RunEncoders() {
	if (EncoderTimer.Get() > ENCODER_TIME) {
		LeftRatio = LeftDriveEncoder.Get() / OldLeftSpeed;
		RightRatio = RightDriveEncoder.Get() / OldRightSpeed;
		if (LeftRatio > RightRatio) {
			LeftSpeed *= (RightRatio / LeftRatio);

		} else if (RightRatio > LeftRatio) {
			RightSpeed *= (LeftRatio / RightRatio);
		}
		LeftEncTotal += LeftDriveEncoder.Get();
		RightEncTotal += RightDriveEncoder.Get();
		LeftDriveEncoder.Reset();
		RightDriveEncoder.Reset();
		EncoderTimer.Reset();
	}
}
void DriveTrainManager::RunRampSpeed(float, LeftNewSpeed, float RightNewSpeed, float ForwardSpeed, float RotationSpeed) {
	LeftNewSpeed = LEFT_DRIVE_DIRECTION * (ApplyDeadband(ForwardSpeed) + ApplyDeadband(RotationSpeed));
	RightNewSpeed = RIGHT_DRIVE_DIRECTION * (ApplyDeadband(ForwardSpeed) - ApplyDeadband(RotationSpeed));
	LeftDifference = LeftNewSpeed - LeftSpeed;
	RightDifference = RightNewSpeed - RightSpeed;
	if (fabs(LeftDifference) >= RAMP_SPEED) {
		LeftSpeed += RAMP_SPEED * Sign(LeftDifference);
	}
	if (fabs(RightDifference) >= RAMP_SPEED) {
		RightSpeed += RAMP_SPEED * Sign(RightDifference);
	}
	if (LeftNewSpeed == 0) {
		LeftSpeed = 0;
	}
	if (RightNewSpeed == 0) {
		RightSpeed = 0;
	}
}
void DriveTrainManager::RunDriveMotors() 
{
    LeftDriveMotor.SetSpeed(LeftSpeed);
    RightDriveMotor.SetSpeed(RightSpeed);
	OldLeftSpeed = LeftSpeed;
	OldRightSpeed = RightSpeed;
}
void DriveTrainManager::RunShifting(int BTNHigh, int BTNLow) {
	if (BTNHigh == 1) {
		DriveShift.Set(HIGH_GEAR);
	} else if (BTNLow == 1) {
		DriveShift.Set(LOW_GEAR);
	}
}
float DriveTrainManager::Sign(float InputSign) {
	if (InputSign > 0) {
		return 1;
	}
	if (InputSign < 0) {
		return -1;
	}
	return 0;
}

void DriveTrainManager::SetDistance(int leftdistance, int rightdistance) {
	LeftDrivePID.Enable();
	LeftDrivePID.SetSetpoint(leftdistance * LEFT_PID_ADJUST);
	RightDrivePID.Enable();
	RightDrivePID.SetSetpoint(rightdistance * RIGHT_PID_ADJUST);
}
bool DriveTrainManager::AtDistance() {
	return LeftDrivePID.OnTarget() && RightDrivePID.OnTarget();
}

void DriveTrainManager::DisablePIDControl() {
	LeftDrivePID.Disable();
	RightDrivePID.Disable();
}

void DriveTrainManager::DashboardInitialize() {
	SmartDashboard::PutData("Right drive PID", &RightDrivePID);
	SmartDashboard::PutData("Left drive PID", &LeftDrivePID);
	//SmartDashboard::PutData("Right encoder", &RightDriveEncoder);
	//SmartDashboard::PutData("Left encoder", &LeftDriveEncoder);
}

void DriveTrainManager::DashboardLoop() {
	//SmartDashboard::PutNumber("Right Cake", RightDrivePID.GetError());
	SmartDashboard::PutNumber("Right Count", RightDriveEncoder.Get());
	//SmartDashboard::PutNumber("Left Cake", LeftDrivePID.GetError());
	SmartDashboard::PutNumber("Left Count", LeftDriveEncoder.Get());
	SmartDashboard::PutBoolean("Shift Gear", DriveShift.Get());
}

void DriveTrainManager::ShiftHigh() {
	DriveShift.Set(HIGH_GEAR);
}
void DriveTrainManager::ShiftLow() {
	DriveShift.Set(LOW_GEAR);
}
void DriveTrainManager::EncoderReset()
{
	LeftDriveEncoder.Reset();
	RightDriveEncoder.Reset();
}
