#pragma once
#include "ComponentObject.h"
#define NOT_GATE_INPUT_TERMINLA_NUMBER 1
#define NOT_GATE_OUTPUT_TERMINLA_NUMBER 1
class CNOTGateComponent :public CComponentObject {
private:
	bool inputValue;
	bool outputValue;

public:
	CNOTGateComponent();
	CNOTGateComponent(CNOTGateComponent& object);
	virtual ~CNOTGateComponent();

	void setInputValue(bool _inputValue);
	bool getInputValue();

	bool getOutputValue();
	void updateOutputValue();
};