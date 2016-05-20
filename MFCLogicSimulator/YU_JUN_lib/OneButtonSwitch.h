#pragma once
#include "ComponentObject.h"

class COnebuttonSwitch :public CComponentObject {

private:
	bool value;
public:
	COnebuttonSwitch();
	COnebuttonSwitch(COnebuttonSwitch& obj);
	virtual ~COnebuttonSwitch();
	bool getValue();
	void setValue(bool _val);
};