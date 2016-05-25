#pragma once
#include "ComponentObject.h"
#include <vector>

#define XOR_GATE_INPUT_VALUE_SIZE 2
#define XOR_GATE_OUTPUT_VALUE_SIZE 2

class CXORGateComponent :public CComponentObject {
#define XOR_GATE_INPUT_DEFAULT_VALUE false
#define XOR_GATE_OUTPUT_DEFAULT_VALUE false
private:
	std::vector< bool > inputValue;
	std::vector< bool > outputValue;

public:
	CXORGateComponent();
	CXORGateComponent(CXORGateComponent& object);
	virtual ~CXORGateComponent();

	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue(int index);

	void updateOutputValue();
};