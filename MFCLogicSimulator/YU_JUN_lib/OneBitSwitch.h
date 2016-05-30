#pragma once
#include "ComponentObject.h"
#define ONE_BIT_SWITCH_VALUE_SIZE 1

class COneBitSwitchComponent :public CComponentObject {
#define ONE_BIT_SWITCH_DEFAULT_VALUE false
private:
	bool value;

public:
	COneBitSwitchComponent();
	COneBitSwitchComponent(COneBitSwitchComponent& obj);
	virtual ~COneBitSwitchComponent();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual void reset();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};