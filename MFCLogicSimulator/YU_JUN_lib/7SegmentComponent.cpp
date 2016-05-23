#include "7SegmentComponent.h"

C7SegmentComponent::C7SegmentComponent()
{
	state = SEVEN_SEGMENT_OUTPUT_INIT_VALUE;
}

C7SegmentComponent::C7SegmentComponent(C7SegmentComponent & object)
	:CComponentObject(object)
{
	state = SEVEN_SEGMENT_OUTPUT_INIT_VALUE;
}

C7SegmentComponent::~C7SegmentComponent()
{
	
}

SEVEN_SEGMENT_STATE C7SegmentComponent::get7SegmentState()
{
	return state;
}

void C7SegmentComponent::set7SegmentState(SEVEN_SEGMENT_STATE _state)
{
	state = _state;
}

