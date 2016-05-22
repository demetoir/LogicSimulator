#pragma once
#include "ComponentObject.h"
#define ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER 0
#define ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER 1
class COneBitSwitchComponent :public CComponentObject {

private:
	bool value;
public:
	COneBitSwitchComponent();
	COneBitSwitchComponent(COneBitSwitchComponent& obj);
	virtual ~COneBitSwitchComponent();
	bool getValue();
	void setValue(bool _val);
};