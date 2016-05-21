#include "OutputPin.h"

COutputPin::COutputPin()
{
	setComponentName(std::string("output pin"));
	value = false;
}

COutputPin::COutputPin(COutputPin & object)
	:CComponentObject(object)
{
	setComponentName(std::string("output pin"));
	value = false;
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
