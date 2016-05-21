#pragma once

#include"ComponentObject.h"

class InputPinComponent : CComponentObject{
private:
	bool value;
public:
	InputPinComponent();
	InputPinComponent(InputPinComponent& object);
	~InputPinComponent();
	void setValue(bool _value);
	bool getValue();
};