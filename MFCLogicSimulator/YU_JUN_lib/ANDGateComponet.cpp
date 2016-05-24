#include "ANDGateComponet.h"

CANDGateComponent::CANDGateComponent()
{
	outputValue.resize(AND_GATE_OUTPUT_VALUE_SIZE + 1, AND_GATE_OUTPUT_DEFUALT_VALUE);
	inputValue.resize(AND_GATE_INPUT_VALUE_SIZE + 1, AND_GATE_INPUT_DEFUALT_VALUE);
}

CANDGateComponent::CANDGateComponent(CANDGateComponent & object)
	:CComponentObject(object)
{
	outputValue.resize(AND_GATE_OUTPUT_VALUE_SIZE + 1, AND_GATE_OUTPUT_DEFUALT_VALUE);
	inputValue.resize(AND_GATE_INPUT_VALUE_SIZE + 1, AND_GATE_INPUT_DEFUALT_VALUE);
}

CANDGateComponent::~CANDGateComponent()
{
}

//input이 바뀌면 output 값이 바뀌었는지 를 반환해줌
bool CANDGateComponent::setInputValue(int index, bool _value)
{
	bool oldOuputValue;
	oldOuputValue = outputValue[1];
	inputValue[index] = _value;
	updateOutputValue();
	if (oldOuputValue = outputValue[1]) {
		return false;
	}
	return true;
}

bool CANDGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CANDGateComponent::getOutputValue(int index)
{
	return	outputValue[index];
}

void CANDGateComponent::updateOutputValue()
{
	outputValue[1] = (inputValue[1] & inputValue[2]);
}
