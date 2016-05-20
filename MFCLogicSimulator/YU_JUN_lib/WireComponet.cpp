#include "WireComponet.h"

CWireComponent::CWireComponent()
{
	CLogicSimulatorComponent();
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
	isStartFromJunction = false;
	value = false;
}

CWireComponent::CWireComponent(int _startX, int _startY, int _endX, int _endY)
{
	startX = _startX;
	startY = _startY;
	endX = _endX;
	endY = _endY;
	isStartFromJunction = false;
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

void CWireComponent::makeJunction() 
{
	isStartFromJunction = true;
}

void CWireComponent::deleteJunction()
{
	isStartFromJunction = false;
}

int CWireComponent::getJunctionX()
{
	return junctionX;
}

int CWireComponent::getJuncTionY()
{
	return junctionY;
}
