#pragma once

#include "ComponentObject.h"
#include <vector>

#define OR_GATE_INPUT_VALUE_SIZE 2 
#define OR_GATE_INPUT_DEFAULT_VALUE false 
#define OR_GATE_OUTPUT_VALUE_SIZE 2 
#define OR_GATE_OUTPUT_DEFAULT_VALUE false

class CORGateComponent :public CComponentObject {
private:
	std::vector< bool > inputValue;
	std::vector< bool > outputValue;
public:
	CORGateComponent();
	CORGateComponent(CORGateComponent& object);
	virtual ~CORGateComponent();

	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);

	bool getOutputValue(int index);
	void updateOutputValue();
};