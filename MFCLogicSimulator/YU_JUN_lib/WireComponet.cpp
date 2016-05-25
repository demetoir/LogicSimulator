#include "WireComponet.h"

CWireComponent::CWireComponent()
{
	CSimulatorObject();
	value = WIRE_COMPONENT_DEFAULT_VALUE;
}

CWireComponent::CWireComponent(CWireComponent&  object)
	:CSimulatorObject(object)
{
	value = WIRE_COMPONENT_DEFAULT_VALUE;
}

CWireComponent::~CWireComponent()
{
	
}

bool CWireComponent::setValue(bool _value)
{
	return value = _value;
}

bool CWireComponent::getValue()
{
	return value;
}
