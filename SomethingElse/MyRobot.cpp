#include "WPILib.h"
#include "schematic.h"
#include <math.h>

class RobotDemo : public SimpleRobot
{

private: //declaring variables
	DigitalOutput high, low, shootPist;
	Victor lmotor, rmotor, angleMotor, shootMotor;
	Joystick controller;
	DriverStationLCD *  lcd;
	Timer timer;
	
	float lspd, rspd, prevl, prevr, rampSpd, spdMax, shootSpd, maxShoot, shootAng, AngMax, deadband, printTime;
	
public:
	RobotDemo(void): //gives values to objects/variables
	high(SHIFTERH),
	low(SHIFTERL),
	shootPist(SHOOTERPISTON),
	lmotor(LEFTMOTOR),
	rmotor(RIGHTMOTOR),
	angleMotor(ANGLEMOTOR), 
	shootMotor(SHOOTERMOTOR),
	controller(CONTROLLER),
	lcd(DriverStationLCD::GetInstance()),
	rampSpd(RAMPSPD),
	spdMax(SPDMAX),
	maxShoot(MAXSHOOT),
	deadband(DEADBAND),
	printTime(PRINTTIME)
	{}

	
	
	void applyDeadband() //gets input, makes sure being very slightly off 0 does nothing
	{
		if (fabs(controller.GetRawAxis(L_AXIS)) <= deadband) //checks if distance from 0 is less than deadband
			lspd = 0; //if so, set input to 0
		else
			lspd = controller.GetRawAxis(L_AXIS); //otherwise, use raw value. OK because will be ramped later
		if (fabs(controller.GetRawAxis(R_AXIS)) <= deadband)
			rspd = 0;
		else
			rspd = controller.GetRawAxis(R_AXIS);		
	}
	
	void ramp() //makes sure motor does not (de)accelerate to quickly
	{
		float ldif = (lspd - prevl); //gets difference between old and present spd (accel)
		float rdif = (rspd - prevr);
		if (ldif > rampSpd) //checks if accel is too high
			lspd += rampSpd * (ldif/fabs(ldif)); //if so, limit it
		if (rdif > rampSpd)
			rspd += rampSpd * (rdif/fabs(rdif));
	}

	void clamp(void) //limits max spd to "spdMax"
	{
		lspd = min(lspd, spdMax); //sees which val is lower, uses it (speed <= spdMax)
		lspd = max(lspd, -spdMax); //same as above, but for negative
		rspd = min(rspd, spdMax);
		rspd = max(lspd, -spdMax);
	}
			
	void shift()
	{
		if (controller.GetRawButton(1))
		{
			high.Set(0);
			low.Set(1);
		}		
		else if (controller.GetRawButton(4))
		{
			high.Set(1);
			low.Set(0);
		}
	}
	
	void setDrive(void)
	{
		lmotor.SetSpeed(lspd);
		rmotor.SetSpeed(-rspd);
		prevl = lspd;
		prevr = rspd;
	}

	void drive() //all dem functions that drive n' stuff
	{			 //"me ken inglesh" -Sir Rev. Dr. Brandon Pupp Great Grand Jr., esq., MEP, Conspiracy theorist, fin, PS i be rock 
		applyDeadband();
		ramp();
		clamp();
		shift();
		setDrive();
	}
	
	
	
	void readyShooter ()
	{
		if (controller.GetRawButton(8))
			if (shootSpd < maxShoot)
				shootSpd +=  0.05 * maxShoot;
			else
				shootPist.Set(1);
		else
			if (shootSpd > 0)
				shootSpd -= 0.05 * maxShoot;
	}
	
	void adjustAngle ()
	{
		if (controller.GetRawButton(6))
			if (shootAng < maxShoot)
				shootAng += 0.05 * maxShoot;
			else
				shootAng = maxShoot;
		else if (controller.GetRawButton(5))
			if (shootAng > -maxShoot)
				shootAng -= 0.05 * maxShoot;
			else
				shootAng = -maxShoot;
		else
			if (shootAng > 0)
				shootAng -= 0.05 * maxShoot;
			else if (shootAng < 0)
				shootAng += 0.05 * maxShoot;
	}

	void setShooter()
	{
		//set shooter vals here
	}
	
	void shoot()
	{
		readyShooter();
		adjustAngle();
		setShooter();
	}


	void print()
	{
		if (timer.Get() > printTime)
		{
			lcd->Clear();
			lcd->Printf(DriverStationLCD::kUser_Line1,1, "lmotor = %5.4f", lmotor.Get());
			lcd->Printf(DriverStationLCD::kUser_Line2,1, "rmotor = %5.4f", rmotor.Get());
			lcd->Printf(DriverStationLCD::kUser_Line3,1, "shootMotor = %5.4f", shootMotor.Get());
			lcd->Printf(DriverStationLCD::kUser_Line4,1, "angleMotor = %5.4f", angleMotor.Get());
			if (high.IsPulsing())
				lcd->Printf(DriverStationLCD::kUser_Line5,1, "gear = high");
			else if (low.IsPulsing())
				lcd->Printf(DriverStationLCD::kUser_Line5,1, "gear = low");
			lcd->UpdateLCD();
			timer.Reset();
			timer.Start();
		}
	}
	
	
	
	void Autonomous(void){}

	void OperatorControl(void)
	{
		while ("Pupp" != "Stupid")
		{
			drive();
			shoot();
			print();
		}
	}
	


	void Test(){}
};

START_ROBOT_CLASS(RobotDemo);

