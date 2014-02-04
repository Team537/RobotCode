#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	float lspd, rspd;
	float deadband;
	float rampspd;
	float shooterspeed;
	bool shooterstate;
	float timeprint;
	
	Joystick controller;
	Victor leftdrive, rightdrive, shooter, angle, feeder, collector;
	CompressorManager comp;
	DigitalOutput highshift, lowshift;
	Relay rod;
	AnalogChannel anglepot, lowball, midball, highball;
	DriverStationLCD* lcd;
	Timer PrintTime;

public:
	RobotDemo(void): // Same order as declaration
	
		controller(CONTROLLER),
		leftdrive(LEFT_DRIVE),
		rightdrive(RIGHT_DRIVE),
		shooter(SHOOTER),
		angle(ANGLE),
		feeder(FEEDER),
		collector(COLLECTOR),
		highshift(HIGH_SHIFT),
		lowshift(LOW_SHIFT),
		rod(ROD),
		anglepot(ANGLE_POT),
		lowball(LOW_BALL),
		midball(MID_BALL),
		highball(HIGH_BALL),
		lcd(DriverStationLCD::GetInstance())
		
	{
		deadband = 0.1;
		rampspd = 0.1;
		shooterspeed = 0.35;
		shooterstate = true;
		timeprint = 0.1;
	}
	
	float ApplyDeadband(float stick) // Applies a deadband, setting small joystick values to zero
	{
		float newvalue = stick;
		if (fabs(newvalue) <=  deadband)
			newvalue = 0;
		return newvalue;
	}
	
	void Clamping(void) // Makes sure that speed values are between negative one and one
	{
		lspd = max(lspd, -1);
		lspd = min(lspd, 1);
		rspd = max(rspd, -1);
		rspd = min(rspd, 1);
	}
	
	void Feeder (void) // Runs the collector and feeder
	{
		if (controller.GetRawButton(BTN_COLLECTOR_FEEDER) == true)
		{
			feeder.SetSpeed(1);
			collector.SetSpeed(-1);
		}
		else
		{
			feeder.SetSpeed(0);
			collector.SetSpeed(0);
		}
	}
	void Print ()
			{
				if (PrintTime.Get() > timeprint)
				{
					lcd->Clear();
					lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Shooter State = %b", shooterstate);
					lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Pressure Switch Value = %i", comp.Switch());
					lcd->UpdateLCD();
					PrintTime.Reset();
					PrintTime.Start();
				}
			}
	
	void RampSpeed(float LNewSpeed, float RNewSpeed) // Ramps the speed values up and down
	{
		LNewSpeed = ApplyDeadband(LNewSpeed);
		RNewSpeed = ApplyDeadband(RNewSpeed);
		float LDifference = LNewSpeed-lspd;
		float RDifference = RNewSpeed-rspd;
		if(fabs(LDifference) >= rampspd)
			lspd += rampspd *(LDifference/(fabs(LDifference)));
		if(fabs(RDifference) >= rampspd)
			rspd += rampspd *(RDifference/(fabs(RDifference)));
		if (LNewSpeed == 0)
			lspd = 0;
		if (RNewSpeed == 0)
			rspd = 0;
	}
	
	void Rod(void) // Controls the rod
	{
		if (controller.GetRawButton(BTN_ROD))
		{
			rod.Set(Relay::kForward);
		}
		else
		{
			rod.Set(Relay::kOff);
		}
	}
	
	void SetMotors(void) // Sets the motor speeds
	{
		leftdrive.Set(lspd);
		rightdrive.Set(rspd);
	}
	
	void Shifting(void) // Controls the drive train shifting
	{
		if (controller.GetRawButton(BTN_HIGH_SHIFT) == true)
		{
			lowshift.Set(0);
			highshift.Set(1);
		}
		if (controller.GetRawButton(BTN_LOW_SHIFT) == true)
		{
			highshift.Set(0);
			lowshift.Set(1);
		}
	}
	
	void ShooterAngle(void) // Controls the shroud for shooter angle
	{
		if (controller.GetRawButton(BTN_ANGLE_UP))
		{
			angle.SetSpeed(-0.7);
		}
		else if (controller.GetRawButton(BTN_ANGLE_DOWN))
		{
			angle.SetSpeed(0.7);
		}
		else
		{
			angle.SetSpeed(0);
		}
	}
	
	void ShooterSpeed(void) // Controls the flywheel for shooter speed
		{
			if (shooterstate == true)
			{
				if (controller.GetRawButton(BTN_SHOOT_TOGGLE))
				{
					shooterstate = false;
				}
				/*
				if (controller.GetRawButton(BTN_SHOOT_SPEED_UP))
				{
					shooter.SetSpeed(shooterspeed + 0.05);
				}
				else if (controller.GetRawButton(BTN_SHOOT_SPEED_DOWN))
				{
					shooter.SetSpeed(shooterspeed - 0.05);
				}
			
				else
				{
			*/
					shooter.SetSpeed(shooterspeed);
			//	}
			}
			else if (shooterstate == false)
			{
				if (controller.GetRawButton(BTN_SHOOT_TOGGLE))
				{
					shooterstate = true;
				}
				shooter.SetSpeed(0);
			}
		}
	
	void OperatorControl(void)
	{
		PrintTime.Start();
		while (IsOperatorControl())
		{
			
			comp.checkCompressor();
			//Shifting();
			
			RampSpeed(controller.GetRawAxis(LEFT_DRIVE_AXIS), controller.GetRawAxis(RIGHT_DRIVE_AXIS));
			Clamping();
			SetMotors();
			Feeder();
			Rod();
			ShooterAngle();
			ShooterSpeed();
			Print();
		}
	}
	
};

START_ROBOT_CLASS(RobotDemo);

