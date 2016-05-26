#pragma once
#include "SimulatorObject.h"


class CComponentObject {
private:
public:
	CComponentObject();
	CComponentObject(CComponentObject& object);
	virtual ~CComponentObject();
	//가상함수들
	virtual bool setInputValue() = 0;
	virtual bool getInputValue() = 0;
	virtual bool getOutputValue() = 0;
	virtual bool update() = 0;
};
