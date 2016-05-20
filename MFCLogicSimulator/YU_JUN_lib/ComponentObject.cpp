#include "ComponentObject.h"

CComponentOBject::CComponentOBject()
{
	CSimulatorObject();
	x = 0;
	y = 0;
	label = std::string("");
	direction = DIRECTION_EAST;
}

CComponentOBject::CComponentOBject(CComponentOBject & object)
{
	CSimulatorObject(object);
	x = object.getX;
	y = object.getY;
	label = object.getLabel();
	direction = object.getDirection();
}

CComponentOBject::~CComponentOBject()
{
}

void CComponentOBject::setX(int _x)
{
	x = _x;
}

int CComponentOBject::getX()
{
	return x;
}

void CComponentOBject::setY(int _y)
{
	y = _y;
}

int CComponentOBject::getY()
{
	return y;
}

void CComponentOBject::setLabel(std::string _label)
{
	label = std::string(_label);
}

std::string CComponentOBject::getLabel()
{
	return label;
}

void CComponentOBject::setDirection(DIRECTION _direction)
{
	direction = _direction;
}

DIRECTION CComponentOBject::getDirection()
{
	return direction;
}
