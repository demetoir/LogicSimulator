#pragma once
#include <string>
class CComponentObject {
private:
	std::string componentName;
public:		
	void setComponentName(std::string _component);
	std::string getComponentName();
	CComponentObject();
	CComponentObject(CComponentObject& obj);
	~CComponentObject();
};