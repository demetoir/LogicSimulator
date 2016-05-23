#include "XORGateComponent.h"

CXORGateComponent::CXORGateComponent()
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;

}

CXORGateComponent::CXORGateComponent(CXORGateComponent & object)
	:CComponentObject(object)
{
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;

}

CXORGateComponent::~CXORGateComponent()
{
}

void CXORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CXORGateComponent::getInputValue1()
{
	return inputValue1;
}

void CXORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CXORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CXORGateComponent::getOutputValue()
{
	return outputValue;
}

void CXORGateComponent::updateOutputValue()
{
	outputValue = (inputValue1^ inputValue2);
}
