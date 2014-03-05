#ifndef SHOOTER_H
#define SHOOTER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "CollectorManager.h"
#include "WPILib.h"

class ShooterManager
{
	Solenoid ShooterMotorShifter, Latch, ShooterCharge;
	Victor ShooterMotor;
	DigitalInput ShooterLimitSwitch;
	Encoder ShooterEncoder;
	Timer ShooterTimer;
	PIDController ShooterPID;
public:
	ShooterManager(void):
		ShooterMotorShifter (SHOOTER_MOTOR_SHIFTER),
		Latch (LATCH),
		ShooterCharge (SHOOTER_CHARGE),
		ShooterMotor (SHOOTER_MOTOR),
		ShooterLimitSwitch (SHOOTER_LIMIT_SWITCH),
		ShooterEncoder(SHOOTER_ENCODER,true,CounterBase::k4X),
		ShooterPID(-0.03, 0, -0.03, &ShooterEncoder, &ShooterMotor)
		{
			ShooterState = 0;
			ShooterEncoder.SetPIDSourceParameter(PIDSource::kDistance);
			ShooterEncoder.Start();
			ShooterEncoder.SetMinRate(0.5);
			
			LatchedEncoderValue = ShooterEncoder.Get();
			
			ShooterPID.SetAbsoluteTolerance(10);
			ShooterPID.SetOutputRange(-1, .25);
		}

	bool IsShooterLocked();
	void StartShooterAuto();
	void StartShooterTeleop();
	void StateMachine(bool SafeToShoot, int TrussButton, int GoalButton, CollectorManager *Collector);
	void ManualShooter(float ShooterAxis, int LatchOn, int LatchOff, int ShiftNeutral, int ShiftGear, int PIDOff, bool SafeToShoot);
	void DashboardInitialize();
	void DashboardLoop();
	void ChargeShooter (int ButtonCharge);
	void DisablePIDControl();
	void ResetShooterState();
	
	
private:
	int ShooterState;
	int LatchedEncoderValue;
};

#endif
