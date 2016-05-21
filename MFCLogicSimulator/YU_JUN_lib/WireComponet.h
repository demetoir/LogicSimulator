#pragma once
#include "ComponentObject.h"


using namespace std;

class CWireComponent:public CSimulatorObject {

private:
	int startX, startY;
	int endX, endY;
	bool junction;
	bool value;

public:
	
	void setStartX(int _StartX);
	int getStartX();
	void setStartY(int _StartY);
	int getStartY();
	void setJuntion(bool _junction);
	bool getjuntion();
	void setEndX(int _EndX);
	int getEndX();
	void setEndY(int _EndY);
	int getEndY();

	CWireComponent();
	CWireComponent(CWireComponent& object);
	CWireComponent(int _startX, int _startY, int _endX, int _endY);
	CWireComponent(int _startX, int _startY, int _endX, int _endY, bool _isStartWithJunction);
	virtual ~CWireComponent();
	void setValue(bool _value);
	int getValue();

};