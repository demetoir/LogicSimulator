#pragma once

#include"ComponentObject.h"
#include "vector"


#define INPUT_PIN_OUTPUT_VALUE_SIZE 1

#define INPUT_PIN_DEFAULT_INPUT_VALUE false

class CInputPinComponent :public CComponentObject{
private:
	std::vector<bool>value;
public:
	CInputPinComponent();
	CInputPinComponent(CInputPinComponent& object);
	~CInputPinComponent();
	void setValue(int index, bool new_value);
	bool getValue(int index);
};