#include "PIDControl.h"

void PosPID::adjustPGain(float newPGain)
{
	pGain = newPGain;
}

void PosPID::adjustIGain(float newIGain)
{
	iGain = newIGain;
}

void PosPID::adjustDGain(float newDGain)
{
	dGain = newDGain;
}

float PosPID::getPGain(void)
{
	return pGain;
}

float PosPID::getIGain(void)
{
	return iGain;
}

float PosPID::getDGain(void)
{
	return dGain;
}

float PosPID::Update(float distanceToTarget)
{
	//I am Chris Burger, and I approve this message.
	//^Burger approved!
	
	errorToTarget = distanceToTarget;

	float output, P, I, D;

	//Accumulate total error
	totalError += errorToTarget;
	
	//Cap the error
	if(totalError > maxError)
		totalError = maxError;
	else if(totalError < -maxError)
		totalError = -maxError;

	//Calculate P
	P = pGain * errorToTarget;
	//Calculate I
	I = iGain * totalError;
	//Calculate D
	D = dGain * (errorToTarget - previousError);

	output = P + I - D;

	previousError = errorToTarget;

	//Limit output
	if(output > maxOut)
		output = maxOut;
	else if (output < -maxOut)
		output = -maxOut;
	
	if(!invert)
		return output;
	else
		return -output;

}

float PosPID::Update(float currentLocation, float target)
{
	//I am Chris Burger, and I approve this message.
	//^Burger approved!

	float output, P, I, D;

	//Set target error
	errorToTarget = target - currentLocation;

	//Accumulate total error
	totalError += errorToTarget;
	
	//Cap the error
	if(totalError > maxError)
		totalError = maxError;
	else if(totalError < -maxError)
		totalError = -maxError;

	//Calculate P
	P = pGain * errorToTarget;
	//Calculate I
	I = iGain * totalError;
	//Calculate D
	D = dGain * (errorToTarget - previousError);

	output = P + I - D;

	previousError = errorToTarget;

	//Limit output
	if(output > maxOut)
		output = maxOut;
	else if (output < -maxOut)
		output = -maxOut;
	
	if(!invert)
		return output;
	else
		return -output;

}
