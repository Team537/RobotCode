#include "WPILib.h"
#include "Schematic.h"
#include "DriveTrainManager.h" // Includes the DriveTrainManager class
#include "CompressorManager.h" // Includes the CompressorManager class
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	
	Joystick PrimaryController;
	CompressorManager comp; // Declares an object of the CompressorManager class
	DriveTrainManager DriveTrain; // Declares an object of the DriveTrainManager class
	
public:
	
	RobotDemo(void):
		PrimaryController(PRIMARY_CONTROLLER)
	{
		
	}
	void Autonomous()
	{
		
	}
	void OperatorControl(void)
	{
		DriveTrain.StartDriveTrain();
		while (IsOperatorControl() && IsEnabled())
		{
			comp.checkCompressor(); // Uses the CompressorManager class to run the compressor when needed
			DriveTrain.RunDriveTrain(PrimaryController.GetRawAxis(LEFT_JOYSTICK), PrimaryController.GetRawAxis(RIGHT_JOYSTICK), (int)PrimaryController.GetRawButton(BUTTON_HIGH_DRIVE_SHIFT), (int)PrimaryController.GetRawButton(BUTTON_LOW_DRIVE_SHIFT)); // Sends joystick values to the DriveTrainManager class
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
