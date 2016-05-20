#pragma once
#include <string>
class CSimulatorObject {
private:
	std::string componentName;
public:		
	void setComponentName(std::string _component);
	std::string getComponentName();
	CSimulatorObject();
	CSimulatorObject(CSimulatorObject& obj);
	~CSimulatorObject();
};