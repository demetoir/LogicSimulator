#include "logicGateComponent.h"

CLogicGateComponent::CLogicGateComponent(LOGIC_GATE_TYPE newGateType)
{
	CLogicSimulatorComponent();
	logicGateType = newGateType;
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
