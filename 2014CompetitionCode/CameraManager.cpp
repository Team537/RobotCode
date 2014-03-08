#include "CameraManager.h"
#include "Schematic.h"
#include "NameSchematic.h"
#include "WPILib.h"

bool CameraManager::IsHotGoal()
{
	return false;
	/*
	SmartDashboard::PutString("Image", "Not Fresh");
	AxisCamera &camera = AxisCamera::GetInstance(CAMERA_IP_ADDRESS);
	
	if (!camera.IsFreshImage())
	{
		SmartDashboard::PutString("Image", "Not Fresh");
		return LastValue;
	}

	SmartDashboard::PutString("Image", "Fresh");
	
	ColorImage *CurrentImage = camera.GetImage();	
	BinaryImage* ThresholdImage = CurrentImage->ThresholdRGB(0, 255, 00, 255, 0, 255);
	
	Image *img = ThresholdImage->GetImaqImage();
	img->
	LastValue = yellowCount > YELLOW_PIXEL_THRESHOLD;
	
	SmartDashboard::PutNumber("Yellow Count", yellowCount);
	
	delete CurrentImage;
	delete ThresholdImage;
	
	return LastValue;*/
}
