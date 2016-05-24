#pragma once
#include "SimulatorObject.h"
#include <string>

class CComponentObject : public CSimulatorObject {
private:
public:
	CComponentObject();
	CComponentObject(CComponentObject& object);
	virtual ~CComponentObject();
};
