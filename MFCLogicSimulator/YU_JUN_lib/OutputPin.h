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

	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};
