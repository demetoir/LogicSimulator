#pragma once
#include "ComponentObject.h"
#include "vector"



#define ONE_BIT_SWITCH_VALUE_SIZE 1
#define ONE_BIT_SWITCH_DEFAULT_VALUE false



class COneBitSwitchComponent :public CComponentObject {

private:
	std::vector<bool> value;

public:
	COneBitSwitchComponent();
	COneBitSwitchComponent(COneBitSwitchComponent& obj);
	virtual ~COneBitSwitchComponent();
	bool getValue();
	void setValue(bool _val);
};