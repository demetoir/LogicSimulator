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
		outputValue = (inputValue1&inputValue2);
		break;
	case LOGIC_GATE_OR:
		outputValue = (inputValue1 | inputValue2);
		break;
	case LOGIC_GATE_XOR:
		outputValue = (inputValue1 ^ inputValue2);
		break;
	case LOGIC_GATE_NOR:
		outputValue = !(inputValue1 | inputValue2);
		break;
	case LOGIC_GATE_NOT:
		outputValue = !inputValue1;
		break;
	default:
		break;
	}
}
