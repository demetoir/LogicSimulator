#include "ComponentObject.h"

void CComponentObject::setComponentName(std::string _componentName)
{
	componentName = std::string(_componentName);
}

std::string CComponentObject::getComponentName()
{
	return componentName;
}

CComponentObject::CComponentObject()
{
	componentName = std::string("");
}

CComponentObject::CComponentObject(CComponentObject & obj)
{
	componentName = obj.getComponentName();
}

CComponentObject::~CComponentObject()
{
}

