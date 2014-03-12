#include "CameraManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "nivision.h"
#include "WPILib.h"

bool CameraManager::IsHotGoal()
{
	    AxisCamera& camera = AxisCamera::GetInstance();
		SmartDashboard::PutNumber("counter", Counter);

		/*if (!camera.IsFreshImage())
		{
			SmartDashboard::PutString("Image", "Not Fresh");
			return LastValue;
		}*/
		SmartDashboard::PutNumber("line 17", 17);
		//if(Counter * Rate >= CameraTimer.Get())
		//{
			
			//return LastValue;
		//}
		ColorImage *CurrentImage = camera.GetImage();
		SmartDashboard::PutString("Image", "Fresh");	
		BinaryImage* ThresholdImage = CurrentImage->ThresholdRGB(100, 255, 100, 255, 100, 255);
		SmartDashboard::PutNumber("line 26", 26);
		ImageInfo info;
		Image *img = ThresholdImage->GetImaqImage();
		imaqGetImageInfo(img, &info);
		SmartDashboard::PutNumber("line 30", 30);
		
		int yellowCount = 0;
		unsigned char * pixels = (unsigned char *) info.imageStart;
		int y, x;
		for (y = 0; y < info.yRes; y++){
			for (x = 0; x < info.xRes; x++){
				int bitmapIndex = (info.pixelsPerLine *y) + x;
				if (pixels[bitmapIndex] == 1)
				{
					yellowCount++;
				}
			}
		}
		SmartDashboard::PutNumber("y res", y);
		SmartDashboard::PutNumber("x res", x);
		SmartDashboard::PutNumber("line 42", 42);
		LastValue = yellowCount > YELLOW_PIXEL_THRESHOLD;
		
		SmartDashboard::PutNumber("Yellow Count", yellowCount);
		delete CurrentImage;
		delete ThresholdImage;
		SmartDashboard::PutNumber("line 49", 49);
		Counter++;
		return LastValue;
	}
	void CameraManager::CameraStart()
	{
		
		CameraTimer.Start();
	}
	void CameraManager::CameraStop()
	{
		CameraTimer.Stop();
		CameraTimer.Reset();
	}

//  rcoe@wi.rr.com
//   first4me2011  

