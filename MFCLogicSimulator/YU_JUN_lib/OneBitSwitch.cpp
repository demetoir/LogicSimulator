#include "OneBitSwitch.h"

COneBitSwitch::COneBitSwitch()
{
	CComponentObject();
	setComponentName(std::string("one button switch"));
	value = false;
	setNumberOfInputTerminal(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER);
}

COneBitSwitch::COneBitSwitch(COneBitSwitch & obj)
	:CComponentObject(obj)
{
	setComponentName(std::string("one button switch"));
	value = false;
	setNumberOfInputTerminal(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER);
}

COneBitSwitch::~COneBitSwitch()
{
	
}

bool COneBitSwitch::getValue()
{
	return value;
}

void COneBitSwitch::setValue(bool _value)
{
	value = _value;
}
