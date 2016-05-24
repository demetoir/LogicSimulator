#include "ORGateComponent.h"

CORGateComponent::CORGateComponent()
{
	inputValue.resize(OR_GATE_INPUT_VALUE_SIZE + 1, OR_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(OR_GATE_OUTPUT_VALUE_SIZE + 1, OR_GATE_OUTPUT_DEFAULT_VALUE);
}

CORGateComponent::CORGateComponent(CORGateComponent & object)
	:CComponentObject(object)
{
	inputValue.resize(OR_GATE_INPUT_VALUE_SIZE + 1, OR_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(OR_GATE_OUTPUT_VALUE_SIZE + 1, OR_GATE_OUTPUT_DEFAULT_VALUE);
}

CORGateComponent::~CORGateComponent()
{
}


bool CORGateComponent::setInputValue(int index, bool _value)
{
	bool oldOutputValue;
	oldOutputValue = outputValue[1];
	inputValue[index] = _value;
	updateOutputValue();
	if (oldOutputValue == outputValue[1]) {
		return false;
	}
	return true;
}

bool CORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CORGateComponent::getOutputValue(int index)
{
	return outputValue[index];
}

void CORGateComponent::updateOutputValue()
{
	outputValue[1] = (inputValue[1] | inputValue[2]);
}
