#pragma once
#include "ComponentObject.h"

class NOTGateComponent : CComponentObject {
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