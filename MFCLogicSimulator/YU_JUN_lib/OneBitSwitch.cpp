#include "OneBitSwitch.h"

COneBitSwitchComponent::COneBitSwitchComponent()
{
	value.resize(ONE_BIT_SWITCH_VALUE_SIZE+1);

	inputTerminalInfo.resize(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER+1);
	outputTerminalInfo.resize(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER+1);

	value[1] = ONE_BIT_SWITCH_DEFAULT_VALUE;
}

COneBitSwitchComponent::COneBitSwitchComponent(COneBitSwitchComponent & obj)
	:CComponentObject(obj)
{
	value.resize(ONE_BIT_SWITCH_VALUE_SIZE + 1);

	inputTerminalInfo.resize(ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER + 1);
	outputTerminalInfo.resize(ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER + 1);
	value[1] = obj.getValue();
}

COneBitSwitchComponent::~COneBitSwitchComponent()
{
	
}

bool COneBitSwitchComponent::getValue()
{
	return value[1];
}

void COneBitSwitchComponent::setValue(bool _value)
{
	value[1] = _value;
}


