#pragma once
#include "ComponentObject.h"
#include <vector>

#define NOT_GATE_INPUT_VALUE_SIZE 1
#define NOT_GATE_OUTPUT_VALUE_SIZE 1

class CNOTGateComponent :public CComponentObject {
#define NOT_GATE_INPUT_DEFAULT_VALUE false
#define NOT_GATE_OUTPUT_DEFAULT_VALUE false
private:
	std::vector < bool > inputValue;
	std::vector < bool > outputValue;
public:
	CNOTGateComponent();
	CNOTGateComponent(CNOTGateComponent& object);
	virtual ~CNOTGateComponent();

	//input value 를 변경하면 output value 가 변경되었는지 알려준다
	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue(int index);

	void updateOutputValue();
};