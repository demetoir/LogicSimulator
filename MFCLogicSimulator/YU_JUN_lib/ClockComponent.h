#pragma once
#include "ComponentObject.h"
#include <time.h>
#define CLOCK_COMPONENT_INPUT_TERMINAL_NUMBER 1
#define CLOCK_COMPONENT_OUTPUT_TERMINAL_NUMBER 0
class CClockComponent :public CComponentObject {
private:
	bool value;
	double clockHZ;
public:
	CClockComponent();
	CClockComponent(CClockComponent& object);
	virtual ~CClockComponent();
	void setValue(bool _value);
	bool getValue();
	void setClockHZ(double _clockHZ);
	double getClockHZ();
};