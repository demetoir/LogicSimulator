#pragma once
#include "ComponentObject.h"
#define XOR_GATE_INPUT_TERMINAL_NUMBER 2
#define XOR_GATE_OUTPUT_TERMINAL_NUMBER 1
class CXORGateComponent :public CComponentObject {
private:
	bool inputValue1;
	bool inputValue2;
	bool outputValue;

public:
	CXORGateComponent();
	CXORGateComponent(CXORGateComponent& object);
	virtual ~CXORGateComponent();

	void setInputValue1(bool _inputValue1);
	bool getInputValue1();
	void setInputValue2(bool _inputValue2);
	bool getInputValue2();
	bool getOutputValue();
	void updateOutputValue();
};