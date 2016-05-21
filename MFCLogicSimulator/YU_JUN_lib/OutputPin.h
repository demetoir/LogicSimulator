#pragma once

#include "ComponentObject.h"

#define OUTPUT_PIN_INPUT_TERMINAL_NUMBER 1
#define OUTPUT_PIN_OUTPUT_TERMINAL_NUMBER 1
class COutputPin :public CComponentObject {
private:
	bool value;
public:
	COutputPin();
	COutputPin(COutputPin& object);
	~COutputPin();
	void setValue(bool _value);
	bool getValue(); 
};
