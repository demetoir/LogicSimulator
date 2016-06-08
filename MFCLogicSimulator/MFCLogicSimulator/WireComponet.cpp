#include "stdafx.h"
#include "WireComponet.h"

CWireComponent::CWireComponent()
{
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

bool CWireComponent::setInputValue(int index,bool _value)
{
	bool oldValue = value;
	value = _value;
	if (oldValue == value) {
		return false;
	}
	return true;
}

bool CWireComponent::getInputValue(int index)
{
	return value;
}

bool CWireComponent::getOutputValue(int index)
{
	return value;
}

bool CWireComponent::update()
{
	return false;
}

int CWireComponent::numberOfInput()
{
	return WIRE_NUMBER_OF_INPUT;
}

int CWireComponent::numberOfOutput()
{
	return WIRE_NUMBER_OF_OUTPUT;
}

void CWireComponent::reset()
{
	value = WIRE_COMPONENT_DEFAULT_VALUE;
}


