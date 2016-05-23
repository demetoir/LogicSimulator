#include "OneBitSwitch.h"

COneBitSwitchComponent::COneBitSwitchComponent()
{
	CComponentObject();
	value = false;
}

COneBitSwitchComponent::COneBitSwitchComponent(COneBitSwitchComponent & obj)
	:CComponentObject(obj)
{
	value = false;
}

COneBitSwitchComponent::~COneBitSwitchComponent()
{
	
}

bool COneBitSwitchComponent::getValue()
{
	return value;
}

void COneBitSwitchComponent::setValue(bool _value)
{
	value = _value;
}
