#pragma once
#include "ComponentObject.h"
#include <vector>


#define ONE_BIT_LAMP_INPUT_VALUE_SIZE 1



class COneBitLampComponent :public CComponentObject {
#define ONE_BIT_LAMP_DEFUALT_VALUE false
private:
	std::vector<bool> value;
public:
	COneBitLampComponent();
	COneBitLampComponent(COneBitLampComponent& object);
	~COneBitLampComponent();

	void setValue(bool _value);
	bool getValue();

};