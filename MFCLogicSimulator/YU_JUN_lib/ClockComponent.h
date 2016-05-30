#pragma once
#include "ComponentObject.h"
#include <time.h>
#include <vector>

class CClockComponent :public CComponentObject {
#define CLOCK_COMPONENT_DEFAULT_CLOCK_HZ 10
#define CLOCK_COMPONENT_DEFAULT_VALUE false
private:
	bool value;
	double clockHZ;

public:
	CClockComponent();
	CClockComponent(CClockComponent& object);
	virtual ~CClockComponent();

	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
	virtual void reset();
	void setClockHZ(double _clockHZ);
	double getClockHZ();
	virtual int numberOfInput();
	virtual int numberOfOutput();	
};