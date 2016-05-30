#pragma once
#include "ComponentObject.h"

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
	virtual void reset();
	virtual int numberOfInput();
	virtual int numberOfOutput();
};
