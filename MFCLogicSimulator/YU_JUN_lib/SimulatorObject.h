#pragma once
#include <string>
#define ID_COMPONENT int 
class CSimulatorObject {
private:
	std::string componentName;
	ID_COMPONENT numberOfComponent;
public:		
	void setComponentName(std::string _component);
	std::string getComponentName();
	CSimulatorObject();
	CSimulatorObject(CSimulatorObject& obj);
	virtual ~CSimulatorObject();
	ID_COMPONENT getNewComponetID();
	ID_COMPONENT getNumberOfComponent();
};