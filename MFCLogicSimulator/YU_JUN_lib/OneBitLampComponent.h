#pragma once
#include "ComponentObject.h"

#include <vector>


#define ONE_BIT_LAMP_INPUT_VALUE_SIZE 1

#define ONE_BIT_LAMP_DEFUALT_VALUE 1


enum ONE_BIT_LAMP_STATE{LAMP_ON,LAMP_OFF};
class COneBitLampComponent :public CComponentObject {
private:
	std::vector<bool> value;
public:
	COneBitLampComponent();
	COneBitLampComponent(COneBitLampComponent& object);
	~COneBitLampComponent();

	void setValue(bool _value);
	bool getValue();

};