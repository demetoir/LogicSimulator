#pragma once

#include"ComponentObject.h"
#define INPUT_PIN_INPUT_TEMINAL_NUMBER 1
#define INPUT_PIN_OUTPUT_TEMINAL_NUMBER 1
class CInputPinComponent :public CComponentObject{
private:
	bool value;
public:
	CInputPinComponent();
	CInputPinComponent(CInputPinComponent& object);
	~CInputPinComponent();
	void setValue(bool _value);
	bool getValue();
};