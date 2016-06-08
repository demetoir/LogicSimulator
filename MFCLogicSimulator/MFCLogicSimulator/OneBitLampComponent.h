#pragma once
#include "ComponentObject.h"

class COneBitLampComponent :public CComponentObject {
#define ONE_BIT_LAMP_DEFUALT_VALUE false
private:
	bool value;

public:
	COneBitLampComponent();
	COneBitLampComponent(COneBitLampComponent& object);
	~COneBitLampComponent();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual void reset();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};