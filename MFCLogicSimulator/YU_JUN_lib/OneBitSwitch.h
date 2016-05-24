#pragma once
#include "ComponentObject.h"
#include "vector"


#define ONE_BIT_SWITCH_INPUT_TERMINAL_NUMBER 0
#define ONE_BIT_SWITCH_OUTPUT_TERMINAL_NUMBER 1

#define ONE_BIT_SWITCH_VALUE_NUMBER 1

#define ONE_BIT_SWITCH_DEFAULT_VALUE false



class COneBitSwitchComponent :public CComponentObject {

private:
	std::vector<bool> value;
	std::vector<int>inputTerminalInfo;
	std::vector<int>outputTerminalInfo;

public:
	COneBitSwitchComponent();
	COneBitSwitchComponent(COneBitSwitchComponent& obj);
	virtual ~COneBitSwitchComponent();
	bool getValue();
	void setValue(bool _val);
};