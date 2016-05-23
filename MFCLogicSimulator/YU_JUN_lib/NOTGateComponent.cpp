#include "NOTGateComponent.h"

CNOTGateComponent::CNOTGateComponent()
{
	inputValue = false;
	outputValue = false;
}

CNOTGateComponent::CNOTGateComponent(CNOTGateComponent & object)
	:CComponentObject(object)
{
	inputValue = false;
	outputValue = false;
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
