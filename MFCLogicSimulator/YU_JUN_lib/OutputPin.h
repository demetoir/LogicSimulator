#pragma once

#include "ComponentObject.h"
#include <vector>

#define OUTPUT_PIN_VALUE_NUMBER 1
#define OUTPUT_PIN_DEFAULT_VALUE true 

class COutputPinComponent :public CComponentObject {
private:
	std::vector<bool> value;
public:
	COutputPinComponent();
	COutputPinComponent(COutputPinComponent& object);
	~COutputPinComponent();
	void setValue(bool _value);
	bool getValue(); 
};
