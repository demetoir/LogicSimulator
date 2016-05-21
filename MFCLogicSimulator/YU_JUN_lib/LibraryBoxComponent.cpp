#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	setComponentName(std::string("library box"));


}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{
	setComponentName(std::string("library box"));
	
}

CLibraryBox::~CLibraryBox()
{
}

ID_COMPONENT CLibraryBox::getNewComponentID()
{
	numberOfComponent += 1;
	return numberOfComponent;
}
