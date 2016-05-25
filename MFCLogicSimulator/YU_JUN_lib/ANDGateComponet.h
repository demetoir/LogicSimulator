#pragma once
#include "ComponentObject.h"



class CANDGateComponent :public CComponentObject{
#define AND_GATE_OUTPUT_DEFUALT_VALUE false
#define AND_GATE_INPUT_DEFUALT_VALUE false
private:
	bool inputValue[2];
	bool outputValue;

public:
	CANDGateComponent();
	CANDGateComponent(CANDGateComponent& object);
	virtual ~CANDGateComponent();

	//input이 바뀌면 output 값이 바뀌었는지 를 반환해줌
	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue();
	void updateOutputValue();
};