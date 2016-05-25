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

void COutputPinComponent::setValue(bool _value)
{
	value = _value;
}

bool COutputPinComponent::getValue()
{
	return value;
}
