#pragma once
//조상 클래스 추가
#include "ComponentObject.h"

//논리 게이트 헤더 헤더추가
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
#include "NANDGateComponent.h"
#include "NORGateComponent.h"
#include "NOTGateComponent.h"
#include "XORGateComponent.h"

//와이어 헤더 추가
#include "WireComponet.h"

//input pin 헤더 추가
#include "InputPinComponent.h"

//output pin 헤더 추가
#include "OutputPin.h"

#include <vector>

 
class CLibraryBox : CComponentObject {

private:
	vector<CComponentObject> logicGateList;
	vector<InputPinComponent> inputList;
	vector< vector<int> > componetGrape;
	vector<COutputPin> outputList;
	vector<CWireComponent> wireList;
	int totalComponentNumber;
	

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	void setinputValue(bool _inputValue, int componentnumber);
	void getOutputValue(int ComponentNumber);
	
	void addInputPin();
	void addOuputPin();	
	void addWire();
	void addANDGate();
	void addORGate();
	void addNORGate();
	void addNANDGate();
	void addNOTGate();
	void addXORGate();

	void deleteInputPin();
	void deleteOutputPin();
	void deleteOutputPin()












};