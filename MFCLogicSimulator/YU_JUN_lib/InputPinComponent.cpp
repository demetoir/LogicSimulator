#include "InputPinComponent.h"

InputPinComponent::InputPinComponent()
{
	setComponentName(std::string("input pin"));
	value = false;
	setNumberOfInputTerminal(INPUT_PIN_INPUT_TEMINAL_NUMBER);
	setNumberOfOutputTerminal(INPUT_PIN_OUTPUT_TEMINAL_NUMBER);

}

InputPinComponent::InputPinComponent(InputPinComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("input pin"));
	value = false;
	setNumberOfInputTerminal(INPUT_PIN_INPUT_TEMINAL_NUMBER);
	setNumberOfOutputTerminal(INPUT_PIN_OUTPUT_TEMINAL_NUMBER);
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
