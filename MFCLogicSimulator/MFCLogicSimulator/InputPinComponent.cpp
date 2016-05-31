#include "stdafx.h"
#include "InputPinComponent.h"

CInputPinComponent::CInputPinComponent()
{
	value = INPUT_PIN_DEFAULT_INPUT_VALUE;
}

CInputPinComponent::CInputPinComponent(CInputPinComponent & object)
	:CComponentObject(object)
{
	value = INPUT_PIN_DEFAULT_INPUT_VALUE;
}

CInputPinComponent::~CInputPinComponent()
{
}

bool CInputPinComponent::setInputValue(int index, bool _value)
{
	bool oldValue = value;
	value = _value;
	if (oldValue == value) {
		return true;
	}
	return false;
}

bool CInputPinComponent::getInputValue(int index)
{
	return value;
}

bool CInputPinComponent::getOutputValue(int index)
{
	return value;
}

bool CInputPinComponent::update()
{
	return false;
}

void CInputPinComponent::reset()
{
	value = INPUT_PIN_DEFAULT_INPUT_VALUE;
}

int CInputPinComponent::numberOfInput()
{
	return 0;
}

int CInputPinComponent::numberOfOutput()
{
	return 1;
}


