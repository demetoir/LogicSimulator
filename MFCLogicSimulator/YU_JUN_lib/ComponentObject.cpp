#include "ComponentObject.h"

CComponentObject::CComponentObject()
{
	CSimulatorObject();	
}

CComponentObject::CComponentObject(CComponentObject & object):
	CSimulatorObject(object)
{

}

CComponentObject::~CComponentObject()
{
}
