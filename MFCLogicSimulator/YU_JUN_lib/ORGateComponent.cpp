#include "ORGateComponent.h"

CORGateComponent::CORGateComponent()
{
	inputValue[0] =  OR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = OR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = OR_GATE_OUTPUT_DEFAULT_VALUE;
}

CORGateComponent::CORGateComponent(CORGateComponent & object)
	:CComponentObject(object)
{
	inputValue[0] = OR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = OR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = OR_GATE_OUTPUT_DEFAULT_VALUE;
}

CORGateComponent::~CORGateComponent()
{
}


bool CORGateComponent::setInputValue(int index, bool _value)
{
	bool oldOutputValue;
	oldOutputValue = outputValue;
	inputValue[index] = _value;
	updateOutputValue();
	if (oldOutputValue == outputValue) {
		return false;
	}
	return true;
}

bool CORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CORGateComponent::getOutputValue()
{
	return outputValue;
}

void CORGateComponent::updateOutputValue()
{
	outputValue = (inputValue[0] | inputValue[1]);
}
