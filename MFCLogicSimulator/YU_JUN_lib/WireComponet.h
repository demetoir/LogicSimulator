#pragma once
#include "ComponentObject.h"
#include <vector>

class CWireComponent:public CComponentObject {
#define WIRE_COMPONENT_DEFAULT_VALUE false
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
};