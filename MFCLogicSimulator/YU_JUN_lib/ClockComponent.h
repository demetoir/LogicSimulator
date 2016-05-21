#pragma once
#include "ComponentObject.h"
#include <time.h>
class CClockComponent : CComponentObject {
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