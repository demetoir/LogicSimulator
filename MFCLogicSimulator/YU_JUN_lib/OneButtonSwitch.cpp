#include "OneButtonSwitch.h"

COnebuttonSwitch::COnebuttonSwitch()
{
	CComponentObject();
	setComponentName(std::string("one button switch"));
	
	value = false;
}

COnebuttonSwitch::COnebuttonSwitch(COnebuttonSwitch & obj)
	:CComponentObject(obj)
{

}

COnebuttonSwitch::~COnebuttonSwitch()
{
	
}

bool COnebuttonSwitch::getValue()
{
	return value;
}

void COnebuttonSwitch::setValue(bool _value)
{
	value = _value;
}
