#pragma once
#include <string>
#include <vector>

#define ID_COMPONENT int 

class CSimulatorObject {
private:
	std::string componentName;
	ID_COMPONENT numberOfComponent;
	int numberOfInputTerminal;
	int numberOfOutputTerminal;
public:		
	void setComponentName(std::string _component);
	std::string getComponentName();
	CSimulatorObject();
	CSimulatorObject(CSimulatorObject& obj);
	virtual ~CSimulatorObject();
	ID_COMPONENT getNewComponetID();
	ID_COMPONENT getNumberOfComponent();
	void setNumberOfInputTerminal(int numberOfTerminal);
	int getNumberOfInputTerminal();
	void setNumberOfOutputTerminal(int numberOfTerminal);
	int getNumberOfOutputTerminal();
};