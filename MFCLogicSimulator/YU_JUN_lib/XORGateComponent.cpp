#include "XORGateComponent.h"

CXORGateComponent::CXORGateComponent()
{
	setComponentName(std::string("XOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(XOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(XOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CXORGateComponent::CXORGateComponent(CXORGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("XOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(XOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(XOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CXORGateComponent::~CXORGateComponent()
{
}

void CXORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CXORGateComponent::getInputValue1()
{
	return inputValue1;
}

void CXORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CXORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CXORGateComponent::getOutputValue()
{
	return outputValue;
}

void CXORGateComponent::updateOutputValue()
{
	outputValue = (inputValue1^ inputValue2);
}
