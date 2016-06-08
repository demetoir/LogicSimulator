#include "stdafx.h"
#include "ClockComponent.h"

CClockComponent::CClockComponent()
{
	value = CLOCK_COMPONENT_DEFAULT_VALUE;
	clockHZ = CLOCK_COMPONENT_DEFAULT_CLOCK_HZ;
}

CClockComponent::CClockComponent(CClockComponent & object)
	:CComponentObject(object)
{
	value = CLOCK_COMPONENT_DEFAULT_VALUE;
	clockHZ = CLOCK_COMPONENT_DEFAULT_CLOCK_HZ;
}

CClockComponent::~CClockComponent()
{
}

bool CClockComponent::setInputValue(int index, bool _value)
{
	if (value == _value) {
		return false;
	}
	value = _value;
	return true;
}

bool CClockComponent::getInputValue(int index)
{
	return value;
}

bool CClockComponent::getOutputValue(int index)
{
	return value;
}

bool CClockComponent::update()
{
	return false;
}

void CClockComponent::reset()
{
	value = CLOCK_COMPONENT_DEFAULT_VALUE;
}


void CClockComponent::setClockHZ(double _clockHZ)
{
	clockHZ = _clockHZ;
}

double CClockComponent::getClockHZ()
{
	return clockHZ;
}

int CClockComponent::numberOfInput()
{
	return 0;
}

int CClockComponent::numberOfOutput()
{
	return 1;
}
