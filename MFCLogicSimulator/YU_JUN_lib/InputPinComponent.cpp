#include "InputPinComponent.h"

CInputPinComponent::CInputPinComponent()
{
	value = false;
}

CInputPinComponent::CInputPinComponent(CInputPinComponent & object)
	:CComponentObject(object)
{
	value = false;
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
