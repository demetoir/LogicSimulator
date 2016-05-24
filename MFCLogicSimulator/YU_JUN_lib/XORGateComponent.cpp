#include "XORGateComponent.h"

CXORGateComponent::CXORGateComponent()
{
	inputValue.resize(XOR_GATE_INPUT_VALUE_SIZE + 1, XOR_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(XOR_GATE_OUTPUT_VALUE_SIZE + 1, XOR_GATE_OUTPUT_DEFAULT_VALUE);
}

CXORGateComponent::CXORGateComponent(CXORGateComponent & object)
	:CComponentObject(object)
{
	inputValue.resize(XOR_GATE_INPUT_VALUE_SIZE + 1, XOR_GATE_INPUT_DEFAULT_VALUE);
	outputValue.resize(XOR_GATE_OUTPUT_VALUE_SIZE + 1, XOR_GATE_OUTPUT_DEFAULT_VALUE);
}

CXORGateComponent::~CXORGateComponent()
{
}

bool CXORGateComponent::setInputValue(int index, bool _value)
{
	bool oldOutputValue;
	oldOutputValue = outputValue[index];
	inputValue[index] = _value;
	updateOutputValue();
	if (oldOutputValue == outputValue[index]) {
		return false;
	}
	return true;
}

bool CXORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CXORGateComponent::getOutputValue(int index)
{
	return outputValue[index];
}

void CXORGateComponent::updateOutputValue()
{
	outputValue[1] = (inputValue[1] ^ inputValue[2]);
}
