#pragma once
#include "ComponentObject.h"

#define WIRE_INPUT_TERMINAL_NUMBER 1
#define WIRE_OUTPUT_TERMINAL_NUMBER 1

class CWireComponent:public CSimulatorObject {
private:
	int startX, startY;
	int endX, endY;
	bool junction;
	bool value;

public:
	CWireComponent();
	CWireComponent(CWireComponent& object);
	CWireComponent(int _startX, int _startY, int _endX, int _endY);
	CWireComponent(int _startX, int _startY, int _endX, int _endY, bool _isStartWithJunction);
	virtual ~CWireComponent();

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

	void setValue(bool _value);
	int getValue();
};