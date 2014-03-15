#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include <cmath>

bool ShooterManager::IsShooterLocked()
{
	return Latch.Get() == LATCH_ON;
	
}
void ShooterManager::DisablePIDControl()
{
	ShooterPID.Disable();
}

void ShooterManager::ManualShooter(float ShooterAxis, int LatchOn, int LatchOff, int ShiftNeutral, int ShiftGear, int PIDOff, bool SafeToShoot)
{
	SmartDashboard::PutNumber("Shooter Axis", ShooterAxis);
	if (!SafeToShoot)  
	{		
		ShooterPID.Disable();
		return;
	}
	if (PIDOff == PRESSED)
	{
		ShooterPID.Disable();
	}
	if (LatchOn == PRESSED)
	{
		Latch.Set(LATCH_ON);
		ShooterEncoder.Reset();
	}
	if (LatchOff == PRESSED)
	{
		Latch.Set(LATCH_OFF);
	}
	if (fabs (ShooterAxis) >= .15)
	{
		ShooterMotor.Set(SHOOTER_MANUAL_WINCH_SPEED * ShooterAxis);
	}
	if  (ShiftNeutral == PRESSED)
	{
		ShooterMotorShifter.Set(SHOOT_SHIFT_NEUTRAL);
	}
	if (ShiftGear == PRESSED)
	{
		ShooterMotorShifter.Set(SHOOT_SHIFT_GEAR);
	}
}

void ShooterManager::StartShooterAuto ()
{
	ShooterState = INITIALAIZE_SHOOTER;
	ShooterCharge.Set(true);
}

void ShooterManager::StartShooterTeleop ()
{
	ShooterCharge.Set(true);
	if (ShooterState == 0)
	{
		ShooterState = INITIALAIZE_SHOOTER;
	}
}
void ShooterManager::ChargeShooter ()
{
	ShooterCharge.Set(true);
}

void ShooterManager::DashboardInitialize()
{
	//SmartDashboard::PutData("Latch", &Latch);
	SmartDashboard::PutData("Shooter Motor", &ShooterMotor);
	SmartDashboard::PutData("Shooter PID", &ShooterPID);
	//SmartDashboard::PutData("Shooter Encoder", &ShooterEncoder);	
}

void ShooterManager::DashboardLoop()
{
	//SmartDashboard::PutNumber("Cake (Shooter Error)", ShooterPID.GetError());
	SmartDashboard::PutNumber("Shooter State", ShooterState);
	//SmartDashboard::PutNumber("LatchedEncoder", LatchedEncoderValue);
	SmartDashboard::PutNumber("Shooter Position", ShooterEncoder.Get());
	SmartDashboard::PutNumber("Shooter Limit Switch", ShooterLimitSwitch.Get());
}

void ShooterManager::ResetShooterState()
{
	ShooterState = INITIALAIZE_SHOOTER;
}

void ShooterManager::StateMachine(bool SafeToShoot, int ResetButton, int GoalButton, CollectorManager *Collector)
{	
	SmartDashboard::PutNumber("Goal Button", GoalButton);	
	SmartDashboard::PutNumber("Safe to Shoot", SafeToShoot);
	
	if (ResetButton == 1 && Collector->SafeToShoot())
	{
		ShooterState = WINCH_TO_LIMIT_SWITCH;
	}
		
    switch (ShooterState) {
	    case INITIALAIZE_SHOOTER:
	    	// just in case we get in here without initializing
	    	ShooterState = WAIT_FOR_COMMAND;
	    	break;
	    	
	    case WAIT_FOR_COMMAND: 
	    	ShooterPID.Disable();
			if (1 == GoalButton)
			{
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterTimer.Start();
				ShooterState = MOVE_TO_GOAL_POINT;
			}			
			
			break;
			
	    case MOVE_TO_GOAL_POINT:	
    		// move to goal point;
	    	Collector->RunCollector(1, 0, 0, 0, 0, 0);
			ShooterMotorShifter.Set(SHOOT_SHIFT_GEAR);
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SHOOTER_GOAL_POINT_OFFSET);
	    	ShooterPID.Enable();	    	
			if (ShooterPID.OnTarget()) 
			{
				ShooterState = SHIFT_MOTOR_TO_NEUTRAL;
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterTimer.Start();
			}
			break;
			
	    case SHIFT_MOTOR_TO_NEUTRAL:	
	    	// motor to neutral
	    	ShooterMotorShifter.Set(SHOOT_SHIFT_NEUTRAL);
	    	ShooterMotor.Set(WINCH_UP * .1);
	    	ShooterPID.Disable();
			
			if (ShooterTimer.Get() > 0.5) {
				ShooterState = SHOOT_THE_BALL;
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterTimer.Start();
			}
			break;
			
			
	    case SHOOT_THE_BALL:
	    	// fire!!
	    	if (!SafeToShoot)
	    	{
	    		break;
	    	}
	    	
	    	Latch.Set(LATCH_OFF);
	    	ShooterMotor.Set(0);
			if (ShooterTimer.Get() > .2) {
				ShooterState = WINCH_MOTOR_TO_GEAR;	
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterTimer.Start();			
			}
			break;
			
	    case WINCH_MOTOR_TO_GEAR:
	    	// re-engage winch and wait
	    	ShooterMotorShifter.Set(SHOOT_SHIFT_NEUTRAL);
			if (ShooterTimer.Get() > 0.25) 
			{
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterState = RETRACT_ARM;
				ShooterTimer.Start();
			}
			break;
			
	    case RETRACT_ARM:	
	    	//  run motor to point LatchOn
	    	if (!SafeToShoot)
	    	{
	    		ShooterPID.Disable();
	    		break;
	    	}
	    	ShooterMotorShifter.Set(SHOOT_SHIFT_GEAR);
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SWITCH_TO_LIMIT_SWITCH_VALUE);
	    	ShooterPID.Enable();
	    	if (ShooterPID.OnTarget()) //|| ShooterLimitSwitch.Get() == SHOOT_LIMIT_HIT)
	    	{
	    		if (ShooterTimer.Get() > .5) 
			    {
	    			ShooterTimer.Stop();
	    	   		ShooterTimer.Reset();
	   		   		ShooterTimer.Start();
 			   		ShooterState = WINCH_TO_LIMIT_SWITCH;
	        	}
	    	}
	    	break;
	    
	    case WINCH_TO_LIMIT_SWITCH:
			Latch.Set(LATCH_OFF);
	    	ShooterMotor.Set(WINCH_DOWN * .5);
	    	if (ShooterLimitSwitch.Get() == 0)
	    	{
	    		ShooterTimer.Stop();
	    		ShooterTimer.Reset();
	    		ShooterTimer.Start();
	    		ShooterState = RELATCH_ARM;
	    	}
	    	break;
	    	
	    case RELATCH_ARM: 	
	    	//  latch on, motor off
			Latch.Set(LATCH_ON);
	    	ShooterPID.Disable();
			if (ShooterTimer.Get() > .5) 
			{
	    		ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterState = WAIT_FOR_COMMAND;
				  
			}
			break;
    }

}
