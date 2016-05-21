#include "ClockComponent.h"

CClockComponent::CClockComponent()
{
	setComponentName(std::string("Clock Component"));
	value = false;
	clockHZ = 10;
	setNumberOfInputTerminal(CLOCK_COMPONENT_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(CLOCK_COMPONENT_OUTPUT_TERMINAL_NUMBER);
}

CClockComponent::CClockComponent(CClockComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("Clock Component"));
	value = object.getValue();
	clockHZ = object.getClockHZ();
	setNumberOfInputTerminal(CLOCK_COMPONENT_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(CLOCK_COMPONENT_OUTPUT_TERMINAL_NUMBER);
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
