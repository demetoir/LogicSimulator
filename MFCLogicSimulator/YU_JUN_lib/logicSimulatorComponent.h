#pragma once

#include <string>

enum DIRECTION {NORTH,SOUTH,EAST,WEST};
class CLogicSimulatorComponent {

	CLogicSimulatorComponent();
	~CLogicSimulatorComponent();


	int x, y;
	std::string label;
	bool inputValue1, inputValue2;
	bool ouputValue;
	DIRECTION direction;

	void setX(int newX);
	int getX();
	void setY(int newY);
	int getY();

	void setLabel(std::string newLable);
	std::string getLabel();
	void setInputValue1(bool newInputValue1);
	bool getInputvalue1();
	void setInputValue2(bool newInputValue2);
	bool getInputValue2();
	void setOutputValue(bool newOutputValue);
	bool getOutputValue();
	void setDirection(DIRECTION newDirection);
	DIRECTION getDirection();



};