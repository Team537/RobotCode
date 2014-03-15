#include "WPILib.h"
#include "Schematic.h"
#include <cmath>
class RobotDemo : public SimpleRobot
{
private:
	float x,y,angle,magnitude,x2,y2,front,back;
	Joystick Stick;
	Victor flmot, frmot, blmot, brmot, fturn, bturn;
	AnalogChannel fpot, bpot;
	Timer timer;
	DriverStationLCD* lcd;
public:
	RobotDemo():
		Stick (1),
		flmot (FLMOT),
		frmot (FRMOT),
		blmot (BLMOT),
		brmot (BRMOT),
		fturn (FTURN),
		bturn (BTURN),
		fpot (FPOT),
		bpot (BPOT),
		lcd(DriverStationLCD::GetInstance())
	{
		
	}
	void Autonomous()
	{
	
	}
	void OperatorControl()
	{
		timer.Start();
		while (IsOperatorControl())
		{
			x = Stick.GetRawAxis(1);
			y = -Stick.GetRawAxis(2);
			if (fabs(x) < 0.1)
			{
				x = 0;
			}
			if (fabs(y) < 0.1)
			{
				y = 0;
			}
			x2 = x*x;
			y2 = y*y;
			magnitude = pow((x2+y2),0.5);
			angle = atan2(y,x)*180/PI;
			magnitude = max(magnitude, -1);
			magnitude = min(magnitude, 1);
			if (angle < 0)
			{
				angle += 180;
				magnitude *= -1;
			}
			/*front = 730 - (angle * 2.7888);
			if ((front + 5) < float(fpot.GetValue()))
			{
				fturn.Set(0.5);
			}
			else if ((front - 5) > float(fpot.GetValue()))
			{
				fturn.Set(-0.5);
			}
			else
			{
				fturn.Set(0);
			}*/
			back = 235 + (angle * 2.8611);
			if ((back + 10) < float(bpot.GetValue()))
						{
							bturn.Set(0.5);
						}
						else if ((back - 10) > float(bpot.GetValue()))
						{
							bturn.Set(-0.5);
						}
						else
						{
							bturn.Set(0);
						}
					if (timer.Get() > 0.1)
					{
						lcd->Clear();
						lcd->Printf(DriverStationLCD::kUser_Line1, 1, "Front = %5.4f", front);
						lcd->Printf(DriverStationLCD::kUser_Line2, 1, "Back = %5.4f", back);
						lcd->Printf(DriverStationLCD::kUser_Line3, 1, "Front Pot = %5.4f", float(fpot.GetValue()));
						lcd->Printf(DriverStationLCD::kUser_Line4, 1, "Back Pot = %5.4f", float(bpot.GetValue()));
						lcd->Printf(DriverStationLCD::kUser_Line5, 1, "Angle = %5.4f", angle);
						lcd->Printf(DriverStationLCD::kUser_Line6, 1, "Magnitude = %5.4f", magnitude);
						lcd->UpdateLCD();
						timer.Reset();
						timer.Start();
					}
			
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

