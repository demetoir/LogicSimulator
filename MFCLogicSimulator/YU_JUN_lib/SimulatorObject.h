#pragma once
#include <string>
#include <vector>

enum TERMINAL_TYPE{TERMINAL_TYPE_INPUT,TERMINAL_TYPE_OUTPUT,TERMINAL_TYPE_NONE};

class CSimulatorObject {
private:
	std::string componentName;
	int numberOfInputTerminal;
	int numberOfOutputTerminal;

public:		
	CSimulatorObject();
	CSimulatorObject(CSimulatorObject& obj);
	virtual ~CSimulatorObject();

	void setComponentName(std::string _component);
	std::string getComponentName();

	void setNumberOfInputTerminal(int numberOfTerminal);
	int getNumberOfInputTerminal();
	void setNumberOfOutputTerminal(int numberOfTerminal);
	int getNumberOfOutputTerminal();
};