#pragma once
#include "ComponentObject.h"
#include <time.h>
#include <vector>



#define CLOCK_COMPONENT_OUTPUT_VALUE_SIZE 1
#define CLOCK_COMPONENT_DEFAULT_CLOCK_HZ 10


class CClockComponent :public CComponentObject {
#define CLOCK_COMPONENT_DEFAULT_VALUE false
private:
	bool value;
	double clockHZ;
	std::vector<int>inputTerminalInfo;
	std::vector<int>outputTerminalInfo;
	std::vector<bool>value;

public:
	CClockComponent();
	CClockComponent(CClockComponent& object);
	virtual ~CClockComponent();

	void setValue(int valueIndex,bool _value);
	bool getValue(int valueIndex);

	void setClockHZ(double _clockHZ);
	double getClockHZ();
	
};