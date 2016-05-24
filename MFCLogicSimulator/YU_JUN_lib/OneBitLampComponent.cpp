#include "OneBitLampComponent.h"

COneBitLampComponent::COneBitLampComponent()
{
	value.resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE + 1, ONE_BIT_LAMP_DEFUALT_VALUE);
}

COneBitLampComponent::COneBitLampComponent(COneBitLampComponent & object)
	:CComponentObject(object)
{
	value.resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE + 1, ONE_BIT_LAMP_DEFUALT_VALUE);
}

COneBitLampComponent::~COneBitLampComponent()
{
}

void COneBitLampComponent::setValue(bool _value)
{
	value[1] = _value;
}

bool COneBitLampComponent::getValue()
{
	return value[1];
}
