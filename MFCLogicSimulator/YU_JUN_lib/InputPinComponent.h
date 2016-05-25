#pragma once

#include"ComponentObject.h"


class CInputPinComponent :public CComponentObject{
#define INPUT_PIN_DEFAULT_INPUT_VALUE false
private:
	bool value;
public:
	CInputPinComponent();
	CInputPinComponent(CInputPinComponent& object);
	~CInputPinComponent();
	void setValue(bool _value);
	bool getValue();
};