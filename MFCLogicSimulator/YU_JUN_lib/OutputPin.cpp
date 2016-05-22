#include "OutputPin.h"

COutputPinComponent::COutputPinComponent()
{
	setComponentName(std::string("output pin"));
	value = false;
	setNumberOfInputTerminal(OUTPUT_PIN_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OUTPUT_PIN_OUTPUT_TERMINAL_NUMBER);
}

COutputPinComponent::COutputPinComponent(COutputPinComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("output pin"));
	value = false;
	setNumberOfInputTerminal(OUTPUT_PIN_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OUTPUT_PIN_OUTPUT_TERMINAL_NUMBER);
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
