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

bool CInputPinComponent::setInputValue(bool _value)
{
	bool oldValue = value;
	value = _value;
	if (oldValue == value) {
		return true;
	}
	return false;
}

bool CInputPinComponent::getInputValue()
{
	return value;
}

bool CInputPinComponent::getOutputValue()
{
	return value;
}

bool CInputPinComponent::update()
{
	return false;
}


