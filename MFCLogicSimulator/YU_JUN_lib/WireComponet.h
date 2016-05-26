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

	virtual bool setInputValue(bool _value);
	virtual bool getInputValue();
	virtual bool getOutputValue();
	virtual bool update();
};