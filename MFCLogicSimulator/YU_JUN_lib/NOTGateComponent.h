#pragma once
#include "ComponentObject.h"
#define NOT_GATE_INPUT_TERMINLA_NUMBER 1
#define NOT_GATE_OUTPUT_TERMINLA_NUMBER 1
class NOTGateComponent :public CComponentObject {
private:
	bool inputValue;
	bool outputValue;

public:
	NOTGateComponent();
	NOTGateComponent(NOTGateComponent& object);
	virtual ~NOTGateComponent();

	void setInputValue(bool _inputValue);
	bool getInputValue();

	bool getOutputValue();
	void updateOutputValue();
};