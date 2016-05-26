#pragma once
#include "ComponentObject.h"

class CNOTGateComponent :public CComponentObject {
#define NOT_GATE_INPUT_DEFAULT_VALUE false
#define NOT_GATE_OUTPUT_DEFAULT_VALUE false
private:
	bool inputValue;
	bool outputValue;
public:
	CNOTGateComponent();
	CNOTGateComponent(CNOTGateComponent& object);
	virtual ~CNOTGateComponent();

	//input value 를 변경하면 output value 가 변경되었는지 알려준다

	virtual bool setInputValue(int index,bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();


};