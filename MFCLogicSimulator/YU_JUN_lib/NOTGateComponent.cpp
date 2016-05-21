#include "NOTGateComponent.h"

NOTGateComponent::NOTGateComponent()
{
	setComponentName(std::string("NOT Gate"));
	inputValue = false;
	outputValue = false;
}

NOTGateComponent::NOTGateComponent(NOTGateComponent & object)
	:CComponentObject(object)
{
	inputValue = false;
	outputValue = false;
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
