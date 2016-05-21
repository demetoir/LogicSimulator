#pragma once


#include "ComponentObject.h"

class COutputPin : CComponentObject {
private:
	bool value;
public:
	COutputPin();
	COutputPin(COutputPin& object);
	~COutputPin();
	void setValue(bool _value);
	bool getValue(); 
};
