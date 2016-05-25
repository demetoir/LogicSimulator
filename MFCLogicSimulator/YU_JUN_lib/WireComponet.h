#pragma once
#include "ComponentObject.h"
#include <vector>

class CWireComponent:public CSimulatorObject {
#define WIRE_COMPONENT_DEFAULT_VALUE false
private:
	bool value;
public:
	CWireComponent();
	CWireComponent(CWireComponent& object);
	virtual ~CWireComponent();

	bool setValue(bool _value);
	bool getValue();
};