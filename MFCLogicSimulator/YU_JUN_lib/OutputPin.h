#pragma once

#include "ComponentObject.h"

class COutputPinComponent :public CComponentObject {
#define OUTPUT_PIN_DEFAULT_VALUE true 
private:
	bool value;
public:
	COutputPinComponent();
	COutputPinComponent(COutputPinComponent& object);
	~COutputPinComponent();
	void setValue(bool _value);
	bool getValue(); 
};
