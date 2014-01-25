#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void ImaginaryDriverSet (void)
{
	plstk = plvirt;
	prstk = prvirt;
}
void AutotimerManage (void)
{
	if (IsDisabled())
	{
		autotimer.Reset();
		autotimer.Stop();
	}
	if (IsEnabled())
	{
		autotimer.Start();
	}
}
void AutonomousLogic (void)
{
	/*
	Warning: The below code is all theoretical
	if (lenc.Get() < LEFT_PYRAMID_FRONT_ENCODER_VALUE and renc.Get() < RIGHT_PYRAMID_FRONT_ENCODER_VALUE)
	{
		mode = 2;
		prvirt = 1;
	}
	else if (lenc.Get() < LEFT_AUTONOMOUS_TURN_VALUE and renc.Get() < RIGHT_AUTONOMOUS_TURN_VALUE)
	{
		mode = 0;
		plvirt = autoswitchval * 1;
		prvirt = autoswitchval * -1;
	}
	else if (shootpot.GetValue() < AUTONOMOUS_HEIGHT_VALUE)
	{
		plvirt = 0;
		prvirt = 0;
		srvirt = 1;
	}
	else if (frisbees > 0)
	{
		srvirt = 0;
		btnsr1 = 1;
	}
	else if (lenc.Get() < LEFT_AUTONOMOUS_TURN_VALUE and renc.Get() < RIGHT_AUTONOMOUS_TURN_VALUE)
	{
		btnsr1 = 0;
		plvirt = autoswitchval * -1;
		prvirt = autoswitchval * 1;
	}
	else if (lenc.Get() < LEFT_PYRAMID_FRONT_ENCODER_VALUE and renc.Get() < RIGHT_PYRAMID_FRONT_ENCODER_VALUE)
	{
		mode = 2;
		prvirt = -1;
	}
	else if (lenc.Get() < LEFT_PYRAMID_FRONT_ENCODER_VALUE and renc.Get() < RIGHT_PYRAMID_FRONT_ENCODER_VALUE)
	{
		mode = 1;
		plvirt = autoswitchval * -1;
		prvirt = autoswitchval * 1;
	}
	// Warning: The above code is all theoretical
	*/
}
void ModeSet (void)
{
	mode = TANK; // Starts the mode at tank
	// Sets mode
	if(btnr1 == 1) // Turns on turbo mode if R1 is pressed
		mode += 1; // Switches the mode to a turbo mode
	if (btnl1 == 1) // Turns on straight mode if L1 is pressed
		mode += 2; // Switches the mode to a straight mode
	if(mode == TANK || mode == STRAIGHT) // Sets the max speed to 0.7 if not in a turbo mode
		spdmax = 0.7; // Sets the max speed to 0.7
	else
		spdmax = 1; // Sets the max speed to 1 if in a turbo mode
}
void Deadband (void)
{
	// Deadband logic
	if (fabs(plstk) <= deadband) // Checks if the left variable is less than the deadband
		plstk = 0; // Sets the left variable to 0 if it is in the deadband
	if (fabs(prstk) <= deadband) // Checks if the right variable is less than the deadband
		prstk = 0; // Sets the right variable to 0 if it is in the deadband
}
void Ramping (void)
{
	// Ramping logic
	if (plstk == 0) // Slows the left speed if it is in the deadband
		plspd -= sign(plspd) * rampspd; // Slows the left speed
	else if (fabs(plstk - plspd) > rampspd) // Speeds up the left speed if it is slower than the stick value
		plspd += sign(plstk) * rampspd; // Speeds up the left speed
	else 
		plspd = plstk; // Sets the left speed equal to the left stick value otherwise
	if (prstk == 0) // Slows the right speed if it is in the deadband
		prspd -= sign(prspd) * rampspd; // Slows the right speed
	else if (fabs(prstk - prspd) > rampspd) // Speeds up the right speed if it is slower than the stick value
		prspd += sign(prstk) * rampspd; // Speeds up the right speed
	else
		prspd = prstk; // Sets the right speed equal to the right stick value otherwise
}
void Clamping (void)
{
	// Clamping speed values
	plspd = min(plspd, spdmax); // Clamps the left speed to a max of the speed max
	plspd = max(plspd, -spdmax); // Clamps the left speed to a min of the negative speed max
	prspd = min(prspd, spdmax); // Clamps the right speed to a max of the speed max
	prspd = max(prspd, -spdmax); // Clamps the right speed to a min of the negative speed max
}
void EncoderRatio (void)
{
	if(lencvar < rencvar) // Checks if the left value is smaller than the right value
	{
		encratio = lencvar / rencvar; // Sets the smaller left value over the larger right value
		prspd *= encratio; // Multiplies the larger right speed by this ratio
	}
	else if(rencvar < lencvar) // Checks if the right value is smaller than the left value
	{
		encratio = rencvar / lencvar; // Sets the smaller right value over the larger left value
		plspd *= encratio; // Multiplies the larger left speed by this ratio
	}
}
/*
 * 
void PossibleParametricAimer (void)
{
	
}
*/
void StringPrep (void)
{
	// Prepping strings for display
	turn = (prspd - plspd) / 2; // Calculates turnyness with an ancient, complex formula
	if(mode == TANK) // Sets the mode output to tank if the robot is in tank
		modestring = "Tank"; // Sets the mode output to tank
	else if(mode == TURBO) // Sets the mode output to turbo if the robot is in turbo
		modestring = "Turbo"; // Sets the mode output to turbo
	else if(mode == STRAIGHT) // Sets the mode output to straight if the robot is in straight
		modestring = "Straight"; // Sets the mode output to straight
	else if(mode == STRAIGHT_TURBO) // Sets the mode output to straight turbo if the robot is in straight turbo
		modestring = "Straight Turbo"; // Sets the mode output to straight turbo
}
#endif
