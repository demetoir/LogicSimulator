#include "InputPinComponent.h"

InputPinComponent::InputPinComponent()
{
	setComponentName(std::string("input pin"));
	value = false;
}

InputPinComponent::InputPinComponent(InputPinComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("input pin"));
	value = false;
}

InputPinComponent::~InputPinComponent()
{
}

void InputPinComponent::setValue(bool _value)
{
	value = _value;
}

bool InputPinComponent::getValue()
{
	return value;
}
