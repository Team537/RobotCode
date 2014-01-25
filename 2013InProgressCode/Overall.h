#ifndef OVERALL_H
#define OVERALL_H
void AutonomousCode (void) // Runs autonomous
{
	AutonomousLogicGo(); // Autonomous logic control
	AutoDriveGo(); // Drives the autonomous
}
void TeleoperatedCode (void) // Runs teleoperated
{
	DriveStartLoopGo(); // Prepares for each loop
	DriveGo(); // Drives the teleop
	DriveDisplayGo(); // Preps and outputs driving data
	
}
#endif
