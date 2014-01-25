#ifndef GO_H
#define GO_H
void AutonomousStartGo (void)
{
	EncoderStart();
	StartAutoTime();
}
void AutonomousLogicGo (void)
{
	AutotimerManage();
	AutonomousLogic();
}
void DriveStartLoopGo (void)
{
	ButtonVarsSet();
	EncoderStop();
	EncoderStart();
}
void AutoDriveGo (void)
{
	ImaginaryDriverSet();
	Shifting();
	Deadband();
	Ramping();
	Clamping();
	Encoders();
	SetMotors();
}
void AutoAimingGo (void)
{
	
}
void DriveGo (void)
{
	Shifting();
	ModeSet();
	JoystickVariables();
	Deadband();
	Ramping();
	Clamping();
	Encoders();
	SetMotors();
}
void DriveDisplayGo (void)
{
	StringPrep();
	GearStrings();
	Print();
}
#endif
