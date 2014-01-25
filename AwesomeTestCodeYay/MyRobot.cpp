#include "WPILib.h"
#include "Schematic.h"
#include <math.h>

class RobotDemo : public SimpleRobot
{
	
private:
Joystick controller;
Victor motor, motor2;
DigitalOutput piston;
float deadband;
float spdmax;
float lspd;
float rspd;
float prevlspd;
float prevrspd;
float rampspd;

	
public:
	RobotDemo(void):
		controller(CONTROLLER),
		motor(MOTOR),
		motor2(MOTOR2),
		piston(PISTON),
		deadband(0.075),
		lspd(0),
		rspd(0)
	{

	}

	void doDeadband()
	{
		if (fabs(controller.GetRawAxis(L_AXIS)) <= deadband)
			lspd = 0;
		else
			lspd = controller.GetRawAxis(L_AXIS);
		if (fabs(controller.GetRawAxis(R_AXIS)) <= deadband)
			rspd = 0;
		else
			rspd = controller.GetRawAxis(R_AXIS);
	}
	
	void clamp() 
	{
		lspd = min(lspd, spdmax);
		lspd = max(lspd, -spdmax);
		rspd = min(rspd, spdmax);
		rspd = max(rspd, -spdmax);
	}
	
	void ramp()
	{
		float ldiff = lspd - prevlspd;
		if (fabs(ldiff) > rampspd)
			lspd += rampspd * (fabs(ldiff)/ldiff);
		float rdiff = rspd - prevrspd;
		if (fabs(rdiff) > rampspd)
			rspd += rampspd * (fabs(rdiff)/rdiff);
		
	}
	void SetVictors(void)
	{
		motor.SetSpeed(lspd);
		motor2.SetSpeed(-rspd);
		prevlspd = lspd;
		prevrspd = rspd;
	}
	void Autonomous(void)
	{

	}

	void OperatorControl(void)
	{
		while (true)
		{
			doDeadband();
			ramp();
			clamp();
			SetVictors();
		}
	}
	

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

