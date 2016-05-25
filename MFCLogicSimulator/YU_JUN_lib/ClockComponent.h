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

	void setValue(bool _value);
	bool getValue();

	void setClockHZ(double _clockHZ);
	double getClockHZ();
	
};