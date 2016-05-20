#include "logicSimulatorComponent.h"

CLogicSimulatorComponent::CLogicSimulatorComponent()
{
	x = 0;
	y = 0;
	label = std::string("");
	direction = DIRECTION_EAST;
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
}

CLogicSimulatorComponent::~CLogicSimulatorComponent()
{
}

void CLogicSimulatorComponent::setX(int newX)
{
	x = newX;
}

int CLogicSimulatorComponent::getX()
{
	return x;
}

void CLogicSimulatorComponent::setY(int newY)
{
	y = newY;
}

int CLogicSimulatorComponent::getY()
{
	return y;
}

void CLogicSimulatorComponent::setLabel(std::string newLabel)
{
	label = std::string(newLabel);
}

std::string CLogicSimulatorComponent::getLabel()
{
	return label;
}

void CLogicSimulatorComponent::setInputValue1(bool newInputValue1)
{
	inputValue1 = newInputValue1;
	
}

bool CLogicSimulatorComponent::getInputvalue1()
{
	return inputValue1;
}

void CLogicSimulatorComponent::setInputValue2(bool newInputValue2)
{
	inputValue2 = newInputValue2;
}

bool CLogicSimulatorComponent::getInputValue2()
{
	return inputValue2;
}

void CLogicSimulatorComponent::setOutputValue(bool newOutputValue)
{
	outputValue = newOutputValue;
}

bool CLogicSimulatorComponent::getOutputValue()
{
	return outputValue;
}

void CLogicSimulatorComponent::setDirection(DIRECTION newDirection)
{
	direction = newDirection;
}

DIRECTION CLogicSimulatorComponent::getDirection()
{
	return direction;
}

void CLogicSimulatorComponent::updateOutputValue()
{
}

