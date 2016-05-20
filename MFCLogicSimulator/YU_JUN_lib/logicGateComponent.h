#pragma once

#include "logicSimulatorComponent.h"
enum LOGIC_GATE_TYPE {LOGIC_GATE_AND,LOGIC_GATE_OR,LOGIC_GATE_XOR,LOGIC_GATE_NOR,LOGIC_GATE_NOT};

class CLogicGateComponent : public CLogicSimulatorComponent {

private:
	LOGIC_GATE_TYPE logicGateType;
public:
	

	CLogicGateComponent(LOGIC_GATE_TYPE newGateType);
	CLogicGateComponent(CLogicGateComponent& obj);
	~CLogicGateComponent();

	LOGIC_GATE_TYPE getLogicGatetype();
	virtual void updateOutputValue();


};