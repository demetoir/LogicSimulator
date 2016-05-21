#include "NOTGateComponent.h"

NOTGateComponent::NOTGateComponent()
{
	setComponentName(std::string("NOT Gate"));
	inputValue = false;
	outputValue = false;
	setNumberOfInputTerminal(NOT_GATE_INPUT_TERMINLA_NUMBER);
	setNumberOfOutputTerminal(NOT_GATE_OUTPUT_TERMINLA_NUMBER);
}

NOTGateComponent::NOTGateComponent(NOTGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("NOT Gate"));
	inputValue = false;
	outputValue = false;
	setNumberOfInputTerminal(NOT_GATE_INPUT_TERMINLA_NUMBER);
	setNumberOfOutputTerminal(NOT_GATE_OUTPUT_TERMINLA_NUMBER);
}

NOTGateComponent::~NOTGateComponent()
{
}

void NOTGateComponent::setInputValue(bool _inputValue)
{
	inputValue = _inputValue;
}

bool NOTGateComponent::getInputValue()
{
	return inputValue;
}

bool NOTGateComponent::getOutputValue()
{
	return outputValue;
}

void NOTGateComponent::updateOutputValue()
{
	outputValue = !inputValue;
}
