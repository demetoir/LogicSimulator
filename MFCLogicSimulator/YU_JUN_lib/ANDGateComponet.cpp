#include "ANDGateComponet.h"

CANDGateComponent::CANDGateComponent()
{
	outputValue =  AND_GATE_OUTPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
}

CANDGateComponent::CANDGateComponent(CANDGateComponent & object)
	:CComponentObject(object)
{
	outputValue = AND_GATE_OUTPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
}

CANDGateComponent::~CANDGateComponent()
{
}

//input이 바뀌면 output 값이 바뀌었는지 를 반환해줌
bool CANDGateComponent::setInputValue(int index, bool _value)
{
	bool oldOuputValue;
	oldOuputValue = outputValue;
	inputValue[index] = _value;
	updateOutputValue();
	if (oldOuputValue = outputValue) {
		return false;
	}
	return true;
}

bool CANDGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CANDGateComponent::getOutputValue()
{
	return	outputValue;
}

void CANDGateComponent::updateOutputValue()
{
	outputValue = (inputValue[0] & inputValue[1]);
}
