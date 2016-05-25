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

void CInputPinComponent::setValue(bool _value)
{
	value = _value;
}

bool CInputPinComponent::getValue()
{
	return value;
}

