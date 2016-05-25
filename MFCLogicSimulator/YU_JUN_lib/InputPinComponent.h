#pragma once

#include"ComponentObject.h"
#include "vector"


#define INPUT_PIN_OUTPUT_VALUE_SIZE 1

class CInputPinComponent :public CComponentObject{
#define INPUT_PIN_DEFAULT_INPUT_VALUE false
private:
	std::vector<bool>value;
public:
	CInputPinComponent();
	CInputPinComponent(CInputPinComponent& object);
	~CInputPinComponent();
	void setValue(int index, bool new_value);
	bool getValue(int index);
};