#include "WPILib.h"
#include "Schematic.h"
#include "math.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 

DriverStationLCD *lcda = DriverStationLCD::GetInstance();

class RobotDemo : public SimpleRobot
{
	Joystick controller, turn;
	Timer timer;
	Victor frot, brot, flmot, frmot, blmot, brmot;
	AnalogChannel fpot, bpot;
	
	float test;
	float deadband;

public:
	RobotDemo(void):
		controller(CONTROLLER),
		turn(TURN),
		frot(FRONT_ROTATIONAL),
		brot(BACK_ROTATIONAL),
		flmot(FRONT_LEFT_MOTOR),
		frmot(FRONT_RIGHT_MOTOR),
		blmot(BACK_LEFT_MOTOR),
		brmot(BACK_RIGHT_MOTOR),
		fpot(FRONT_POT),
		bpot(BACK_POT)
	{
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		float counter;
		timer.Start();
		float percent;
		deadband = .05;
		float pi = 3.141592653589793238462643;
		float bpotval, fpotval;
		float min = 600, max;
		float fchgval = .5;
		float bchgval = .5;
		
		//float frot, brot;
		
		// frot range is 330-880
		// brot range is 245-745
		
		while (IsOperatorControl())
		{
			/*
			 * if (((contorller.GetAxis(1))^2 + (contorller.GetAxis(2))^2) > 0.9)
			 * 	
			 * 
			 */
			counter = timer.Get();
			
			//frot.Set(controller.GetRawAxis(1));
			//brot.Set(controller.GetRawAxis(1));
			if (controller.GetRawAxis(2) <= 0)
				percent = ((acos(controller.GetRawAxis(1)) / pi));
			else if (controller.GetRawAxis(2) > 0)
				percent = ((acos(-controller.GetRawAxis(1)) / pi));
			fpotval = percent * 550 + 330;
			percent = (fpotval - 330) / 550;
			bpotval = percent * 500 + 245;
			
			if (fpot.GetValue() < fpotval)
				fchgval = -.5;
			
			else if (fpot.GetValue() > fpotval)
				fchgval = .5;
			
			if (fpot.GetValue() < fpotval + 10 && fpot.GetValue() > fpotval - 10)
				fchgval = 0;

			if (bpot.GetValue() > bpotval)
				bchgval = -.5;
						
			else if (bpot.GetValue() < bpotval)
				bchgval = .5;
						
			if (bpot.GetValue() < bpotval + 20 && bpot.GetValue() > bpotval - 20)
				bchgval = 0;
			
			frot.Set(fchgval);
			brot.Set(bchgval);
			
			/*else if (fpotval > fpot.GetValue() + 10)
				chgval *= -1;
						
			else if (fpotval < fpot.GetValue() - 10)
			{
				if (chgval < 0)
					chgval *= -1;
			}*/
			
			if (pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2) > deadband && controller.GetRawButton(1))
			{
				if (controller.GetRawAxis(2) > 0)
				{
					flmot.Set(-sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					frmot.Set(sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					blmot.Set(-sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					brmot.Set(sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
				}
				
				else if (controller.GetRawAxis(2) < 0)
				{
					// turn wheels to cos-1(stickx)
					flmot.Set(sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					frmot.Set(-sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					blmot.Set(sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
					brmot.Set(-sqrt(pow(controller.GetRawAxis(1), 2) + pow(controller.GetRawAxis(2), 2)));
				}
			}
			else
			{
				flmot.Set(0);
				frmot.Set(0);
				blmot.Set(0);
				brmot.Set(0);
			}
			
			/*flmot.Set(-controller.GetRawAxis(4));
			frmot.Set(controller.GetRawAxis(4));
			blmot.Set(-controller.GetRawAxis(4));
			brmot.Set(controller.GetRawAxis(4));*/
			if (float (fpot.GetValue()) < min)
				min = float (fpot.GetValue());
			
			else if (float (fpot.GetValue()) > max)
				max = float (fpot.GetValue());
			
			if (counter >= .1)
			{
				lcda->Clear();
				/*lcda->Printf(DriverStationLCD::kUser_Line1, 1, "Joy 1 value :: %5.4f", controller.GetRawAxis(2));
				lcda->Printf(DriverStationLCD::kUser_Line2, 1, "Goal :: %5.4f", float (fpotval));
				lcda->Printf(DriverStationLCD::kUser_Line3, 1, "Actual :: %d", fpot.GetValue());
				lcda->Printf(DriverStationLCD::kUser_Line4, 1, "Radians :: %5.4f", ((acos(-controller.GetRawAxis(1)) / pi)));
				lcda->Printf(DriverStationLCD::kUser_Line5, 1, "Max :: %5.4f", max);
				lcda->UpdateLCD();*/
				timer.Reset();
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

