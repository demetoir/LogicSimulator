#include "stdafx.h"

#include "7SegmentComponent.h"

C7SegmentComponent::C7SegmentComponent()
{
	for (int i = 0; i < 7; i++) {
		value[i] = SEVEN_SEGMENT_DEFUALT_VALUE;
	}
}

C7SegmentComponent::C7SegmentComponent(C7SegmentComponent & object)
	:CComponentObject(object)
{
	for (int i = 0; i < 7; i++) {
		value[i] = SEVEN_SEGMENT_DEFUALT_VALUE;
	}
}

C7SegmentComponent::~C7SegmentComponent()
{
	
}

bool C7SegmentComponent::setInputValue(int index, bool _value)
{
	bool oldValue = value[index];
	value[index] = _value;
	if (oldValue == _value) {
		return false;
	}
	return true;
}

bool C7SegmentComponent::getInputValue(int index)
{
	return value[index];
}

bool C7SegmentComponent::getOutputValue(int index)
{
	return value[index];
}

bool C7SegmentComponent::update()
{
	return false;
}

void C7SegmentComponent::reset()
{
	for (int i = 0; i < 7; i++) {
		value[i] = SEVEN_SEGMENT_DEFUALT_VALUE;
	}
}

int C7SegmentComponent::numberOfInput()
{
	return 7;
}

int C7SegmentComponent::numberOfOutput()
{
	return 0;
}

