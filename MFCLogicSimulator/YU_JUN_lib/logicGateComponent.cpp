#include "logicGateComponent.h"

CLogicGateComponent::CLogicGateComponent(LOGIC_GATE_TYPE _gateType)
{
	CLogicSimulatorComponent();
	logicGateType = _gateType;
	switch (_gateType)
	{	
	case LOGIC_GATE_AND:
		componetName = std::string("AND GATE");
		break;
	case LOGIC_GATE_OR:
		componetName = std::string("OR GATE");
		break;
	case LOGIC_GATE_XOR:
		componetName = std::string("XOR GATE");
		break;
	case LOGIC_GATE_NOR:
		componetName = std::string("NOR GATE");
		break;
	case LOGIC_GATE_NOT:
		componetName = std::string("NOT GATE");
		break;
	}

}

CLogicGateComponent::CLogicGateComponent(CLogicGateComponent & obj):
	CLogicSimulatorComponent(obj)
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

LOGIC_GATE_TYPE CLogicGateComponent::getLogicGateType()
{
	return LOGIC_GATE_TYPE();
}
