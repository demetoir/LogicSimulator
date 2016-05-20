#pragma once

#include "ComponentObject.h"

enum LOGIC_GATE_TYPE {LOGIC_GATE_AND,LOGIC_GATE_OR,LOGIC_GATE_XOR,LOGIC_GATE_NOR,LOGIC_GATE_NOT};
enum DIRECTION { DIRECTION_NORTH, DIRECTION_SOUTH, DIRECTION_EAST, DIRECTION_WEST };

class CLogicGateComponent : public CComponentObject {

private:
	LOGIC_GATE_TYPE logicGateType;
	

public:
	

	CLogicGateComponent(LOGIC_GATE_TYPE GateType);
	CLogicGateComponent(CLogicGateComponent& obj);
	~CLogicGateComponent();

	LOGIC_GATE_TYPE getLogicGatetype();
	virtual void updateOutputValue();


};