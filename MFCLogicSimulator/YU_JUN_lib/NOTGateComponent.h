#pragma once
#include "ComponentObject.h"

class CNOTGateComponent :public CComponentObject {
#define NOT_GATE_INPUT_DEFAULT_VALUE false
#define NOT_GATE_OUTPUT_DEFAULT_VALUE true
private:
	bool inputValue;
	bool outputValue;

public:
	CNOTGateComponent();
	CNOTGateComponent(CNOTGateComponent& object);
	virtual ~CNOTGateComponent();
	virtual bool setInputValue(int index,bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual void reset();
};