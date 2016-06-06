#pragma once
#include "ComponentObject.h"

class CANDGateComponent :public CComponentObject{
#define AND_GATE_OUTPUT_DEFUALT_VALUE false
#define AND_GATE_INPUT_DEFUALT_VALUE false
private:
	bool inputValue[2];
	bool outputValue;

public:
	CANDGateComponent();
	CANDGateComponent(CANDGateComponent& object);
	virtual ~CANDGateComponent();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual void reset();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};