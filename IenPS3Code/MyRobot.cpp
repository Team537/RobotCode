#include "WPILib.h"
#include "Schematic.h"
// #include "math.h"
// #include "CompressorManager.h"

/* ADAM READ
i've copied in the shooter code and i've tried to
get it working.  it should take a little tweaking,
be close to functioning.  the compressor isn't
in the code yet, so that's to be added.

THE SCHEMATIC FILE HAS BEEN CORRUPTED, AND IT NEED THE
NEW PORT VALUES.  PUT THOSE INTO THE CURRENT SCHEMATIC
FILE BEFORE YOU RUN, OR IT HAS NO CHANCE OF WORKING.
*/

class RobotDemo : public SimpleRobot
{
	float shootwaittime, primewaittime;
	
	// shooter stuff
	Timer shottime, shootertime;
	Solenoid firefrisbee;
	eShooterMode ShootMode;
	float spinspeed;
	Compressor comp;
	DriverStationLCD *lcda;
	
	Joystick controller;
	Timer timer;
	Victor frot, brot, flmot, frmot, blmot, brmot, spin1;
	AnalogChannel fpot, bpot;
	
	// CompressorManager comp;
	
	float test;
	float deadband;
	float contaxis4;
	bool shootyesorno;
	

public:
	RobotDemo(void):
		firefrisbee(FIRE_FRISBEE),
		comp(COMPRESSOR),
		controller(CONTROLLER),
		lcda(DriverStationLCD::GetInstance()),
		frot(FRONT_ROTATIONAL),
		brot(BACK_ROTATIONAL),
		flmot(FRONT_LEFT_MOTOR),
		frmot(FRONT_RIGHT_MOTOR),
		blmot(BACK_LEFT_MOTOR),
		brmot(BACK_RIGHT_MOTOR),
		spin1(SHOOT_MOTOR),
		fpot(FRONT_POT),
		bpot(BACK_POT)
	{
		shootwaittime = .4;
		primewaittime = .05;
		spinspeed = 0;
	}

	void Autonomous(void)
	{
		
	}
	
	bool AcceptableToFire()
	{
		if (shottime.Get() > shootwaittime)
			return true;
		else
			return false;
	}
	
	bool AcceptableToPrime()
	{
		if (shootertime.Get() > 5 && shottime.Get() > primewaittime)
			return true;
		else
			return false;
	}
	
	void Shoot (bool teleop)
	{
		// code to differentiate teleop from autonomous
		/*if (teleop == true)
			shootyesorno = controller.GetRawButton(BTN_SHOOT);
		else if (teleop == false)
			shootyesorno = true;*/
		if (AcceptableToFire() == true && firefrisbee.Get() == true)
		{
			firefrisbee.Set(false); // SHOOT THE DARN FRISBEE
			shottime.Stop();
			shottime.Reset();
			shottime.Start();
		}
		if (shootyesorno == true && firefrisbee.Get() == false && AcceptableToFire() == true && ShootMode == eShoot)
		{
			firefrisbee.Set(true); // Primes that there frisbee
			shottime.Stop();
			shottime.Reset();
			shottime.Start();
		}
	}
	
	void ShootModeSet()
	{
		if (controller.GetRawButton(BTN_MODE_RELOAD) == true && ShootMode == eShoot)
		{
			ShootMode = eReload;
			spinspeed = 0;
			shootertime.Stop();
			shootertime.Reset();
			shottime.Stop();
			shottime.Reset();
		}
		else if (controller.GetRawButton(BTN_MODE_SHOOT) == true && ShootMode == eReload)
		{
			ShootMode = eShoot;
			spinspeed = 1; // CHANGE BACK TO 1.  40% IS BUTTERZONE FOR CHILDREN
			shootertime.Start();
			shottime.Start();
		}
		spin1.Set(-spinspeed);
	}

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
		
		while (IsOperatorControl())
		{
			// comp.checkCompressor();
			ShootModeSet();
			Shoot(true);
			fpotval = fpot.GetValue();
			bpotval = bpot.GetValue();
				counter = timer.Get();
				if (controller.GetRawButton(3))
				{
					frot.SetSpeed(0);
					brot.SetSpeed(0);
					flmot.SetSpeed(0);
					frmot.SetSpeed(0);
					blmot.SetSpeed(0);
					brmot.SetSpeed(0);
				}
				else if (controller.GetRawButton(BTN_L1) == false)
				{
					if (controller.GetRawButton(7))
					{
						if (fpotval < 860)
							frot.SetSpeed(-0.5);
						if (bpotval <  725)
							brot.SetSpeed(-0.5);
						if (fpotval > 860 and bpotval > 725)
						{
							frot.Set(0);
							brot.Set(0);
							flmot.Set(0.5);
							frmot.Set(0.5);
							blmot.Set(0.5);
							brmot.Set(0.5);
						}
					}
					else if (controller.GetRawButton(8))
					{
						if (fpotval < 860)
							frot.SetSpeed(-0.5);
						if (bpotval <  725)
							brot.SetSpeed(-0.5);
						if (fpotval > 860 and bpotval > 725)
						{
							frot.Set(0);
							brot.Set(0);
							flmot.Set(-0.5);
							frmot.Set(-0.5);
							blmot.Set(-0.5);
							brmot.Set(-0.5);
						}
					}
					else
					{
						if (controller.GetRawAxis(4) <= 0)
							percent = ((acos(controller.GetRawAxis(3)) / pi));
						else if (controller.GetRawAxis(4) > 0)
							percent = ((acos(-controller.GetRawAxis(3)) / pi));
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
						
						if (pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2) > deadband && controller.GetRawButton(BTN_R1))
						{
							if (controller.GetRawAxis(4) > 0)
							{
								flmot.Set(0.5 * -sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								frmot.Set(0.5 * sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								blmot.Set(0.5 * -sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								brmot.Set(0.5 * sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
							}
							
							else if (controller.GetRawAxis(4) < 0)
							{
								flmot.Set(0.5 * sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								frmot.Set(0.5 * -sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								blmot.Set(0.5 * sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
								brmot.Set(0.5 * -sqrt(pow(controller.GetRawAxis(3), 2) + pow(controller.GetRawAxis(4), 2)));
							}
						}
						else
						{
							flmot.Set(0);
							frmot.Set(0);
							blmot.Set(0);
							brmot.Set(0);
						}
						contaxis4 = 0;
					}
				}
				else
				{
					if (contaxis4 == 0)
						contaxis4 = controller.GetRawAxis(4);
					if (controller.GetRawButton(BTN_R1))
					{
						if (contaxis4 > 0)
						{
							flmot.Set(-0.25);
							frmot.Set(0.25);
							blmot.Set(-0.25);
							brmot.Set(0.25);
						}
						else if (contaxis4 < 0)
						{
							flmot.Set(0.25);
							frmot.Set(-0.25);
							blmot.Set(0.25);
							brmot.Set(-0.25);
						}
					}	
				}
				if (float (fpot.GetValue()) < min)
					min = float (fpot.GetValue());
				
				else if (float (fpot.GetValue()) > max)
					max = float (fpot.GetValue());
				
				if (counter >= .1)
				{
					lcda->Clear();
					lcda->Printf(DriverStationLCD::kUser_Line3, 1, "FPot :: %d", fpotval);
					lcda->Printf(DriverStationLCD::kUser_Line4, 1, "BPot :: %d", bpotval);
					lcda->UpdateLCD();
					timer.Reset();
				
				}
		}
	}
};
START_ROBOT_CLASS(RobotDemo);
