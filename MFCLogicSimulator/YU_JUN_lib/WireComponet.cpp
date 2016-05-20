#include "WireComponet.h"

CWireComponent::CWireComponent()
{
	CComponentObject();
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
	junction = false;
	value = false;
}

CWireComponent::CWireComponent(CWireComponent&  object):CComponentObject(object)
{

	startX = object.getStartX();
	startY = object.getStartY();
	endX = object.getEndX();
	endY = object.getEndY();
	junction = object.getjuntion();
	value = false;	
}

CWireComponent::CWireComponent(int _startX, int _startY, int _endX, int _endY)
{
	CComponentObject();
	startX = _startX;
	startY = _startY;
	endX = _endX;
	endY = _endY;
	junction = false;
	value = false;
}

CWireComponent::CWireComponent(int _startX, int _startY, int _endX, int _endY, bool _junction)
{
	startX = _startX;
	startY = _startY;
	endX = _endX;
	endY = _endY;
	junction = _junction;
}

CWireComponent::~CWireComponent()
{
	
}

void CWireComponent::setValue(bool _value)
{
	value = _value;
}

int CWireComponent::getValue()
{
	return value;
}

void CWireComponent::setStartX(int _StartX)
{
	startX = _StartX;
}

int CWireComponent::getStartX()
{
	return startX;
}

void CWireComponent::setStartY(int _StartY)
{
	startY = _StartY;
}

int CWireComponent::getStartY()
{
	return startY;
}

void CWireComponent::setJuntion(bool _junction)
{
	junction = _junction;
}

bool CWireComponent::getjuntion()
{
	return junction;
}

void CWireComponent::setEndX(int _EndX)
{
	endX = _EndX;
}

int CWireComponent::getEndX()
{
	return endX;
}

void CWireComponent::setEndY(int _EndY)
{
	endY = _EndY;
}

int CWireComponent::getEndY()
{
	return endY;
}

