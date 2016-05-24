#pragma once

#include"ComponentObject.h"
#include "vector"

#define INPUT_PIN_INPUT_TEMINAL_NUMBER 0
#define INPUT_PIN_OUTPUT_TEMINAL_NUMBER 1

#define CLOCK_COMPONENT_VALUE_NUMBER 1

#define CLOCK_COMPONENT_DEFAULT_VALUE false

class CInputPinComponent :public CComponentObject{
private:
	std::vector<int>inputTerminalInfo;
	std::vector<int>outputTerminalInfo;
	std::vector<bool>value;
public:
	CInputPinComponent();
	CInputPinComponent(CInputPinComponent& object);
	~CInputPinComponent();
	void setValue(int index, bool new_value);
	bool getValue(int index);
};