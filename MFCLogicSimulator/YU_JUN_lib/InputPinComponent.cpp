#include "InputPinComponent.h"

CInputPinComponent::CInputPinComponent()
{
	setComponentName(std::string("input pin"));
	value = false;
	setNumberOfInputTerminal(INPUT_PIN_INPUT_TEMINAL_NUMBER);
	setNumberOfOutputTerminal(INPUT_PIN_OUTPUT_TEMINAL_NUMBER);

}

CInputPinComponent::CInputPinComponent(CInputPinComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("input pin"));
	value = false;
	setNumberOfInputTerminal(INPUT_PIN_INPUT_TEMINAL_NUMBER);
	setNumberOfOutputTerminal(INPUT_PIN_OUTPUT_TEMINAL_NUMBER);
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
