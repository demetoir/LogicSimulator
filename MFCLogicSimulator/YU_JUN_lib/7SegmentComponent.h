#pragma once
#include "ComponentObject.h"


#include<vector>




#define SEVEN_SEGMENT_INPUT_VALUE_SIZE 7

class C7SegmentComponent :public CComponentObject {
#define SEVEN_SEGMENT_DEFUALT_VALUE false	
private:
	bool value[7];

public:	
	C7SegmentComponent();
	C7SegmentComponent(C7SegmentComponent& object);
	~C7SegmentComponent();


	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index);
	virtual bool getOutputValue(int index);
	virtual bool update();
};
