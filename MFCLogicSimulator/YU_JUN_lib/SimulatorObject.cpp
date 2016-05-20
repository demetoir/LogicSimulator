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
}

CSimulatorObject::CSimulatorObject(CSimulatorObject & obj)
{
	componentName = obj.getComponentName();
}

CSimulatorObject::~CSimulatorObject()
{
}

