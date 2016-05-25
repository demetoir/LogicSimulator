#include "XORGateComponent.h"

CXORGateComponent::CXORGateComponent()
{
	inputValue[0] = XOR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = XOR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = XOR_GATE_OUTPUT_DEFAULT_VALUE;
}

CXORGateComponent::CXORGateComponent(CXORGateComponent & object)
	:CComponentObject(object)
{
	inputValue[0] = XOR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = XOR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = XOR_GATE_OUTPUT_DEFAULT_VALUE;
}

CXORGateComponent::~CXORGateComponent()
{
}

bool CXORGateComponent::setInputValue(int index, bool _value)
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

bool CXORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CXORGateComponent::getOutputValue()
{
	return outputValue;
}

void CXORGateComponent::updateOutputValue()
{
	outputValue = (inputValue[0] ^ inputValue[1]);
}
