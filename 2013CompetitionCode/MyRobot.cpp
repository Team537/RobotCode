#include "WPILib.h"
#include "Schematic.h"
#include "CompressorManager.h"
#include <cmath>
#include "dashData/dashData.h"
#include "PID/PIDControl.h"
#include <fstream>
#include <string>

class RobotDemo : public SimpleRobot
{
private:
	float rampspd; // Speed of ramping (bigger = faster ramping)
	float lspd; // Left motor speed
	float rspd; // Right motor speed
	bool emergency;
	float deadband; // Buffer for joystick not ending up exactly at 0 when let go of
	eRobotMode mode; // Mode variable: 0 = tank, 1 = turbo, 2 = straight, 3 = straight turbo
	eGear Gear;
	int driveint; // Drive gear
	char * gearstring; // Gear output string
	float lencvar; // Left encoder variable
	float rencvar; // Right encoder variable
	float encratio; // Encoder ratio, small over big
	float spdmax; // Speed max
	float dist;
	float frisbeedist;
	float spinspeed;
	float maxspinspeed;
	float feedangle;
	float shootwaittime;
	float primewaittime;
	eShooterMode ShootMode;
	eMode curstate;
	eShootPreset curShooterPreset;
	bool hardstopoff;
	float buttonrequirement;
	bool shootyesorno;
	float firecount;
	int state;
	int autoswitchval;
	float autoprimewaittime;
	float newVal;
	
	Joystick primarycontroller, secondarycontroller;
	Victor left, right, spin1, angle;
	DigitalInput autoswitch1, autoswitch2, autoswitch3;
	Solenoid shiftHi, shiftLow, firefrisbee, climb, drive, hardstop, brake, climbdeploy, pneubumpere, pneubumperr;
	DriverStationLCD* lcd;
	AnalogChannel shooterpot;
	Timer timer, shootertime, shottime, uh_oh, autotime, autoshoottime, testingtimer;
	CompressorManager comp;
	DigitalInput /*topswitch,*/ botswitch;
	PosPID anglePID;
	dashData debug;
public:
	RobotDemo(void): // Same order as declaration
		primarycontroller(PRIMARY_CONTROLLER),
		secondarycontroller(SECONDARY_CONTROLLER),
		left(LEFT_MOTOR),
		right(RIGHT_MOTOR),
		spin1(SPIN_MOTOR_1),
		angle(HEIGHT_ADJUSTMENT),
		autoswitch1(AUTO_SWITCH_ONE),
		autoswitch2(AUTO_SWITCH_TWO),
		autoswitch3(AUTO_SWITCH_THREE),
		shiftHi(SHIFT_HIGH),
		shiftLow(SHIFT_LOW),
		firefrisbee(PUSH_FRISBEE),
		climb(CLIMB),
		drive(DRIVE),
		hardstop(HARD_STOP_DEPLOY),
		brake(CLIMBER_BRAKE_RELEASE),
		climbdeploy(CLIMBER_DEPLOY),
		pneubumpere(PNEUMATIC_BUMPER_EXTEND),
		pneubumperr(PNEUMATIC_BUMPER_RETRACT),
		lcd(DriverStationLCD::GetInstance()),
		shooterpot(SHOOTER_POT),
		// topswitch(TOP_SWITCH),
		botswitch(BOT_SWITCH),
		anglePID(0.5f, 0.0f, 0.0f, 2.0f, 1.0f)
	{
		debug.dashLink();
		anglePID.setDebug(&debug);
		rampspd = 0.05f;
		lspd = 0;
		rspd = 0;
		emergency = false;
		deadband = 0.15f;
		mode = eTank;
		// modestring = "Tank";
		gearstring = "High";
		spdmax = 1.0;
		spinspeed = 0;
		Gear = eHigh;
		shootwaittime = 0.4;
		primewaittime = 0.05;
		hardstopoff = true;
		curstate = dDrive;
		buttonrequirement = .8; // sets the value the axis must exceed to register as a button
		firecount = 0;
		state = 0;
		autoprimewaittime = .75;
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
	float ApplyDeadband(float stick)
	{
		float newvalue = stick;
		if (fabs(newvalue) <=  deadband)
			newvalue = 0;
		return newvalue;
	}
	
	/*void Autonomous(void)
	{
		comp.checkCompressor();
		climb.Set(0);
		drive.Set(1);
		ShootMode = eShoot;
		autotime.Stop();
		autotime.Reset();
		autotime.Start();
		angle.Set(0);
		shiftHi.Set(0);
		shiftLow.Set(1);
		firecount = 0;
		firefrisbee.Set(SHOOT);
		timer.Start();
		testingtimer.Start();
		
		while (IsAutonomous())
		{
			comp.checkCompressor();
			Print();
			switch (state)
		
			{
			case DRIVEANDANGLE:
				//AutonomousSwitch();
				spin1.Set(-1); // Turn on Shooter
				angle.Set(1);
				state = DRIVEANDANGLEISDONE;
				break;
			case DRIVEANDANGLEISDONE:
				bool driveDone;
				bool angleDone;
				if (autotime.Get() > 1)
				{
					left.Set(0);
					right.Set(0);
					driveDone = true;
				}
					angle.Set(MakeshiftPID(PITCH_AUTO, shooterpot.GetValue()));
					if (shooterpot.GetValue() == PITCH_AUTO)
					{
						angleDone = true;
					}
				if (driveDone && angleDone && autotime.Get() > 8)
				{
					state = LOADSHOOTER;
				}
				break;
			case LOADSHOOTER:
				angle.Set(0); // Turn off angle
				if (firefrisbee.Get() == SHOOT)
				{
					autoshoottime.Stop();
					autoshoottime.Reset();
					autoshoottime.Start();
					firefrisbee.Set(LOAD);	
				}
				if (autoshoottime.Get() > shootwaittime)
				{
					state = SHOOTSHOOTER;
				}
				break;
			case SHOOTSHOOTER:
				if (firefrisbee.Get() == LOAD)
				{
					firefrisbee.Set(SHOOT);
					firecount++;
					autoshoottime.Stop();
					autoshoottime.Reset();
					autoshoottime.Start();
				}
				if (firecount >= 4)
				{
					autoshoottime.Stop();
					autoshoottime.Reset();
					autoshoottime.Start();
					state = DRIVEBACK;
				}
				else if (autoshoottime.Get() > autoprimewaittime)
				{
					state = LOADSHOOTER;
				}
				break;
			case DRIVEBACK:
				left.Set(-.5);
				right.Set(.5);
				if (autoshoottime.Get() >= 2)
				{
					state = ENDAUTONOMOUS;
				}
				break;
			case ENDAUTONOMOUS:
				spin1.Set(0);
				firefrisbee.Set(SHOOT);
				left.Set(0);
				right.Set(0);
				break;
			}
		}
	}
	/*int AutonomousSwitch() {
		bool autoswitchval1 = autoswitch1.Get();
		bool autoswitchval2 = autoswitch2.Get();
		bool autoswitchval3 = autoswitch3.Get();
		
		
		autoswitchval = 0;
		if(autoswitchval1)
			autoswitchval |= 1;
		if(autoswitchval2)
			autoswitchval |= 2;
		if(autoswitchval3)
			autoswitchval |= 4;
		
		return autoswitchval;
	}
	*/
	void Clamping() {
		lspd = min(lspd, spdmax);
		lspd = max(lspd, -spdmax);
		rspd = min(rspd, spdmax);
		rspd = max(rspd, -spdmax);
	}
	void Climb()
	{
		
	}
	void EmergencyStop() {
		if (uh_oh.Get() > .25 && primarycontroller.GetRawButton(BTN_UH_OH))
		{
			uh_oh.Stop();
			uh_oh.Reset();
			uh_oh.Start();
			if (emergency == false)
				emergency = true; // Uh-oh, bad stuff up da wazoo
			else if (emergency == true)
				emergency = false;
		}
	}
	/*void HardStop()
	{
		if (primarycontroller.GetRawButton(BTN_HARD_STOP_TOGGLE) == true && hardstopoff == true)
		{
			hardstopoff = false;
			// hardstop.Set(hardstop.Get() == 1 ? 0 : 1);
			if (hardstop.Get() == 1)
				hardstop.Set(0);
			else
				hardstop.Set(1);
		}
		else if (not primarycontroller.GetRawButton(BTN_HARD_STOP_TOGGLE))
			hardstopoff = true;
	}*/
	float MakeshiftPID(int destination, int potVal)
	{
		int difference = abs(potVal - destination);
		if (difference > 40)
			newVal = 1;
		else if (difference > 25)
			newVal = .5;
		else if (difference > 10)
			newVal = .44;
		else if (difference > 2)
			newVal = .33;
		else
		{
			newVal = 0;
			curShooterPreset = None;
		}
		if (potVal < destination) // TOO LOW
		{
			newVal *= -1;
		}
		return newVal;
	}
	void ModeSet (void)
	{
		if (primarycontroller.GetRawButton(BTN_TURTLE_MODE) == true)
		{
			mode = eTurtle;
			spdmax = .75;
		}
		else if (primarycontroller.GetRawButton(BTN_TURTLE_MODE) == false)
		{
			mode = eTank;
			spdmax = 1;
		}
	}
	void OperatorControl(void)
	{
		// Initial settings
		shiftLow.Set(0); // Turns off low gear
		shiftHi.Set(1); // Turns on high gear
		climb.Set(0);
		drive.Set(1);
		Gear = eDrive;
		hardstop.Set(0);
		timer.Start();
		ShootMode = eReload;
		spinspeed = 0;
		shootertime.Stop();
		shootertime.Reset();
		pneubumpere.Set(0);
		pneubumperr.Set(1);
		uh_oh.Start();
		brake.Set(0);
		curShooterPreset = None;
		
		// send some initial stuff to the dashboard
		if (curstate == cClimb)
			debug.sendInt(PACKET_CLIMB, 'c');
		else
			debug.sendInt(PACKET_CLIMB, 'd');
		if (shiftHi.Get() == 0)
			debug.sendInt(PACKET_GEAR, 'l');
		else
			debug.sendInt(PACKET_GEAR, 'h');
		
		while (IsOperatorControl())
		{
			EmergencyStop(); // Is bad stuff goin' on?
			if (primarycontroller.GetRawButton(BTN_CLIMB) == true && drive.Get() == 1)
			{
				curstate = cClimb;
				drive.Set(0);
				climb.Set(1);
				debug.sendInt(PACKET_CLIMB, 'c');
				brake.Set(1);
				
				// sets the motor values to be the same when climb mode starts
				rspd = 0;
				lspd = 0;
				right.Set(rspd);
				left.Set(lspd);
			}
			else if (primarycontroller.GetRawButton(BTN_DRIVE) == true && climb.Get() == 1)
			{
				curstate = dDrive;
				climb.Set(0);
				drive.Set(1);
				debug.sendInt(PACKET_CLIMB, 'd');
				brake.Set(0);
			}
			
			if (curstate == cClimb)
			{
				if (shiftHi.Get() == 1)
				{
					shiftHi.Set(0);
					shiftLow.Set(1);
				}
				if (primarycontroller.GetRawButton(4))
					brake.Set(0);
				else if (primarycontroller.GetRawButton(3))
					brake.Set(1);
				
				/*if (primarycontroller.GetRawAxis(LEFT_DRIVE_JOY) > lspd)
					lspd += .001;
				else if (primarycontroller.GetRawAxis(LEFT_DRIVE_JOY) < lspd)
					lspd -= .001;
				if (primarycontroller.GetRawAxis(LEFT_DRIVE_JOY) > rspd)
					rspd += .001;
				else if (primarycontroller.GetRawAxis(LEFT_DRIVE_JOY) < rspd)
					rspd -= .001;*/
				RampSpeed(primarycontroller.GetRawAxis(LEFT_DRIVE_JOY), primarycontroller.GetRawAxis(LEFT_DRIVE_JOY));
				// else if (ApplyDeadband(primarycontroller.GetRawAxis(LEFT_)
				lspd = max(lspd, -.75);
				lspd = min(lspd, .75);
				rspd = max(rspd, -.75);
				rspd = min(rspd, .75);
				if (primarycontroller.GetRawButton(5) == true)
					climbdeploy.Set(0);
				else if (primarycontroller.GetRawButton(6) == true)
					climbdeploy.Set(1);
				else if (primarycontroller.GetRawButton(7) == true)
				{
					pneubumpere.Set(0);
					pneubumperr.Set(1);
				}
				else if (primarycontroller.GetRawButton(8) == true)
				{
					pneubumpere.Set(1);
					pneubumperr.Set(0);
				}
				SetMotors();
			}
			else if (curstate == dDrive)
			{
				ModeSet();
				//HardStop();
				RampSpeed(primarycontroller.GetRawAxis(LEFT_DRIVE_JOY), primarycontroller.GetRawAxis(RIGHT_DRIVE_JOY));
				Clamping();
				SetMotors();
				ShootPreset();
				ShootModeSet();
				ShootAngle();
				Shoot(true);
				if (primarycontroller.GetRawButton(7) == true && shiftHi.Get() == true)
				{
					debug.sendInt(PACKET_GEAR, 'l');
					shiftHi.Set(0);
					shiftLow.Set(1);
				}
				else if (primarycontroller.GetRawButton(8) == true && shiftLow.Get() == true)
				{
					debug.sendInt(PACKET_GEAR, 'h');
					shiftLow.Set(0);
					shiftHi.Set(1);
				}
			}
			Print();
			
			if (emergency == false) // If it's all okay fo' now
			{
				comp.checkCompressor(); // Controls the big daddy compressor				
				Print();
			}
		}
	}
	void Print ()
	{
		// Displays data
		if (timer.Get() > PRINT_TIME) // Checks if 0.1 seconds have passed since the last print
		{
			lcd->Clear(); // Clears message box
			lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Shooter Pot = %5.4f", float(shooterpot.GetValue()));
			lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Makeshift PID value = %5.4f", newVal);
			lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Right = %5.4f", right.Get());
			lcd->Printf(DriverStationLCD::kUser_Line5, 1, "Left = %5.4f", left.Get());
			lcd->Printf(DriverStationLCD::kUser_Line6, 1, "Hardstop = %5.4f", hardstop.Get());
			lcd->UpdateLCD(); // Updates screen with new dqata
			timer.Reset(); // Resets printing timer
			timer.Start();
		}
	}
	void RampSpeed(float LNewSpeed, float RNewSpeed) // Ramps dem new motor values
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
	void SetMotors (void) // Makes those there motors go
	{
		left.SetSpeed(-lspd); // Sets the left motor equal to the final left speed
		right.SetSpeed(rspd); // Sets the right motor equal to the final right speed
	}
	void Shifting (eGear ChangeGear)
	{
		if(ChangeGear == eLow) // Shifting to low gear if L2 is pressed
		{
			shiftHi.Set(0); // Turns off high gear
			shiftLow.Set(1); // Turns on low gear
			Gear = eLow;
			gearstring = "Low"; // Sets the gear output to low
		}
		else if(ChangeGear == eHigh) // Shifting to high gear if R2 is pressed
		{
			shiftLow.Set(0); // Turns off low gear
			shiftHi.Set(1); // Turns on high gear
			Gear = eHigh;
			gearstring = "High"; // Sets the gear output to high
		}
		else if(ChangeGear == eClimb)
		{
			/*if (gearstring == "High")
					driveint = 1;
			if (gearstring == "Low")
					driveint = 0;*/
			drive.Set(0);
			climb.Set(1); // Shifts to climb gear
			Gear = eClimb;
		}
		else if(ChangeGear == eDrive)
		{
			climb.Set(0);
			drive.Set(1); // Shifts to drive gear
			Gear = eDrive;
		}
	}
	void Shoot (bool teleop)
	{
		// code to differentiate teleop from autonomous
		if (teleop == true)
			shootyesorno = secondarycontroller.GetRawButton(BTN_SHOOT);
		else if (teleop == false)
			shootyesorno = true;
		if (AcceptableToFire() == true && firefrisbee.Get() == LOAD)
		{
			firefrisbee.Set(SHOOT); // SHOOT THE DARN FRISBEE
			shottime.Stop();
			shottime.Reset();
			shottime.Start();
		}
		if (shootyesorno == true && firefrisbee.Get() == SHOOT && AcceptableToFire() == true && ShootMode == eShoot)
		{
			firefrisbee.Set(LOAD); // Primes that there frisbee
			shottime.Stop();
			shottime.Reset();
			shottime.Start();
		}
	}
	void ShootPreset()
	{
		if (secondarycontroller.GetRawButton(1))
			curShooterPreset = pt3;
		else if (secondarycontroller.GetRawButton(2))
			curShooterPreset = Reload;
		else if (secondarycontroller.GetRawButton(3))
			curShooterPreset = Start;
		else if (secondarycontroller.GetRawButton(4))
			curShooterPreset = Travel;
		else
			curShooterPreset = None;
	}
	void ShootAngle()
	{
		if (curShooterPreset == None)
		{
			if (ApplyDeadband(secondarycontroller.GetRawAxis(ROUGH_ANGLE_JOY)) > 0 /*&& PITCH_BOTTOM_LIMIT > shooterpot.GetValue()*/)
				angle.Set(-.7); // GOING DOWN
			else if (ApplyDeadband(secondarycontroller.GetRawAxis(ROUGH_ANGLE_JOY)) < 0 /*&& PITCH_TOP_LIMIT < shooterpot.GetValue()*/)
				angle.Set(.7); // GOING UP
			else if (ApplyDeadband(secondarycontroller.GetRawAxis(FINE_ANGLE_JOY)) > 0 /*&& PITCH_BOTTOM_LIMIT > shooterpot.GetValue()*/)
				angle.Set(-.35); // GOING DOWN
			else if (ApplyDeadband(secondarycontroller.GetRawAxis(FINE_ANGLE_JOY)) < 0 /*&& PITCH_TOP_LIMIT < shooterpot.GetValue()*/)
				angle.Set(.35); // GOING UP
			else
				angle.Set(0);
		}
		else
		{
			switch (curShooterPreset)
			{
			case Reload:
				angle.Set(MakeshiftPID(PITCH_LOAD, shooterpot.GetValue()));
				break;
			case pt3:
				angle.Set(MakeshiftPID(PITCH_3PT, shooterpot.GetValue()));
				break;
			case Start:
				angle.Set(MakeshiftPID(PITCH_START, shooterpot.GetValue()));
				break;
			case Travel:
				angle.Set(MakeshiftPID(PITCH_TRAVEL, shooterpot.GetValue()));
				break;
			case Auto:
				break;
			case None:
				break;
			}
		}
		debug.sendInt(PACKET_ANGLE, shooterpot.GetValue());
	}
	void ShootModeSet()
	{
		if (secondarycontroller.GetRawButton(7) == true && ShootMode == eShoot)
		{
			ShootMode = eReload;
			spinspeed = 0;
			shootertime.Stop();
			shootertime.Reset();
			shottime.Stop();
			shottime.Reset();
		}
		else if (secondarycontroller.GetRawButton(8) == true && ShootMode == eReload)
		{
			ShootMode = eShoot;
			spinspeed = 1; //Full power
			shootertime.Start();
			shottime.Start();
		}
		spin1.Set(-spinspeed);
	}
};

START_ROBOT_CLASS(RobotDemo);
