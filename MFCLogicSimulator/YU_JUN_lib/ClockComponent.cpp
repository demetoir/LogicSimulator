#include "ClockComponent.h"

CClockComponent::CClockComponent()
{
	value.resize(CLOCK_COMPONENT_VALUE_NUMBER+1);
	value[1] = CLOCK_COMPONENT_DEFAULT_VALUE;
	clockHZ = CLOCK_COMPONENT_DEFAULT_CLOCK_HZ;
	outputTerminalInfo.resize(CLOCK_COMPONENT_INPUT_TERMINAL_NUMBER + 1);
}

CClockComponent::CClockComponent(CClockComponent & object)
	:CComponentObject(object)
{
	value[1] = object.getValue(1);
	clockHZ = object.getClockHZ();
	outputTerminalInfo.resize(CLOCK_COMPONENT_INPUT_TERMINAL_NUMBER + 1);
}

CClockComponent::~CClockComponent()
{
}

void CClockComponent::setValue(int valueIndex, bool _value)
{
	value[valueIndex] = _value;
}

bool CClockComponent::getValue(int valueIndex)
{
	return value[valueIndex];
}

void CClockComponent::setClockHZ(double _clockHZ)
{
	clockHZ = _clockHZ;
}

double CClockComponent::getClockHZ()
{
	return clockHZ;
}
