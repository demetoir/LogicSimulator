#include "XORGateComponent.h"

XORGateComponent::XORGateComponent()
{
	setComponentName(std::string("XOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(XOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(XOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

XORGateComponent::XORGateComponent(XORGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("XOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(XOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(XOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

XORGateComponent::~XORGateComponent()
{
}

void XORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool XORGateComponent::getInputValue1()
{
	return inputValue1;
}

void XORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool XORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool XORGateComponent::getOutputValue()
{
	return outputValue;
}

void XORGateComponent::updateOutputValue()
{
	outputValue = (inputValue1^ inputValue2);
}
