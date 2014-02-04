#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "Schematic.h"
#include "WPILib.h"

class DriveTrain
{
	Victor MotorL, MotorR;
	Solenoid Shift;
	Encoder LEnc, REnc;
	DriverStationLCD* enclcd;
public:
	DriveTrain(void):
		MotorL(VICTL),
		MotorR(VICTR),
		Shift(SHIFT),
		LEnc(LEFT_ENCODER,true,CounterBase::k4X),
		REnc(RIGHT_ENCODER,true,CounterBase::k4X),
		enclcd(DriverStationLCD::GetInstance())
		{
		deadband = 0.1;
		rampspd = 0.1;
		spdmax = 1;
		}
	void Drive (float Left, float Right, int High, int Low);
	void StartDrive ();
	float LSpeed();
	float RSpeed();
	
private:
	float deadband;
	float rampspd;
	float lspd, rspd;
	float LDifference, RDifference;
	float prevl, prevr;
	float lenc, renc;
	float spdmax;
	
	float ApplyDeadband (float stick);
	void Clamping ();
	void Encoders ();
	void EncPrint ();
	void RampSpeed (float LNewSpeed, float RNewSpeed);
	void SetMotors ();
	void Shifting (int BTNHigh, int BTNLow);
	float Sign (float inputsign);
};

#endif
