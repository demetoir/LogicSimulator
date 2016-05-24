#include "NOTGateComponent.h"

CNOTGateComponent::CNOTGateComponent()
{
	inputValue.resize(NOT_GATE_INPUT_VALUE_SIZE + 1, NOT_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(NOT_GATE_OUTPUT_VALUE_SIZE + 1, NOT_GATE_OUTPUT_DEFAULT_VALUE);
}

CNOTGateComponent::CNOTGateComponent(CNOTGateComponent & object)
	:CComponentObject(object)
{
	inputValue.resize(NOT_GATE_INPUT_VALUE_SIZE + 1, NOT_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(NOT_GATE_OUTPUT_VALUE_SIZE + 1, NOT_GATE_OUTPUT_DEFAULT_VALUE);
}

CNOTGateComponent::~CNOTGateComponent()
{
}

//input value 를 변경하면 output value 가 변경되었는지 알려준다
bool CNOTGateComponent::setInputValue(int index, bool _value)
{
	bool oldOutputValue;
	oldOutputValue = outputValue[1];
	updateOutputValue();
	if (oldOutputValue == outputValue[1]) {
		return false;
	}
	return true;
}

bool CNOTGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CNOTGateComponent::getOutputValue(int index)
{
	return outputValue[index];
}

void CNOTGateComponent::updateOutputValue()
{
	outputValue[1] = !inputValue[1];
}
