#ifndef ROBOT_FUNCTIONS_H
#define ROBOT_FUNCTIONS_H
void ButtonVarsSet (void)
{
	btnl1 = primcont.GetRawButton(BTN_L1);
	btnr1 = primcont.GetRawButton(BTN_R1);
	btnl2 = primcont.GetRawButton(BTN_L2);
	btnr2 = primcont.GetRawButton(BTN_R2);
}
void StartAutoTime()
{
	autotimer.Stop(); // Stops the timer
	autotimer.Reset(); // Sets the timer to 0
	autotimer.Start(); // Starts the timer
}
void StartTime()
{
	timer.Start(); // Starts the timer
}
void EncoderStop (void)
{
	lenc.Stop(); // Stops the left encoder
	renc.Stop(); // Stops the right encoder
}
void EncoderStart (void)
{
	lenc.Start(); // Starts the left encoder
	renc.Start(); // Starts the right encoder
}
void Shifting (void)
{
	if(btnl2 == 1) // Shifting to low gear if L2 is pressed
	{
		shiftHi.Set(NO); // Turns off high gear
		shiftLow.Set(YES); // Turns on low gear
	}
	else if(btnr2 == 1) // Shifting to high gear if R2 is pressed
	{
		shiftLow.Set(NO); // Turns off low gear
		shiftHi.Set(YES); // Turns on high gear
	}
}
void JoystickVariables (void)
{
	// Assigns joystick values to variables 
	prstk = primcont.GetRawAxis(RIGHTSTICK);  // Y of right joystick of the PS3 
	if(mode < 2) // Sets left stick equal to the right stick in the straight modes
		plstk = primcont.GetRawAxis(LEFTSTICK);  // Y of left joystick of the PS3
	else
		plstk = prstk; // Sets right variable to the left variable in the straight modes
}
void Encoders (void)
{
	if(mode > 1) // Checks if the robot is in a straight mode
	{
		lencvar = lenc.Get(); // Gets the left encoder value
		rencvar = lenc.Get(); // Gets the right encoder value
		EncoderRatio();
	}
}
void SetMotors (void)
{
	// Setting motor speeds
	left.SetSpeed(plspd); // Sets the left motor equal to the final left speed
	right.SetSpeed(-prspd); // Sets the right motor equal to the final right speed
	// Something is negative with mechanical or electrical for the right motor - not our fault: NEVER OUR FAULT
}
void GearStrings (void)
{
	if(shiftHi.Get() == YES) // Sets the gear output to high if the robot is in high gear
		gearstring = "High"; // Sets the gear output to high
	else if (shiftLow.Get() == YES) // Sets the gear output to low if the robot is in low gear
		gearstring = "Low"; // Sets the gear output to low
	autoswitchval1 = autoswitch1.Get();
	autoswitchval2 = autoswitch2.Get();
	if (autoswitchval1 == autoswitchval2)
		autoswitchval = 0;
	else if (autoswitchval1 > autoswitchval2)
			autoswitchval = -1;
	else if (autoswitchval1 < autoswitchval2)
			autoswitchval = 1;
}
void Print (void)
{
	// Displays data
	#ifdef PRINT_DEBUG // Printing function
	if (timer.Get() > PRINT_TIME) // Checks if 0.25 seconds have passed since the last print
	{
		lcd->Clear(); // Clears message box
		lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Left = %.1f", -plspd); // Displays left speed
		lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Right = %.1f", -prspd); // Displays right speed
		lcd->Printf(DriverStationLCD::kUser_Line3, 1, "Turn = %.1f", turn); // Displays turnyness value
		lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Mode = %s", modestring); // Displays driving mode
		lcd->Printf(DriverStationLCD::kUser_Line5, 1, "Gear = %s", gearstring); // Displays gear
		lcd->Printf(DriverStationLCD::kUser_Line6, 1, "Auto Switch = %.1f", autoswitchval); // Displays autonomous switch value
		lcd->UpdateLCD(); // Updates screen with new data
		timer.Reset(); // Resets printing timer
	}
	#endif // Ends the printing function
}
#endif
