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

void CClockComponent::setValue(bool _value)
{
	value = _value;
}

bool CClockComponent::getValue()
{
	return value;
}

void CClockComponent::setClockHZ(double _clockHZ)
{
	clockHZ = _clockHZ;
}

double CClockComponent::getClockHZ()
{
	return clockHZ;
}
