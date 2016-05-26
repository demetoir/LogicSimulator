#include "WireComponet.h"

CWireComponent::CWireComponent()
{
	CSimulatorObject();
	value = WIRE_COMPONENT_DEFAULT_VALUE;
}

CWireComponent::CWireComponent(CWireComponent&  object)
	:CComponentObject(object)
{
	value = WIRE_COMPONENT_DEFAULT_VALUE;
}

CWireComponent::~CWireComponent()
{
	
}

bool CWireComponent::setInputValue(bool _value)
{
	bool oldValue = value;
	value = _value;
	if (oldValue == value) {
		return false;
	}
	return true;
}

bool CWireComponent::getInputValue()
{
	return value;
}

bool CWireComponent::getOutputValue()
{
	return value;
}

bool CWireComponent::update()
{
	return false;
}


