#pragma once
#include "ComponentObject.h"


#include<vector>


#define SEVEN_SEGMENT_DEFUALT_VALUE false

#define SEVEN_SEGMENT_INPUT_TERMINAL_NUMBER 7
#define SEVEN_SEGMENT_OUTPUT_TERMINAL_NUMBER 7
#define SEVEN_SEGMENT_VALUE_NUMBER 7

class C7SegmentComponent :public CComponentObject {
	
private:
	std::vector<bool> value;

public:	
	C7SegmentComponent();
	C7SegmentComponent(C7SegmentComponent& object);
	~C7SegmentComponent();

	bool get7SegmentState(int index);	 
	void set7SegmentState(int index,bool _value);	
};
