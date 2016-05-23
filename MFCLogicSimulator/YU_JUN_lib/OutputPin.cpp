#include "OutputPin.h"

COutputPinComponent::COutputPinComponent()
{
	value = false;
}

COutputPinComponent::COutputPinComponent(COutputPinComponent & object)
	:CComponentObject(object)
{
	value = false;
}

COutputPinComponent::~COutputPinComponent()
{
}

void COutputPinComponent::setValue(bool _value)
{
	value = _value;
}

bool COutputPinComponent::getValue()
{
	return value;
}
