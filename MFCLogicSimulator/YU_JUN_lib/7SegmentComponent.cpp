#include "7SegmentComponent.h"

C7SegmentComponent::C7SegmentComponent()
{
	value.resize(SEVEN_SEGMENT_INPUT_VALUE_SIZE + 1, SEVEN_SEGMENT_DEFUALT_VALUE);
}

C7SegmentComponent::C7SegmentComponent(C7SegmentComponent & object)
	:CComponentObject(object)
{
	value.resize(SEVEN_SEGMENT_INPUT_VALUE_SIZE + 1, SEVEN_SEGMENT_DEFUALT_VALUE);
}

C7SegmentComponent::~C7SegmentComponent()
{
	
}

bool C7SegmentComponent::get7SegmentState(int index)
{
	return value[index];
}

void C7SegmentComponent::set7SegmentState(int index, bool _value)
{
	value[index] = _value;
}

