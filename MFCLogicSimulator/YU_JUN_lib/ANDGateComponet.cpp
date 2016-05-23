#include "ANDGateComponet.h"

CANDGateComponent::CANDGateComponent()
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CANDGateComponent::CANDGateComponent(CANDGateComponent & object)
	:CComponentObject(object)
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CANDGateComponent::~CANDGateComponent()
{
}

void CANDGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CANDGateComponent::getInputValue1()
{
	return inputValue1;
}

void CANDGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CANDGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CANDGateComponent::getOutputValue()
{
	return outputValue;
}

void CANDGateComponent::updateOutputValue()
{
	outputValue = (inputValue1 & inputValue2);
}
