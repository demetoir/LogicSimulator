#pragma once
#include "ComponentObject.h"
#define SEVEN_SEGMENT_INPUT_INIT_VALUE 0
#define SEVEN_SEGMENT_INPUT_A 1
#define SEVEN_SEGMENT_INPUT_B 2
#define SEVEN_SEGMENT_INPUT_C 4
#define SEVEN_SEGMENT_INPUT_D 8
#define SEVEN_SEGMENT_INPUT_E 16
#define SEVEN_SEGMENT_INPUT_F 32
#define SEVEN_SEGMENT_INPUT_G 64
#define SEVEN_SEGMENT_STATE int 

#define SEVEN_SEGMENT_OUTPUT_INIT_VALUE 0;

class C7SegmentComponent : CComponentObject {
	
private:
	SEVEN_SEGMENT_STATE state;

public:
	
	C7SegmentComponent();
	C7SegmentComponent(C7SegmentComponent& object);
	~C7SegmentComponent();

	SEVEN_SEGMENT_STATE get7SegmentState();	 
	void set7SegmentState(SEVEN_SEGMENT_STATE _state);
	
};
