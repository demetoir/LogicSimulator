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
		setOutputValue((getInputvalue1()&getInputValue2()));
		break;
	case LOGIC_GATE_OR:
		setOutputValue( (getInputvalue1() | getInputValue2()));
		break;
	case LOGIC_GATE_XOR:
		setOutputValue((getInputvalue1() ^ getInputValue2()));
		break;
	case LOGIC_GATE_NOR:
		setOutputValue(!(getInputvalue1() | getInputValue2()));
		break;
	case LOGIC_GATE_NOT:
		setOutputValue((!getInputvalue1()));
		break;
	default:
		break;
	}
}
