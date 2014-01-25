#include "WPILib.h" 
#include "Schematic.h"
#include "ControllerSchematic.h"
#include "Constants.h"
#include "Latch.h"
#include "Ramping/Ramping.h"
#include "PID/PIDControl.h"
#include "dashData.h"
#include <DriverStationLCD.h>
#include <stdio.h>
#include "vizData.h"
#include <cmath>

DriverStationLCD* lcda = DriverStationLCD::GetInstance();

class Team537Bot : public SimpleRobot
{
	Joystick leftStick, rightStick, secondary;
	Victor leftDrive, rightDrive, shootSpeed, collFeed, collCollect;
	//Encoder leftCoder, rightCoder;
	Compressor comp;
	Timer time, feedTime,  printTime, autoTime, aimTimer;
	Solenoid shiftHi, shiftLow/*, bridgePush*/;
	Victor shootPitch/*, shootYaw*/;
	Relay rubbercoatedaluminumRod;
	AnalogChannel pitchPot;
	//Encoder flyWheelSpeed;
	PosPID flyWheelPID, pitchPID, yawPID;
	AnalogChannel lowerBall, midBall, upperBall;
	Latch latch;
	GearTooth gt;
	dashData debug;
	//DigitalInput switch1, switch2;
	vizData vd;

	float flycnt;
	//float clickTarget;
	//float speedTarget;
	float shooterMotor;
	bool speedReady;
	int pdesiredPos, pPot;
	int h_center, yDesPos;
	int numBalls;
	float pi;
	int state;
public:
	Team537Bot(void):
		leftStick(CONT_LEFT),
		rightStick(CONT_RIGHT),
		secondary(CONT_SECOND),
		leftDrive(DRIVE_LEFT),
		rightDrive(DRIVE_RIGHT),
		shootSpeed(SHOOT_FLY),
		collFeed(COLLECT_FEED),
		collCollect(COLLECT_COLLECT),
		//leftCoder(DRIVE_LEFT_ENCODER),
		//rightCoder(DRIVE_RIGHT_ENCODER),
		comp(COMPRESSOR),
		time(),
		feedTime(),
		printTime(),
		autoTime(),
		aimTimer(),
		shiftHi(DRIVE_SHIFT_HIGH),
		shiftLow(DRIVE_SHIFT_LOW),
		//bridgePush(BRIDGE_PUSH),
		shootPitch(SHOOT_PITCH),
		//shootYaw(SHOOT_YAW),
		rubbercoatedaluminumRod(COLLECT_rubbercoatedaluminumROD),
		pitchPot(SHOOT_PITCH_POT),
		//flyWheelSpeed(SHOOT_FLY_ENC),
		flyWheelPID(FW_P_GAIN, FW_I_GAIN, FW_D_GAIN, FW_MAX_ERROR, FW_MAX_OUTPUT),
		pitchPID(PCH_P_GAIN, PCH_I_GAIN, PCH_D_GAIN, PCH_MAX_ERROR, PCH_MAX_OUTPUT),
		yawPID(YAW_P_GAIN, YAW_I_GAIN, YAW_D_GAIN, YAW_MAX_ERROR, YAW_MAX_OUTPUT),
		lowerBall(LOWER_BALL),
		midBall(MID_BALL),
		upperBall(TOP_BALL),
		latch(),
		gt(1, 5, false),
		//switch1(A_SWITCH_1),
		//switch2(A_SWITCH_2),
		pi(3.141592653589793238462643383279)
	{
		GetWatchdog().SetEnabled(true);
		GetWatchdog().SetExpiration(10.0);
		debug.dashLink();
		feedTime.Start();
		printTime.Start();
		//flyWheelSpeed.Start();
		comp.Start();
		gt.Start();
		time.Start();
		flycnt = 0;
		//clickTarget = 65;
		//speedTarget = 1.0;
		//shooterMotor = 1.0;
		speedReady = false;
		//flyWheelSpeed.SetDistancePerPulse(.45);
		//leftCoder.Start();
		//rightCoder.Start();
		pdesiredPos = 610;
		numBalls = 0;
		aimTimer.Start();
		state = 0;
	}

	/* Function to determine what to do with compressor*/
	void testCompressor(void)
	{
		if (comp.GetPressureSwitchValue() == 1)
			comp.Stop();
		else
			comp.Start();
	}

	/* Function to change shroud angle */
	
	void changeAngle(int position, bool PID)
	{
		if (PID)
		{
			if (position > PITCH_MAX)
				position = PITCH_MAX;
			else if (position < PITCH_MIN)
				position = PITCH_MIN;

			pPot = pitchPot.GetValue();
			pdesiredPos = position;

			float motorVal = pitchPID.Update(pPot, pdesiredPos);
			if (motorVal < PITCH_DEAD && motorVal > -PITCH_DEAD)
				motorVal = 0.0;

			if (pitchPot.GetValue() > PITCH_MAX || pitchPot.GetValue() < PITCH_MIN)
			{
				motorVal = 0.0;
				return;
			}

			shootPitch.Set(motorVal);
		}
		else
		{
			float motorVal;
			int pval = pitchPot.GetValue();

			if (pval > position + 3)
				motorVal = 0.1;
			else if (pval < position - 3)
				motorVal = -0.1;
			else
				motorVal = 0.0;

			shootPitch.Set(motorVal);
		}
	}

	void OperatorControl(void)
	{
		/* declaring the shit ton of variables we use */
		INT16 pitchTarget = pitchPot.GetValue();
		//flyWheelSpeed.SetDistancePerPulse(.45);
		GetWatchdog().SetEnabled(true);
		GetWatchdog().SetExpiration(10.0);
		float speedTarget = 1.0;
		float flycnt = 0;
		float clickTarget = 60;
		DriverStationLCD* lcd = DriverStationLCD::GetInstance();
		float pgain = FW_P_GAIN, igain = FW_I_GAIN, dgain = FW_D_GAIN;
		Latch platch, dlatch, ilatch;
		float shooterMotor = 0.5;

		int pitchDesired = 600;
		flyWheelPID.setDebug(&debug);

		bool lat = 1;

		//float fwDesired = 1000, fwCurrent;
		//float fwDesDead = 100;

		time.Start();

		bool DCallow = true, DFallow = true;

		float lDriveSpeed, rDriveSpeed;
		bool shiftStatus = 0;
		bool bridgeStatus;
		float collectorSpeed, feederSpeed;
		int bRod;
		float yawSpeed, pitchSpeed;
		
		int prevSS = 0, currSS;

		bool ssReady = false;

		//leftCoder.Reset();
		//rightCoder.Reset();

		bool usingPreset = false;
		bool driveStaight = false;
		
		int collStatus = 0, shiftingStatus/*, pushStatus*/;
		
		int collLat = 0;
		
		//int bridgeLat = 0;
		
		bool firstTime = true;
		int s_preset = 0, prevPreset = 1;
		int shiftVal = 0;
		//int newHoopCenter = 0, prevHoopCenter = 0;

		bool userAim = true;
		bool firstAim = false;
		double rotTime = 0;
		int aimDir = 0;
		int d, h;
		int tstamp, otstamp = -1;
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();

			/* Makes sure compressor turns off when it gets full */
			testCompressor();

			/* Drives the left and right skates */
			lDriveSpeed = leftStick.GetY();
			rDriveSpeed = -rightStick.GetY();

			/*
			Pushes bridge when right trigger is pressed and send status
			bridgeStatus = leftStick.GetTrigger();
			if (bridgePush.Get())
				pushStatus = 'D';
			else
				pushStatus = 'U';
			
			if (pushStatus != bridgeLat){
				debug.sendInt(PUSHER, pushStatus);
				bridgeLat = pushStatus;
			}
			*/
			/* Set Collector and send its status */
			if (rightStick.GetRawButton(11))
			{
				lat = false;
			}
			else if (rightStick.GetTrigger())
			{
				lat = true;
			}
			if(collCollect.Get() > 0)
			{
				collStatus = 'R';
			}
			else if(collCollect.Get() < 0)
			{
				collStatus= 'F';
			}
			else
			{
				collStatus = 'S';
			}
			if (collLat != collStatus) {
				//printf("Sending: %d\n", collStatus);
				debug.sendInt(CLCT, collStatus);
				collLat = collStatus;
			}
			if (DCallow)
				collectorSpeed = (true == lat) ? -0.95 : 0.0;

			/* Set both skates to same speed */
			if (leftStick.GetRawButton(3))
				driveStaight = true;
			else
				driveStaight = false;
			
			/* Shifts to high gear if right 3 is pressed */
			if (rightStick.GetRawButton(3))
				shiftStatus = 1;

			/* Shifts to low gear if right 2 is pressed and send status */
			if (rightStick.GetRawButton(2))
				shiftStatus = 0;
			if (shiftHi.Get())
				shiftingStatus = 'H';
			else
				shiftingStatus = 'L';
			if (shiftVal != shiftingStatus) {
				debug.sendInt(GEAR, shiftingStatus);
				
				
				shiftVal = shiftingStatus;
			}

			
			/* Adjusts the PID values */
			if (printTime.Get() > .25)
			{
				//lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Encoder %4.0f", flyWheelSpeed.Get());
				if (platch.UpdateLatch(leftStick.GetRawButton(6)))
					pgain += 0.10;
				else if (platch.UpdateLatch(leftStick.GetRawButton(7)))
					pgain -= 0.10;

				if (dlatch.UpdateLatch(leftStick.GetRawButton(11)))
					dgain += 1.0;
				else if (dlatch.UpdateLatch(leftStick.GetRawButton(10)))
					dgain -= 1.0;

				if (ilatch.UpdateLatch(leftStick.GetRawButton(9)))
					igain += .10;
				else if (ilatch.UpdateLatch(leftStick.GetRawButton(8)))
					igain -= .10;

				flyWheelPID.adjustPGain(pgain);
				flyWheelPID.adjustDGain(dgain);
				flyWheelPID.adjustIGain(igain);
				char sb[120];
				sprintf(sb, "%8.1f %8.1f %8.1f", pgain, dgain, igain);
			}
			
			/* Rotates the RubberCoatedAluminum Rod */
			if (secondary.GetRawButton(BTN_L1))
				bRod = 1;
			else
				bRod = 0;
			
			/* Adjust shroud speed and set presets if desired */
			pitchTarget = pitchPot.GetValue();
			pitchSpeed = secondary.GetRawAxis(AXIS_RIGHT_Y) * .5;
			if (pitchSpeed > .05 || pitchSpeed < -0.05)
			{
				usingPreset = false;
				s_preset = 0;
			}
			
			if (secondary.GetRawButton(BTN_TRIANGLE)) // Fender
			{
				clickTarget = 45;
				pitchDesired = 780;
				usingPreset = true;
				s_preset = 4;
			}
			else if (secondary.GetRawButton(BTN_SQUARE)) // Front of Key
			{
				clickTarget = 65;
				pitchDesired = 607;
				usingPreset = true;
				s_preset = 3;
			}
			else if (secondary.GetRawButton(BTN_CIRCLE)) // Back of Key
			{
				clickTarget = 65;
				pitchDesired = 620;
				usingPreset = true;
				s_preset = 2;
			}
			else if (secondary.GetRawButton(BTN_CROSS)) // Bump
			{
				clickTarget = 107;
				pitchDesired = 630;
				usingPreset = true;
				s_preset = 1;
			}
			if (prevPreset != s_preset){
				debug.sendInt(CURR_PRESET, s_preset);
				prevPreset = s_preset;
			}
			
			if (((pitchTarget > PITCH_MAX) && (pitchSpeed > 0)) || ((pitchTarget < PITCH_MIN) && pitchSpeed < 0))
			{
				pitchSpeed = 0.0;
				usingPreset = false;
				s_preset = 0;
			}
			
			/* Gets status from ball IR sensors */
			bool lb, mb, ub;
			if (upperBall.GetVoltage() >= 1.5)
				ub = true;
			else
				ub = false;
			if (midBall.GetVoltage() >= 1.5)
				mb = true;
			else
				mb = false;
			if (lowerBall.GetVoltage() >= 1.5)
				lb = true;
			else
				lb = false;

			currSS = gt.Get();
			
			/* Automaticly moves balls in feeder */
			switch (state)
			{
			case 0:
				DCallow = true;
				DFallow = false;
				feederSpeed = 0.0;
				if (firstTime)
				{
					numBalls = 0;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				if (secondary.GetRawButton(BTN_R1))
				{
					state = 7;
					firstTime = true;
				}
				else if (lb)
				{
					state = 1;
					firstTime = true;
				}
				break;
			case 1:
				DCallow = true;
				DFallow = false;
				if (firstTime)
				{
					numBalls = 1;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				feederSpeed = 0.33;
				if (mb)
					state = 2;
				break;
			case 2:
				DCallow = true;
				DFallow = false;
				if (firstTime)
				{
					numBalls = 1;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				feederSpeed = 0.0;
				if (secondary.GetRawButton(BTN_R1))
				{
					state = 7;
					firstTime = true;
				}
				else if (lb)
				{
					state = 3;
					firstTime = true;
				}
				break;
			case 3:
				DCallow = true;
				DFallow = false;
				if (firstTime)
				{
					numBalls = 2;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				feederSpeed = 0.33;
				if (ub)
				{
					state = 4;
					firstTime = true;
				}
				break;
			case 4:
				DCallow = true;
				DFallow = false;
				if (firstTime)
				{
					numBalls = 2;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				feederSpeed = 0.0;
				if (secondary.GetRawButton(BTN_R1))
				{
					state = 7;
					firstTime = true;
				}
				else if (lb)
				{
					state = 5;
					firstTime = true;
				}
				break;
			case 5:
				DCallow = false;
				DFallow = false;
				if (firstTime)
				{
					numBalls = 3;
					debug.sendInt(BALL_COUNT, numBalls);
					firstTime = false;
				}
				feederSpeed = 0.33;
				collectorSpeed = -0.95;
				feedTime.Reset();
				state = 6;
				break;
			case 6:
				if (0.5 < feedTime.Get())
				{
					DFallow = true;
					DCallow = false;
					feederSpeed = 0.0;
					collectorSpeed = -0.95;
					state = 7;
				}
				break;
			case 7:
				DFallow = true;
				DCallow = false;
				collectorSpeed = 0.95;

				if (ssReady && flycnt <= clickTarget - 7) {
					numBalls--;
					debug.sendInt(BALL_COUNT, numBalls);
					ssReady = false;
				}
				if (flycnt <= clickTarget + 4 && flycnt >= clickTarget - 4)
					ssReady = true;
				else
					ssReady = false;

				if (!lb && !mb && !ub && rightStick.GetTrigger())
				{
					state = 0;
					lat = true;
					firstTime = true;
				}
				break;
			}
			
			prevSS = currSS;
			
			/* Runs the collector if R1 is pressed */
			if (DFallow)
				feederSpeed = (secondary.GetRawButton(BTN_R1)) ? 0.5 : 0.0;


			/* Rotates Yaw */
			if (secondary.GetRawAxis(AXIS_DPAD_X) >= 1.0)
				yawSpeed = 0.65;
			else if (secondary.GetRawAxis(AXIS_DPAD_X) <= -1.0)
				yawSpeed = -0.65;
			else
				 yawSpeed = secondary.GetRawAxis(AXIS_LEFT_X) * 0.40;

			/* Auto aims if dpad down is pressed */
			if (secondary.GetRawAxis(AXIS_DPAD_Y) >= 1.0)
			{
				int height;
				userAim = false;
				if (firstAim)
				{
					d = vd.getCenter(tstamp, height);
					otstamp = tstamp;
					//15-19.99 ppf=15 dfp=27
					//20-24.99 ppf=19 dfp=21
					//25-30.99 ppf=22 dfp=17
					//31-40.99 ppf=32 dfp=12
					//41-70.00 ppf=41 dfp=9
					firstAim = false;
					double ppf, dfp;

					d = d - 160;
					h = height;

					if(d < 0)
					{
						aimDir = -1;
						d *= -1;
					}
					else
						aimDir = 1;

					if (h >= 15 && h < 20) {
						ppf = 15;
						dfp = 27;
					}
					else if (h >= 20 && h < 25) {
						ppf = 19;
						dfp = 21;
					}
					else if (h >= 25 && h < 31) {
						ppf = 22;
						dfp = 17;
					}
					else if (h >= 31 && h < 41) {
						ppf = 32;
						dfp = 12;
					}
					else if (h >= 41 && h <= 70) {
						ppf = 41;
						dfp = 9;
					}
					else
					{
						ppf = 324;
						dfp = 1;
					}
					// rotTime = atan2(d,324)/0.461;
					rotTime = atan2(d, ppf*dfp)/0.461;
					//printf("Height: %d  |  Distance: %d  |  Time: %f\n", h, d, rotTime);
					aimTimer.Reset();
				}
				
				/*if (aimTimer.Get() <= rotTime)
					shootYaw.Set(.7 * aimDir);
				else
					shootYaw.Set(0.0);
				*/
			}
			else
			{
				userAim = true;
				firstAim = true;
			}

			
			/* PID stuff for the flywheel */
			if (time.Get() > 0.1)
			{
				flycnt = (float)gt.Get() * 1.0;
				gt.Reset();
				time.Reset();

				speedTarget += flyWheelPID.Update(flycnt, clickTarget);
				if (speedTarget > FW_MAX_OUTPUT)
					speedTarget = FW_MAX_OUTPUT;
				else if (speedTarget <= 0)
					speedTarget = 0;
				//shooterMotor = speedTarget / 250;
				//shooterMotor = (shooterMotor > 1.0) ? 1.0 : (shooterMotor < 0.0) ? 0.0 : shooterMotor;
				//debug.sendFloat(2, flycnt);
				//debug.sendFloat(3, speedTarget);
				//debug.sendFloat(4, clickTarget);
				//debug.sendFloat(3, speedTarget);
				//debug.sendInt(2, s(int) flycnt);
				//debug.sendInt(4, (int) clickTarget);
			}

			/* Prints out values so we can get "useful" info */
			if (printTime.Get() > .25)
			{
				/* Adjusts the shooter Speed. Some reason this is here */
				const float FLY_CHNG = .05;
				if (secondary.GetRawButton(BTN_L2)) {
					shooterMotor += FLY_CHNG;
					//clickTarget += FLY_CHNG;
					//ssReady = false;
				}
				if (secondary.GetRawButton(BTN_R2)) {
					shooterMotor -= FLY_CHNG;
					//clickTarget -= FLY_CHNG;
					//ssReady = false;
				}
				/*if (clickTarget > 250)
					clickTarget = 250;
				if (clickTarget < 0)
					clickTarget = 0;
				*/
				debug.sendInt(ACTUAL, (int) flycnt);
				debug.sendInt(WANTED, (int) clickTarget);
				debug.sendInt(CURR_ANGLE, pitchTarget);

				lcd->Clear();
				lcd->Printf(DriverStationLCD::kUser_Line1, 1, "FlyWheelxx %4.0f", clickTarget);
				lcd->Printf(DriverStationLCD::kUser_Line2, 1, " Actual :: %4.0f", flycnt);
				lcd->Printf(DriverStationLCD::kUser_Line3, 1, "Angle   :: %d", pitchTarget);
				lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Balls   :: %d", numBalls);
				//lcd->Printf(DriverStationLCD::kUser_Line5, 1, "Left: %d", leftCoder.Get());
				//lcd->Printf(DriverStationLCD::kUser_Line6, 1, "Right: %d ", rightCoder.Get());
				lcd->Printf(DriverStationLCD::kUser_Line6, 1, "bRod :: %d", bRod);
				lcd->UpdateLCD();
				
				printf("%d  |  %d,%d,%d  | V: %f \n", state, lb,mb,ub,midBall.GetVoltage());
				
				printTime.Reset();
			}

			/* Overrides the whole robot so only the pitch moves */
			if (rightStick.GetRawButton(8) && rightStick.GetRawButton(9))
			{
				//shooterMotor = 0;
				flyWheelPID.Reset();
				lDriveSpeed = 0;
				rDriveSpeed = 0;
				yawSpeed = 0;
				bridgeStatus = 0;
				collectorSpeed = 0;
				feederSpeed = 0;
				bRod = 0;
				pitchSpeed = secondary.GetRawAxis(AXIS_RIGHT_Y) * 0.5;
			}

			/* Sets All the Outputs */
			shootSpeed.Set(-shooterMotor);
			/*if (userAim)
			{
				shootYaw.Set(-yawSpeed);
				firstAim = true;
			}*/
			if (usingPreset)
				changeAngle(pitchDesired, true);
			else
				shootPitch.Set(pitchSpeed);
			if (driveStaight)
			{
				leftDrive.Set(-rDriveSpeed);
				rightDrive.Set(rDriveSpeed);
			}
			else
			{
				leftDrive.Set(lDriveSpeed);
				rightDrive.Set(rDriveSpeed);
			}
			shiftHi.Set(shiftStatus);
			shiftLow.Set(!shiftStatus);
			//bridgePush.Set(bridgeStatus);
			collCollect.Set(collectorSpeed);
			collFeed.Set(feederSpeed);
			if (bRod == 1)
				rubbercoatedaluminumRod.Set(Relay::kForward);
			else if (bRod == 0)
				rubbercoatedaluminumRod.Set(Relay::kOff);
		}
	}
};

START_ROBOT_CLASS(Team537Bot);
