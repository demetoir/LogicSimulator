#include "NORGateComponent.h"

CNORGateComponent::CNORGateComponent()
{
	setComponentName(std::string("NOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(NOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(NOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CNORGateComponent::CNORGateComponent(CNORGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("NOR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(NOR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(NOR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CNORGateComponent::~CNORGateComponent()
{
}

void CNORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CNORGateComponent::getInputValue1()
{
	return inputValue1;
}

void CNORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CNORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CNORGateComponent::getOutputValue()
{
	return outputValue;
}

void CNORGateComponent::updateOutputValue()
{
	outputValue = !(inputValue1 | inputValue2);
}
