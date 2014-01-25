#include "WPILib.h"
#include "Ramping.h"

#define RAMP_SPD .1

class RobotDemo : public SimpleRobot
{
	Joystick leftStick, rightStick, secondary; // only joystick
	Victor leftDrive, rightDrive, shootSpeed, collFeed;
	Relay collCollect;
	Compressor comp;
	Timer time, test;
	Solenoid shiftHi, shiftLow,bridgePush;
	Victor shootPitch;
	PWM brassRod;
	
public:
	RobotDemo(void):
	leftStick(1),
	rightStick(2),
	secondary(3),
	leftDrive(1,2),
	rightDrive(1,1),
	shootSpeed(1,5),
	collFeed(1,6),
	collCollect(1,1),
	comp(1,7,1,4),
	time(),
	test(),
	shiftHi(1,1),
	shiftLow(1,3),
	bridgePush(1,8),
	shootPitch(1,4),
	brassRod(1,9)
	{
		GetWatchdog().SetEnabled(true);
		GetWatchdog().SetExpiration(5.0);
		//time.Start();
		test.Start();
	}


	void Autonomous(void)
	{
		GetWatchdog().Feed();
		shootSpeed.Set(CubicRamp(shootSpeed.Get(),1,RAMP_SPD));	
	}

	void OperatorControl(void)
	{
		comp.Start();
		
		GetWatchdog().SetEnabled(true);
		GetWatchdog().SetExpiration(10.0);
				
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			shootSpeed.Set(CubicRamp(shootSpeed.Get(),1,RAMP_SPD));
			
			//collCollect.Set(Relay::kForward);
			
			//if(comp.GetPressureSwitchValue() == 1 && time.Get() > .25)
			//{
			//	
			//	comp.Stop();
			//	time.Reset();
			//}
			//else
			//	comp.Start();

			leftDrive.Set(leftStick.GetY());//CubicRamp(leftDrive.Get(),leftStick.GetY(),RAMP_SPD));
			rightDrive.Set(rightStick.GetY());//CubicRamp(rightDrive.Get(),rightStick.GetY(),RAMP_SPD));
			bridgePush.Set(rightStick.GetTrigger());
			
			if (leftStick.GetTrigger())
				collCollect.Set(Relay::kForward);
			else
				collCollect.Set(Relay::kOff);
			
			if(rightStick.GetRawButton(3))
			{
				shiftHi.Set(1);
				shiftLow.Set(0);
			}
			if(rightStick.GetRawButton(2))
			{
				shiftHi.Set(0);
				shiftLow.Set(1);
			}
			
			if(secondary.GetRawButton(3))
				{
				brassRod.SetRaw(1);
				collFeed.Set(1);
				}
			else 
				{
				brassRod.SetRaw(0);
				collFeed.Set(0);
				}
			
			shootPitch.Set(secondary.GetRawAxis(4));
			
			if(test.Get() > .25)
			{
				printf("SP: %f | LS: %f | RS: %f | PS: %d\n",
						shootSpeed.Get(), leftDrive.Get(),
						rightDrive.Get(), comp.GetPressureSwitchValue());
				test.Reset();
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
