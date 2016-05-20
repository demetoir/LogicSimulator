#include "ComponentObject.h"

CComponentObject::CComponentObject()
{
	CSimulatorObject();
	x = 0;
	y = 0;
	label = std::string("");
	direction = DIRECTION_EAST;
}

CComponentObject::CComponentObject(CComponentObject & object):
	CSimulatorObject(object)
{
	x = object.getX();
	y = object.getY();
	label = object.getLabel();
	direction = object.getDirection();
}

CComponentObject::~CComponentObject()
{
}

void CComponentObject::setX(int _x)
{
	x = _x;
}

int CComponentObject::getX()
{
	return x;
}

void CComponentObject::setY(int _y)
{
	y = _y;
}

int CComponentObject::getY()
{
	return y;
}

void CComponentObject::setLabel(std::string _label)
{
	label = std::string(_label);
}

std::string CComponentObject::getLabel()
{
	return label;
}

void CComponentObject::setDirection(DIRECTION _direction)
{
	direction = _direction;
}

DIRECTION CComponentObject::getDirection()
{
	return direction;
}
