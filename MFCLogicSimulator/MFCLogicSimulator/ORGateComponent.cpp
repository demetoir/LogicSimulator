#include "stdafx.h"
#include "ORGateComponent.h"

CORGateComponent::CORGateComponent()
{
	inputValue[0] =  OR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = OR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = OR_GATE_OUTPUT_DEFAULT_VALUE;
}

CORGateComponent::CORGateComponent(CORGateComponent & object)
	:CComponentObject(object)
{
	inputValue[0] = OR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = OR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = OR_GATE_OUTPUT_DEFAULT_VALUE;
}

CORGateComponent::~CORGateComponent()
{
}


bool CORGateComponent::setInputValue(int index, bool _value)
{
	inputValue[index] = _value;
	return update();
}

bool CORGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CORGateComponent::getOutputValue(int index)
{
	return outputValue;
}

bool CORGateComponent::update()
{
	bool oldValue = outputValue;
	outputValue = (inputValue[0] | inputValue[1]);
	if (oldValue == outputValue) {
		return false;
	}
	return true;
}

void CORGateComponent::reset()
{
	inputValue[0] = OR_GATE_INPUT_DEFAULT_VALUE;
	inputValue[1] = OR_GATE_INPUT_DEFAULT_VALUE;
	outputValue = OR_GATE_OUTPUT_DEFAULT_VALUE;
}

int CORGateComponent::numberOfInput()
{
	return 2;
}

int CORGateComponent::numberOfOutput()
{
	return 1;
}

