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

