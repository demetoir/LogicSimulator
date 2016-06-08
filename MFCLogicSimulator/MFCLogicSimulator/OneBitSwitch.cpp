#include "stdafx.h"
#include "OneBitSwitch.h"

COneBitSwitchComponent::COneBitSwitchComponent()
{
	value = ONE_BIT_SWITCH_DEFAULT_VALUE;
}

COneBitSwitchComponent::COneBitSwitchComponent(COneBitSwitchComponent & obj)
	:CComponentObject(obj)
{
	value = ONE_BIT_SWITCH_DEFAULT_VALUE;
}

COneBitSwitchComponent::~COneBitSwitchComponent()
{
	
}

bool COneBitSwitchComponent::setInputValue(int index, bool _value)
{
	if (value == _value) {
		return false;
	}
	value = _value;
	return  true;
}

bool COneBitSwitchComponent::getInputValue(int index)
{
	return value;
}

bool COneBitSwitchComponent::getOutputValue(int index)
{
	return value;
}

bool COneBitSwitchComponent::update()
{
	return false;
}

void COneBitSwitchComponent::reset()
{
	value = ONE_BIT_SWITCH_DEFAULT_VALUE;
}

int COneBitSwitchComponent::numberOfInput()
{
	return 0;
}

int COneBitSwitchComponent::numberOfOutput()
{
	return 1;
}


