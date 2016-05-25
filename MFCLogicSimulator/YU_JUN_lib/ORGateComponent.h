#pragma once
#include "ComponentObject.h"


class CORGateComponent :public CComponentObject {
#define OR_GATE_OUTPUT_DEFAULT_VALUE false
#define OR_GATE_INPUT_DEFAULT_VALUE false 
private:
	bool inputValue[2];
	bool outputValue;
public:
	CORGateComponent();
	CORGateComponent(CORGateComponent& object);
	virtual ~CORGateComponent();

	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue();
	void updateOutputValue();
};