#include "stdafx.h"
#include "OutputPin.h"

COutputPinComponent::COutputPinComponent()
{
	value = OUTPUT_PIN_DEFAULT_VALUE;
}

COutputPinComponent::COutputPinComponent(COutputPinComponent & object)
	:CComponentObject(object)
{
	value = OUTPUT_PIN_DEFAULT_VALUE;
}

COutputPinComponent::~COutputPinComponent()
{
}

bool COutputPinComponent::setInputValue(int index, bool _value)
{
	bool oldValue = value;
	value = _value;
	if (oldValue == value) {
		return false;
	}
	return true;
}

bool COutputPinComponent::getInputValue(int index)
{
	return value;
}

bool COutputPinComponent::getOutputValue(int index)
{
	return value;
}

bool COutputPinComponent::update()
{
	return false;
}

int COutputPinComponent::numberOfInput()
{
	return OUTPUT_PIN_NUMBER_OF_INPUT;
}

int COutputPinComponent::numberOfOutput()
{
	return OUTPUT_PIN_NUMBER_OF_OUTUPUT;
}

void COutputPinComponent::reset()
{
	value = OUTPUT_PIN_DEFAULT_VALUE;
}
