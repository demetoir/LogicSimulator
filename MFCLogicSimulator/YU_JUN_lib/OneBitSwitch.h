#pragma once
#include "ComponentObject.h"
#define ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER 0
#define ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER 1
class COneBitSwitch :public CComponentObject {

private:
	bool value;
public:
	COneBitSwitch();
	COneBitSwitch(COneBitSwitch& obj);
	virtual ~COneBitSwitch();
	bool getValue();
	void setValue(bool _val);
};