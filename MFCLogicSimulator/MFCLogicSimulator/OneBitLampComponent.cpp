#include "stdafx.h"
#include "OneBitLampComponent.h"

COneBitLampComponent::COneBitLampComponent()
{
	value = ONE_BIT_LAMP_DEFUALT_VALUE;
}

COneBitLampComponent::COneBitLampComponent(COneBitLampComponent & object)
	:CComponentObject(object)
{
	value = ONE_BIT_LAMP_DEFUALT_VALUE;
}

COneBitLampComponent::~COneBitLampComponent()
{
}

bool COneBitLampComponent::setInputValue(int index, bool _value)
{
	bool oldValue = value;
	value = _value;
	if(oldValue == value){
		return false;
	}
	return true;
}

bool COneBitLampComponent::getInputValue(int index)
{
	return value;
}

bool COneBitLampComponent::getOutputValue(int index)
{
	return value;
}

bool COneBitLampComponent::update()
{
	return false;
}

void COneBitLampComponent::reset()
{
	value = ONE_BIT_LAMP_DEFUALT_VALUE;
}

int COneBitLampComponent::numberOfInput()
{
	return 1;
}

int COneBitLampComponent::numberOfOutput()
{
	return 0;
}


