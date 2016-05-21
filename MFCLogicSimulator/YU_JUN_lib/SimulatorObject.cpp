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
	numberOfComponent = 0;
	numberOfInputTerminal = 0;
	numberOfOutputTerminal = 0;
}

CSimulatorObject::CSimulatorObject(CSimulatorObject & obj)
{
	componentName = obj.getComponentName();
	numberOfComponent = 0;
}

CSimulatorObject::~CSimulatorObject()
{
}

ID_COMPONENT CSimulatorObject::getNewComponetID()
{
	numberOfComponent += 1;
	return numberOfComponent;
}

ID_COMPONENT CSimulatorObject::getNumberOfComponent()
{
	return numberOfComponent;
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

