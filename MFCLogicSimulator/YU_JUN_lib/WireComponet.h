#pragma once
#include "LogicSimulatorComponent.h"
#include <vector>

using namespace std;
class CWireComponent {


	int startX, startY;
	int endX, endY;
	bool isStartFromJunction;
	int junctionX;
	int junctionY;
	bool value;
public:
	
	void setStartX(int _StartX);
	int getStartX();
	void setStartY(int _StartY);
	int getStartY();

	void setEndX(int _EndX);
	int getEndX();
	void setEndY(int _EndY);
	int getEndY();
	void makeJunction();

	void deleteJunction();
	int getJunctionX();
	int getJuncTionY();

	CWireComponent();
	CWireComponent(int _startX, int _startY, int _endX, int _endY);
	
	~CWireComponent();
	void setValue(bool _value);
	int getValue();


};