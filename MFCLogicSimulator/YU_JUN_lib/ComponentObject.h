#pragma once
#include "SimulatorObject.h"
#include <string>

enum DIRECTION {DIRECTION_NONE,DIRECTION_SOUTH,DIRECTION_NORTH,DIRECTION_EAST,DIRECTION_WEST};

class CComponentObject : public CSimulatorObject {
private:
	int  x, y;
	std::string label;
	DIRECTION direction;

public:
	CComponentObject();
	CComponentObject(CComponentObject& object);
	virtual ~CComponentObject();
	void setX(int _x);
	int getX();
	void setY(int _y);
	int getY();
	void setLabel(std::string _label);
	std::string getLabel();
	void setDirection(DIRECTION _direction);
	DIRECTION getDirection();
};
