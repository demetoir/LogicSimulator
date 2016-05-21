#pragma once
#include "ComponentObject.h"
#define NOR_GATE_INPUT_TERMINAL_NUMBER 2
#define NOR_GATE_OUTPUT_TERMINAL_NUMBER 0

class CNORGateComponent :public CComponentObject {
private:
	bool inputValue1;
	bool inputValue2;
	bool outputValue;

public:
	CNORGateComponent();
	CNORGateComponent(CNORGateComponent& object);
	virtual ~CNORGateComponent();

	void setInputValue1(bool _inputValue1);
	bool getInputValue1();
	void setInputValue2(bool _inputValue2);
	bool getInputValue2();
	bool getOutputValue();
	void updateOutputValue();
};