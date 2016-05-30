#pragma once
#include "ComponentObject.h"

class CXORGateComponent :public CComponentObject {
#define XOR_GATE_INPUT_DEFAULT_VALUE false
#define XOR_GATE_OUTPUT_DEFAULT_VALUE false
private:
	bool inputValue[2];
	bool outputValue;

public:
	CXORGateComponent();
	CXORGateComponent(CXORGateComponent& object);
	virtual ~CXORGateComponent();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual void reset();
};