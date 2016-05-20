#include "logicGateComponent.h"

CLogicGateComponent::CLogicGateComponent(LOGIC_GATE_TYPE _gateType)
{
	CComponentObject();
	logicGateType = _gateType;
	switch (_gateType)
	{	
	case LOGIC_GATE_AND:
		setComponentName(std::string("AND GATE"));
		break;
	case LOGIC_GATE_OR:
		setComponentName(std::string("OR GATE"));
		break;
	case LOGIC_GATE_XOR:
		setComponentName(std::string("XOR GATE"));
		break;
	case LOGIC_GATE_NOR:
		setComponentName(std::string("NOR GATE"));
		break;
	case LOGIC_GATE_NOT:
		setComponentName(std::string("NOT GATE"));
		break;
	}

}

CLogicGateComponent::CLogicGateComponent(CLogicGateComponent & obj)
	:CComponentObject(obj)
{
	logicGateType = obj.getLogicGatetype();
}

CLogicGateComponent::~CLogicGateComponent()
{
}

LOGIC_GATE_TYPE CLogicGateComponent::getLogicGatetype()
{
	return logicGateType;
}

void CLogicGateComponent::updateOutputValue()
{
	switch (logicGateType)
	{
	case LOGIC_GATE_AND:
		output = (input1&input2);
		break;
	case LOGIC_GATE_OR:
		output = (input1|input2);
		break;
	case LOGIC_GATE_XOR:
		output = (input1^input2 );
		break;
	case LOGIC_GATE_NOR:
		output = !(input1|input2);
		break;
	case LOGIC_GATE_NOT:
		output = !input1;
		break;
	default:
		break;
	}
}

void CLogicGateComponent::setInputValue1(bool _input1)
{
	input1 = _input1;
}

bool CLogicGateComponent::getInputValue1()
{
	return input1;
}

void CLogicGateComponent::setInputValue2(bool _input2)
{
	input2 = _input2;
}

bool CLogicGateComponent::getInputValue2()
{
	return input2;
}

bool CLogicGateComponent::getOutputValue()
{
	return output;
}

LOGIC_GATE_TYPE CLogicGateComponent::getLogicGateType()
{
	return LOGIC_GATE_TYPE();
}
