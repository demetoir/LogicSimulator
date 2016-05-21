#include "OneBitLampComponent.h"

COneBitLampComponent::COneBitLampComponent()
{
	setComponentName(std::string("one bit lamp component"));
	lampState = LAMP_OFF;
}

COneBitLampComponent::COneBitLampComponent(COneBitLampComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("one bit lamp component"));
	lampState = LAMP_OFF;
}

COneBitLampComponent::~COneBitLampComponent()
{
}

void COneBitLampComponent::setLampState(ONE_BIT_LAMP_STATE _lampState)
{
	lampState = _lampState;
}

void COneBitLampComponent::setLampState(bool _lampstate)
{
	lampState = (ONE_BIT_LAMP_STATE)_lampstate;
}

void COneBitLampComponent::setLampON()
{
	lampState = LAMP_ON;
}

void COneBitLampComponent::setLampOFF()
{
	lampState = LAMP_OFF;
}

ONE_BIT_LAMP_STATE COneBitLampComponent::getLampState()
{
	return lampState;
}
