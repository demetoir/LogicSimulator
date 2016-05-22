#include "OneBitSwitch.h"

COneBitSwitchComponent::COneBitSwitchComponent()
{
	CComponentObject();
	setComponentName(std::string("one button switch"));
	value = false;
	setNumberOfInputTerminal(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER);
}

COneBitSwitchComponent::COneBitSwitchComponent(COneBitSwitchComponent & obj)
	:CComponentObject(obj)
{
	setComponentName(std::string("one button switch"));
	value = false;
	setNumberOfInputTerminal(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER);
}

COneBitSwitchComponent::~COneBitSwitchComponent()
{
	
}

bool COneBitSwitchComponent::getValue()
{
	return value;
}

void COneBitSwitchComponent::setValue(bool _value)
{
	value = _value;
}
