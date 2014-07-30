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
	Sort();
	SmartDashboard::PutNumber("A", A);
		SmartDashboard::PutNumber("B", B);
		SmartDashboard::PutNumber("C", C);
		SmartDashboard::PutNumber("D", D);
}

void Swerve::Sort(){
	Ratio = A;
	if (Ratio < B){
		Ratio = B;
	}
	if (Ratio < C){
		Ratio = C;
	}
	if (Ratio < D){
		Ratio = D;
	}
	if (Ratio > 1){
		A/=Ratio;
		B/=Ratio;
		C/=Ratio;
		D/=Ratio;
		
	}
	
}

void Swerve::SetSpeed(){
	
}
