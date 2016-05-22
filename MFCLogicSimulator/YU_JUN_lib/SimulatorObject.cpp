#include "SimulatorObject.h"

void CSimulatorObject::setComponentName(std::string _componentName)
{
	componentName = std::string(_componentName);
	
}

std::string CSimulatorObject::getComponentName()
{
	return componentName;
}

CSimulatorObject::CSimulatorObject()
{
	componentName = std::string("");
	numberOfInputTerminal = 0;
	numberOfOutputTerminal = 0;
}

CSimulatorObject::CSimulatorObject(CSimulatorObject & obj)
{
	componentName = obj.getComponentName();
}

CSimulatorObject::~CSimulatorObject()
{
}

void CSimulatorObject::setNumberOfInputTerminal(int numberOfTerminal)
{
	numberOfInputTerminal = numberOfTerminal;
}

int CSimulatorObject::getNumberOfInputTerminal()
{
	return numberOfInputTerminal;
}

void CSimulatorObject::setNumberOfOutputTerminal(int numberOfTerminal)
{
	numberOfOutputTerminal = numberOfTerminal;
}

int CSimulatorObject::getNumberOfOutputTerminal()
{
	return numberOfOutputTerminal;
}

