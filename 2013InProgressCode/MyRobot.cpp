#include "WPILib.h" // Includes the FIRST WPILib
#include "CompressorManager.h" // Includes the compressor file
#include "Schematic.h" // Includes the schematic
#include <cmath> // Includes the cmath math library
DriverStationLCD *lcda = DriverStationLCD::GetInstance();
#define PRINT_DEBUG // Defines the print function

template<typename T>  // Declares a fancy sign function
inline T sign(T value) { return (T(0) < value) - (value < T(0)); } // A fancy sign function

// Declares variables
	float rampspd = 0.1f; // Speed of ramping (bigger = faster ramping)
	float plvirt; // Imaginary person on primary left joystick
	float prvirt; // Imaginary person on primary right joystick
	float srvirt; // Imaginary person on secondary right joystick
	float plstk = 0; // Y position of left joystick
	float prstk = 0; // Y position of right joystick
	float plspd = 0; // Left motor speed
	float prspd = 0; // Right motor speed
	float turn = 0; // Turnyness (scale of -1 to 1)
	bool btnl1 = 0; // L1 pressed?
	bool btnr1 = 0; // R1 pressed?
	bool btnl2 = 0; // L2 pressed?
	bool btnr2 = 0; // R2 pressed?
	bool btnsl1 = 0; // Secondary L1 pressed?
	bool btnsr1 = 0; // Secondary R1 pressed?
	float deadband = 0.15f; // Buffer for joystick not ending up exactly at 0 when let go of
	int mode = 0; // Mode variable: 0 = tank, 1 = turbo, 2 = straight, 3 = straight turbo
	char * modestring = "Tank"; // Mode output string
	char * gearstring = "Unknown"; // Gear output string
	float lencvar; // Left encoder variable
	float rencvar; // Right encoder variable
	float encratio; // Encoder ratio, small over big
	float spdmax = 0.7; // Speed max
	float autoswitchval1;
	float autoswitchval2;
	float autoswitchval; // Autonomous switch value
	int frisbees; // Number of frisbees
	/*
	float shooterdistsensor;
	float frisbeex;
	float frisbeexgoal;
	float frisbeey;
	float frisbeeygoal;
	float frisbeetime;
	float frisbeemuzzlevelocity;
	float shooteranglerad;
	float shooterheight;
	float shooterlength;
	*/

class RobotDemo : public SimpleRobot
{
	// Declares class instances
	Joystick primcont; // Primary controller joysticks
	Joystick seccont; // Secondary controller joysticks
	Victor left; // Left side motor
	Victor right; // Right side motor
	CompressorManager comp; // Compressor
	Compressor thing;
	Timer timer; // Printing timer
	Timer autotimer; // Autonomous timer
	Solenoid shiftHi, shiftLow; // Gear shifting solenoids
	DriverStationLCD* lcd; // Driver station message box
	Encoder lenc; // Left encoder
	Encoder renc; // Right encoder
	AnalogChannel shootpot; // Shooter potentiometer
	DigitalInput autoswitch1, autoswitch2; // Autonomous Switch
#include "Functions.h"
#include "RobotFunctions.h"
#include "Go.h"
#include "Overall.h"
public:
	RobotDemo(void):
		// Initializes class instances (in the same order as above)
		primcont(PRIMCONT), // Initializes the primary controller
		seccont(SECCONT), // Initializes the secondary controller
		left(LEFT_MOTOR), // Initializes the left motor
		right(RIGHT_MOTOR), // Initializes the right motor
		comp(COMPRESSOR), // Initializes the compresser
		thing(COMPRESSOR),
		shiftHi(SHIFT_RIGHT), // Initializes the high shifting solenoid
		shiftLow(SHIFT_LEFT), // Initializes the low shifting solenoid
		lcd(DriverStationLCD::GetInstance()), // Initializes the driver station message box
		lenc(LEFT_ENCODER), // Initializes the left encoder
		renc(RIGHT_ENCODER), // Initializes the right encoder
		shootpot(SHOOT_POT),
		autoswitch1(AUTO_SWITCH_ONE),
		autoswitch2(AUTO_SWITCH_TWO)
	{
		
	}
	void Autonomous(void) // All the autonomous code goes in here
	{
		AutonomousStartGo(); // Gets ready for autonomous
		StartTime(); // Starts the timer
		while (IsAutonomous())
		{
			AutonomousCode(); // Runs autonomous
		}
	}
	void OperatorControl(void) // All the teleop code goes in here
	{
		StartTime(); // Starts the timer
		while (IsOperatorControl())
		{
			//left.Set(1);
			//thing.Start();
			//right.Set(1);
			//lcda->Clear();
			//lcda->Printf(DriverStationLCD::kUser_Line3, 1, "Comp :: %f", left.Get());
			//lcda->UpdateLCD();
			//thing.Start();
			TeleoperatedCode(); // Runs teleoperated
		}
	}
};
START_ROBOT_CLASS(RobotDemo);
