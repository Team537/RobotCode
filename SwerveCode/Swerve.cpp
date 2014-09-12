#include "Swerve.h"
#include "Schematic.h"
#include "cmath"
#include "WPILib.h"

void Swerve::SetVariables(float Magnitude, float DirectionRadians, float Twist){
	if (fabs(Magnitude) <= deadband){
		Magnitude = 0;
	}
	if (fabs(DirectionRadians) <= deadbandrad){
			DirectionRadians = 0;
	}
	if (fabs(Twist) <= deadband){
			Twist = 0;
	}
	SmartDashboard::PutNumber("Test", 16);
	A = (cos(DirectionRadians)*Magnitude)-(Twist*LENGTH);
	B = (cos(DirectionRadians)*Magnitude)+(Twist*LENGTH);
	C = (sin(DirectionRadians)*Magnitude)-(Twist*WIDTH);
	D = (sin(DirectionRadians)*Magnitude)+(Twist*WIDTH);
	SmartDashboard::PutNumber("Test2", 537);
	SmartDashboard::PutNumber("A", A);
	SmartDashboard::PutNumber("B", B);
	SmartDashboard::PutNumber("C", C);
	SmartDashboard::PutNumber("D", D);
	SmartDashboard::PutNumber("Test3", 538);
	
}



void Swerve::FindWheelSpeed(){
	frontlspeed = sqrt((pow(B,2))+(pow(D,2)));
	frontrspeed = sqrt((pow(B,2))+(pow(C,2)));
	backlspeed = sqrt((pow(A,2))+(pow(D,2)));
	backrspeed = sqrt((pow(A,2))+(pow(D,2)));
}

void Swerve::Sort(){
	Ratio = frontlspeed;
	if (Ratio < frontrspeed){
		Ratio = frontrspeed;
	}
	if (Ratio < backlspeed){
		Ratio = backlspeed;
	}
	if (Ratio < backlspeed){
		Ratio = backlspeed;
	}
	if (Ratio > 1){
		frontlspeed/=Ratio;
		frontrspeed/=Ratio;
		backlspeed/=Ratio;
		backrspeed/=Ratio;
		
	}
	SmartDashboard::PutNumber("Test4", 539);
}
void Swerve::Ramping() {
	Sort();
	frontlspeed = LEFT_DRIVE_DIRECTION * frontlspeed;
	frontrspeed = RIGHT_DRIVE_DIRECTION *frontrspeed;
	backlspeed = LEFT_DRIVE_DIRECTION * backlspeed;
	backrspeed = RIGHT_DRIVE_DIRECTION * backrspeed;
	frontldif = frontlspeed - FrontLeftOldSpeed;
	frontrdif = frontrspeed - FrontRightOldSpeed;
	backldif = backlspeed - BackLeftOldSpeed;
	backrdif = backrspeed - BackRightOldSpeed;
	if (fabs(frontldif) >= RAMP_SPEED) {
		FrontLeftOldSpeed += RAMP_SPEED * Sign(frontldif);
	}
	if (fabs(frontrdif) >= RAMP_SPEED) {
		FrontRightOldSpeed += RAMP_SPEED * Sign(frontrdif);
	}
	if (fabs(backldif) >= RAMP_SPEED) {
		BackLeftOldSpeed += RAMP_SPEED * Sign(backldif);
	}
	if (fabs(backrdif) >= RAMP_SPEED) {
		BackRightOldSpeed += RAMP_SPEED * Sign(backrdif);
	}
	if (frontlspeed == 0) {
		FrontLeftOldSpeed = 0;
	}
	if (frontrdif == 0) {
		FrontRightOldSpeed = 0;
	}
	if (frontlspeed == 0) {
		BackLeftOldSpeed = 0;
	}
	if (frontrdif == 0) {
		BackRightOldSpeed = 0;
	}
}
void Swerve::SetWheelSpeed()
{
	SFL.Set(FrontLeftOldSpeed);
	SFR.Set(FrontRightOldSpeed);
	SBL.Set(BackLeftOldSpeed);
	SBR.Set(BackRightOldSpeed);
}
float Swerve::Sign(float InputSign) {
	if (InputSign > 0) {
		return 1;
	}
	if (InputSign < 0) {
		return -1;
	}
	return 0;
}
void Swerve::FindAngle(){
	FLAng = atan2(B,D)*180/PI;
	FRAng = atan2(B,C)*180/PI;
	BLAng = atan2(A,D)*180/PI;
	BRAng = atan2(A,C)*180/PI;
}

void Swerve::SetAngle(){
	FrontRightAngle.Enable();
	FrontRightAngle.SetSetpoint(FRAng);
	FrontLeftAngle.Enable();
	FrontLeftAngle.SetSetpoint(FLAng);
	BackRightAngle.Enable();
	BackRightAngle.SetSetpoint(BRAng);
	BackLeftAngle.Enable();
	BackLeftAngle.SetSetpoint(BLAng);
	if (FrontRightAngle.OnTarget())
		AFR.Set(0);
	if (FrontLeftAngle.OnTarget())
		AFL.Set(0);
	if (BackRightAngle.OnTarget())
		ABR.Set(0);
	if (BackLeftAngle.OnTarget())
		ABL.Set(0);
}
