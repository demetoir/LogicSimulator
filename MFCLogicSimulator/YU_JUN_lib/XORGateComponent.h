#pragma once
#include "ComponentObject.h"
#include <vector>

#define XOR_GATE_INPUT_NUMBER 2
#define XOR_GATE_INPUT_DEFAULT_VALUE false

#define XOR_GATE_OUTPUT_NUMBER 2
#define XOR_GATE_OUTPUT_DEFAULT_VALUE false


class CXORGateComponent :public CComponentObject {
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