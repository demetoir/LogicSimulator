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

	virtual bool setInputValue(bool _value);
	virtual bool getInputValue();
	virtual bool getOutputValue();
	virtual bool update();
};
