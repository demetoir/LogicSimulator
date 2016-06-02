#pragma once
#include "ComponentObject.h"
#include <vector>

class CWireComponent:public CComponentObject {
#define WIRE_COMPONENT_DEFAULT_VALUE false
#define WIRE_NUMBER_OF_INPUT 1
#define WIRE_NUMBER_OF_OUTPUT 3
private:
	bool value;

public:
	CWireComponent();
	CWireComponent(CWireComponent& object);
	virtual ~CWireComponent();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual void reset();
};