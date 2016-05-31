#pragma once

class CComponentObject {
private:
public:
	CComponentObject();
	CComponentObject(CComponentObject& object);
	virtual ~CComponentObject();
	//가상함수들
	virtual bool setInputValue(int index, bool _value) = 0;
	virtual bool getInputValue(int index) = 0;
	virtual bool getOutputValue(int index) = 0;
	virtual bool update() = 0;
	virtual int numberOfInput() = 0;
	virtual int numberOfOutput() = 0;
	virtual void reset() = 0;
};
