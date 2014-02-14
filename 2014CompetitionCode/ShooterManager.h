#ifndef SHOOTER_H
#define SHOOTER_H
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

class ShooterManager
{
	Solenoid ShooterMotorShifter, Flappers;
	Victor ShooterMotor;
	DigitalInput ShooterLimitSwitch;
	Encoder ShooterEncoder;
	Timer ShooterTimer;
public:
	ShooterManager(void):
		ShooterMotorShifter (SHOOTER_MOTOR_SHIFTER),
		Flappers (FLAPPERS),
		ShooterMotor (SHOOTER_MOTOR),
		ShooterLimitSwitch (SHOOTER_LIMIT_SWITCH),
		ShooterEncoder(SHOOTER_ENCODER,true,CounterBase::k4X)
		{
			ShooterState = 1;
		}

	bool Safe;
	/*void StartShooterAuto();
	void StartShooterTeleop();
	*/void RunShooter(int PrimeButton, int GoalButton, int TrussButton);
	void PracticeShooter (float ShooterAxis, int GoalButton);
	
private:
	int ShooterState;
	void RunPrime (int PrimeBtn);
	void RunGoalShot (int GoalBtn);
	void RunTrussShot (int TrussBtn);
	
};

#endif
