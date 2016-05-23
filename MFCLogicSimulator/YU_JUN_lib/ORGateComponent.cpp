#include "ORGateComponent.h"

CORGateComponent::CORGateComponent()
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CORGateComponent::CORGateComponent(CORGateComponent & object)
	:CComponentObject(object)
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CORGateComponent::~CORGateComponent()
{
}

void CORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CORGateComponent::getInputValue1()
{
	return inputValue1;
}

void CORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CORGateComponent::getOutputValue()
{
	return outputValue;
}

void CORGateComponent::updateOutputValue()
{
	outputValue = (inputValue1 | inputValue2);
}
