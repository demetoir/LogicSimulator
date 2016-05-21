#include "OutputPin.h"

COutputPin::COutputPin()
{
	setComponentName(std::string("output pin"));
	value = false;
	setNumberOfInputTerminal(OUTPUT_PIN_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OUTPUT_PIN_OUTPUT_TERMINAL_NUMBER);
}

COutputPin::COutputPin(COutputPin & object)
	:CComponentObject(object)
{
	setComponentName(std::string("output pin"));
	value = false;
	setNumberOfInputTerminal(OUTPUT_PIN_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OUTPUT_PIN_OUTPUT_TERMINAL_NUMBER);
}

COutputPin::~COutputPin()
{
}

void COutputPin::setValue(bool _value)
{
	value = _value;
}

bool COutputPin::getValue()
{
	return value;
}
