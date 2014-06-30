#include "DriveTrainManager.h"
#include "Schematic.h"
#include <cmath>

void DriveTrainManager::StartDriveTrain() // Runs at the start of teleop
{
	LeftDriveEncoder.SetDistancePerPulse(0.45);
	RightDriveEncoder.SetDistancePerPulse(0.45);
	LeftDriveEncoder.Start();
	RightDriveEncoder.Start();
	EncoderTimer.Start();
	DriveShift.Set(1);
	LeftEncTotal = 0;
	RightEncTotal = 0;
}
void DriveTrainManager::RunDriveTrain(float JoystickLeft, float JoystickRight, int ButtonHighShift, int ButtonLowShift) // Loops during teleop
{
	RunShifting(ButtonHighShift, ButtonLowShift);
	RunRampSpeed(JoystickLeft, JoystickRight);
	RunEncoders();
	RunClamping();
	RunDriveMotors();
}
float DriveTrainManager::ApplyDeadband (float JoystickValue) // Applies a deadband to the joystick values so the robot always stops when the joysticks aren't being pressed
	{
		if (fabs(JoystickValue) <= 0.1)
		{
			JoystickValue = 0;
		}
		return JoystickValue;
	}
void DriveTrainManager::RunClamping (void) // Makes sure values being sent to Victors are between -1 and 1
	{
		LeftSpeed = min(LeftSpeed, 1);
		LeftSpeed = max(LeftSpeed, -1);
		RightSpeed = min(RightSpeed, 1);
		RightSpeed = max(RightSpeed, -1);
	}
void DriveTrainManager::RunEncoders () // Corrects turning of drive train with encoder ratios (we didn't end up using this in competition)
	{
		if (EncoderTimer.Get() > 0.1)
		{
			LeftRatio = LeftDriveEncoder.Get() / OldLeftSpeed;
			RightRatio = RightDriveEncoder.Get() / OldRightSpeed;
			if (LeftRatio > RightRatio)
			{
				LeftSpeed *= (RightRatio / LeftRatio);
				
			}
			else if (RightRatio > LeftRatio)
			{
				RightSpeed *= (LeftRatio / RightRatio);
			}
			LeftEncTotal += LeftDriveEncoder.Get();
			RightEncTotal += RightDriveEncoder.Get();
			LeftDriveEncoder.Reset();
			RightDriveEncoder.Reset();
			EncoderTimer.Reset();
		}
	}
void DriveTrainManager::RunRampSpeed (float LeftNewSpeed, float RightNewSpeed) // Ramps speeds sent to Victors so changing directions is smoother
	{
		LeftNewSpeed = LEFT_DRIVE_DIRECTION * ApplyDeadband(LeftNewSpeed);
		RightNewSpeed = RIGHT_DRIVE_DIRECTION * ApplyDeadband(RightNewSpeed);
		LeftDifference = LeftNewSpeed - LeftSpeed;
		RightDifference = RightNewSpeed - RightSpeed;
		if (fabs(LeftDifference) >= 0.1)
		{
			LeftSpeed += 0.1 * Sign(LeftDifference);
		}
		if (fabs(RightDifference) >= 0.1)
		{
			RightSpeed += 0.1 * Sign(RightDifference);
		}
		if (LeftNewSpeed == 0)
		{
			LeftSpeed = 0;
		}
		if (RightNewSpeed == 0)
		{
			RightSpeed = 0;
		}
	}
void DriveTrainManager::RunDriveMotors (void) // Sets the Victors to the speeds they should be set to
	{
		LeftDriveMotor.SetSpeed(LeftSpeed);
		RightDriveMotor.SetSpeed(RightSpeed);
		OldLeftSpeed = LeftSpeed;
		OldRightSpeed = RightSpeed;
	}
void DriveTrainManager::RunShifting (int BTNHigh, int BTNLow) // Controls the shifting of the drive train
	{
		if (BTNHigh == 1)
		{
			DriveShift.Set(1);
		}
		else if (BTNLow == 1)
		{
			DriveShift.Set(0);
		}
	}
float DriveTrainManager::Sign (float InputSign) // Returns the sign of the number entered as either -1, 0, or 1
	{
		if (InputSign > 0)
		{
			return 1;
		}
		if (InputSign < 0)
		{
			return -1;
		}
		return 0;
	}
