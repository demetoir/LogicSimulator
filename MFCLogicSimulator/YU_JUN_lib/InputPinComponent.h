#pragma once

#include"ComponentObject.h"
#define INPUT_PIN_INPUT_TEMINAL_NUMBER 1
#define INPUT_PIN_OUTPUT_TEMINAL_NUMBER 0
class InputPinComponent :public CComponentObject{
private:
	bool value;
public:
	InputPinComponent();
	InputPinComponent(InputPinComponent& object);
	~InputPinComponent();
	void setValue(bool _value);
	bool getValue();
};