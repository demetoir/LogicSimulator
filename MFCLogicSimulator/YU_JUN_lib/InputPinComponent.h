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
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual void reset();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};