#include "WPILib.h"
#include "Schematic.h"

DriverStationLCD *lcda = DriverStationLCD::GetInstance();

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick wheel;
	Victor fldrive, frdrive, bldrive, brdrive, frot;
	AnalogChannel fpot;
	float fturn, fl, fr, bl, br, frr;

public:
	RobotDemo(void):
		wheel(1),
		fldrive(FRONT_LEFT_MOTOR),
		frdrive(FRONT_RIGHT_MOTOR),
		bldrive(BACK_LEFT_MOTOR),
		brdrive(BACK_RIGHT_MOTOR),
		frot(FRONT_ROTATIONAL),
		fpot(FRONT_POT)
	{
		fturn = 0;
		fl = 0;
		fr = 0;
		bl = 0;
		br = 0;
		frr = 0;
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
	
	float PID(int dest, int current)
	{
		int difference = abs(dest - current);
		if (difference > 20)
			frr = .3;
		else if (difference > 10)
			frr = .2;
		else if (difference > 3)
			frr = .1;
		else
			frr = 0;
		
		if (dest > current)
			frr *= -1;
		return frr;
	}
	void OperatorControl(void)
	{
		Timer printtime;
		printtime.Start();
		while (IsOperatorControl())
		{
			frr = wheel.GetRawAxis(TURN);
			// frdrive.Set(wheel.GetRawAxis(TURN));
			if (printtime.Get() > .1)
			{
				lcda->Clear();
				lcda->Printf(DriverStationLCD::kUser_Line1, 1, "Steering :: %5.4f", wheel.GetRawAxis(1));
				lcda->Printf(DriverStationLCD::kUser_Line2, 1, "F-Pot :: %5.4f", float(fpot.GetValue()));
				lcda->Printf(DriverStationLCD::kUser_Line1, 1, "F-Rot val :: %5.4f", frr);
				lcda->UpdateLCD();
				printtime.Reset();
			}
			setMotors();
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void setMotors()
	{
		fldrive.Set(fl);
		frdrive.Set(fr);
		bldrive.Set(bl);
		brdrive.Set(br);
		frot.Set(frr);
	}
	
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

