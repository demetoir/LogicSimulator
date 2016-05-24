#include "OutputPin.h"

COutputPinComponent::COutputPinComponent()
{
	value.resize(OUTPUT_PIN_VALUE_NUMBER + 1, OUTPUT_PIN_DEFAULT_VALUE);
}

COutputPinComponent::COutputPinComponent(COutputPinComponent & object)
	:CComponentObject(object)
{
	value.resize(OUTPUT_PIN_VALUE_NUMBER + 1, OUTPUT_PIN_DEFAULT_VALUE);
}

COutputPinComponent::~COutputPinComponent()
{
}

void COutputPinComponent::setValue(bool _value)
{
	value[1] = _value;
}

bool COutputPinComponent::getValue()
{
	return value[1];
}
