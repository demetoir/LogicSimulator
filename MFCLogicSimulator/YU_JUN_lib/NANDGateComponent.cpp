#include "NANDGateComponent.h"

CNANDGateComponent::CNANDGateComponent()
{
	setComponentName(std::string("NAND Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CNANDGateComponent::CNANDGateComponent(CNANDGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("NAND Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CNANDGateComponent::~CNANDGateComponent()
{
}

void CNANDGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CNANDGateComponent::getInputValue1()
{
	return inputValue1;
}

void CNANDGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CNANDGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CNANDGateComponent::getOutputValue()
{
	return outputValue;
}

void CNANDGateComponent::updateOutputValue()
{
	outputValue = !(inputValue1 & inputValue2);
}
