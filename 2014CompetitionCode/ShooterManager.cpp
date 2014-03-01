#include "ShooterManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include <cmath>

bool ShooterManager::IsShooterLocked()
{
	return ShooterState == 3;
}

void ShooterManager::ManualShooter(float ShooterAxis, int LatchOn, int LatchOff, int ShiftNeutral, int ShiftGear)
{
	SmartDashboard::PutNumber("Shooter Axis", ShooterAxis);
	if (LatchOn == PRESSED)
	{
		Latch.Set(LATCH_ON);
	}
	if (LatchOff == PRESSED)
	{
		Latch.Set(LATCH_OFF);
	}
	if (fabs (ShooterAxis) >= .1)
	{
	ShooterMotor.Set(.5 * ShooterAxis);
	}
	if  (ShiftNeutral == PRESSED)
	{
		ShooterMotorShifter.Set(0);
	}
	if (ShiftGear == PRESSED)
	{
		ShooterMotorShifter.Set(1);
	}
}

void ShooterManager::StartShooterAuto ()
{
	ShooterState = 0;
	ShooterCharge.Set(true);
}

void ShooterManager::StartShooterTeleop ()
{
	ShooterCharge.Set(true);
	if (ShooterState == 0)
	{
		ShooterState = 3;
	}
}
void ShooterManager::ChargeShooter (int ButtonCharge)
{
	if (ButtonCharge == true)
	{
		ShooterCharge.Set(true);
	}
}

void ShooterManager::DashboardInitialize()
{
	SmartDashboard::PutData("Latch", &Latch);
	SmartDashboard::PutData("Shooter Motor", &ShooterMotor);
	SmartDashboard::PutData("Shooter PID", &ShooterPID);
	SmartDashboard::PutData("Encoder", &ShooterEncoder);	
}

void ShooterManager::DashboardLoop()
{
	SmartDashboard::PutNumber("Cake (Shooter Error)", ShooterPID.GetError());
	SmartDashboard::PutNumber("Shooter State", ShooterState);
	SmartDashboard::PutNumber("LatchedEncoder", LatchedEncoderValue);
}

void ShooterManager::StateMachine(bool SafeToShoot, int TrussButton, int GoalButton)
{		
	if (!SafeToShoot)  
	{
		ShooterPID.Disable();		
		return;
	}
	
    switch (ShooterState) {
	    case 0:
	    	// just in case we get in here without initializing
	    	break;
	    	
	    case 1:	
	    	//  run motor to point LatchOn
	    	ShooterMotorShifter.Set(SHOOT_SHIFT_ON);
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SHOOTER_LATCH_POINT_OFFSET);
	    	ShooterPID.Enable();
	    	if (ShooterPID.OnTarget() || ShooterLimitSwitch.Get() == SHOOT_LIMIT_HIT)
	    	{
	    		if (ShooterTimer.Get() > .5) 
			    {
	    			ShooterTimer.Stop();
	    	   		ShooterTimer.Reset();
	   		   		ShooterTimer.Start();
 			   		ShooterState = 2;
	        	}
	    	}
	    	break;
	    	
	    case 2: 	
	    	//  latch on, motor off
			Latch.Set(LATCH_ON);
	    	ShooterPID.Disable();
			if (ShooterTimer.Get() > .5) 
			{
	    		ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterState = 3;
				  
			}
			break;
			
	    case 3: 	
	    	//  wait for button
			if (1 == TrussButton)
			{
				ShooterState = 4;
			} 
			else if (1 == GoalButton)
			{
				ShooterTimer.Start();
				ShooterState = 8;
			}			
			break;
			
    	case 4:	
    		// backmotor down to LatchOff;
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SHOOTER_LATCH_OFF_POINT_OFFSET);
	    	ShooterPID.Enable();
			if (ShooterPID.OnTarget()) 
			{
	    		ShooterTimer.Start();
				ShooterState = 5;
			}
			break;
			
	    case 5:	
	    	// release latch, move to TrussPoint
	    	ShooterPID.Disable();
	    	
			Latch.Set(LATCH_OFF);
		
			if (ShooterTimer.Get() > .5) 
			{
	    		ShooterTimer.Stop();
		  		ShooterTimer.Reset();
	    		ShooterTimer.Start();
				ShooterState = 6;
	    	}
			break;
			
	    case 6: 	
	    	// waiting
			if (ShooterTimer.Get() > 0.25)
			{
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterState = 7;
			}
			break;
			
	    case 7:	// move to TrussPoint
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SHOOTER_TRUSS_POINT_OFFSET);
	    	ShooterPID.Enable();
			if (ShooterPID.OnTarget())
			{
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterTimer.Start();
				ShooterState = 11;
			}			
			break;
			
	    case 11: //Wait before truss shot
	    	if (ShooterTimer.Get() > 0.5) 
	    	{
	    		ShooterTimer.Stop();
	    		ShooterTimer.Reset();
	    		ShooterState = 9;
	    	}
	    	
	    case 8:	
    		// move to goal point;
	    	ShooterPID.SetSetpoint(LatchedEncoderValue + SHOOTER_GOAL_POINT_OFFSET);
	    	ShooterPID.Enable();
	    	Latch.Set(LATCH_OFF);
			if (ShooterPID.OnTarget() && ShooterTimer.Get() > 0.25) 
			{
				ShooterState = 9;
				ShooterTimer.Stop();
				ShooterTimer.Reset();
			}
			break;
			
	    case 9:	
	    	// motor to neutral
	    	ShooterMotorShifter.Set(SHOOT_SHIFT_OFF);
	    	ShooterPID.Disable();;
			ShooterTimer.Start();
			ShooterState = 10;
			
	    case 10:
	    	// wait & goto 1
			if (ShooterTimer.Get() > 5) 
			{
				ShooterTimer.Stop();
				ShooterTimer.Reset();
				ShooterState = 1;
				ShooterTimer.Start();
			}
			break;
    }

}
