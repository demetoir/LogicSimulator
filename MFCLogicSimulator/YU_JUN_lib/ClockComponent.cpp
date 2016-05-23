#include "ClockComponent.h"

CClockComponent::CClockComponent()
{
	value = false;
	clockHZ = 10;
}

CClockComponent::CClockComponent(CClockComponent & object)
	:CComponentObject(object)
{
	value = object.getValue();
	clockHZ = object.getClockHZ();
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
