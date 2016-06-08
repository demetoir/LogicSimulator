#include "stdafx.h"
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
	inputValue[index] = _value;
	return update();
}

bool CXORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CXORGateComponent::getOutputValue(int index)
{
	return outputValue ;
}

bool CXORGateComponent::update()
{
	bool oldValue = outputValue;
	outputValue = (inputValue[0] ^ inputValue[1]);
	if (oldValue == outputValue) {
		return false;
	}
	return true;
}

int CXORGateComponent::numberOfInput()
{
	return 2;
}

int CXORGateComponent::numberOfOutput()
{
	return 1;
}

void CXORGateComponent::reset()
{
	inputValue[0] = XOR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = XOR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = XOR_GATE_OUTPUT_DEFAULT_VALUE;
}


