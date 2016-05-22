#include "NOTGateComponent.h"

CNOTGateComponent::CNOTGateComponent()
{
	setComponentName(std::string("NOT Gate"));
	inputValue = false;
	outputValue = false;
	setNumberOfInputTerminal(NOT_GATE_INPUT_TERMINLA_NUMBER);
	setNumberOfOutputTerminal(NOT_GATE_OUTPUT_TERMINLA_NUMBER);
}

CNOTGateComponent::CNOTGateComponent(CNOTGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("NOT Gate"));
	inputValue = false;
	outputValue = false;
	setNumberOfInputTerminal(NOT_GATE_INPUT_TERMINLA_NUMBER);
	setNumberOfOutputTerminal(NOT_GATE_OUTPUT_TERMINLA_NUMBER);
}

CNOTGateComponent::~CNOTGateComponent()
{
}

void CNOTGateComponent::setInputValue(bool _inputValue)
{
	inputValue = _inputValue;
}

bool CNOTGateComponent::getInputValue()
{
	return inputValue;
}

bool CNOTGateComponent::getOutputValue()
{
	return outputValue;
}

void CNOTGateComponent::updateOutputValue()
{
	outputValue = !inputValue;
}
