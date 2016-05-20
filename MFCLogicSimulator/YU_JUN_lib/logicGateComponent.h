#pragma once

#include "ComponentObject.h"

enum LOGIC_GATE_TYPE {LOGIC_GATE_AND,LOGIC_GATE_OR,LOGIC_GATE_XOR,LOGIC_GATE_NOR,LOGIC_GATE_NOT};

class CLogicGateComponent : public CComponentObject {

private:
	LOGIC_GATE_TYPE logicGateType;
	bool input1;
	bool input2;
	bool output;

public:
	
	CLogicGateComponent(LOGIC_GATE_TYPE GateType);
	CLogicGateComponent(CLogicGateComponent& obj);
	virtual ~CLogicGateComponent();

	LOGIC_GATE_TYPE getLogicGatetype();
	void updateOutputValue();
	void setInputValue1(bool input1);
	bool getInputValue1();
	void setInputValue2(bool input2);
	bool getInputValue2();
	bool getOutputValue();
	LOGIC_GATE_TYPE getLogicGateType();

};