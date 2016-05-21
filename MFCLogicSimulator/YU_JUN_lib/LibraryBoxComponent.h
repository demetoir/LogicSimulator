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


class CLibraryBox :public CComponentObject {
private:
	//부품들을 담을 벡터 객체들
	std::vector<CComponentObject> logicGateList;
	std::vector<InputPinComponent> inputList;
	std::vector<COutputPin> outputList;
	std::vector<CWireComponent> wireList;

	//부품간의 그래프를표현할 2중 vector
	std::vector< std::vector<int> > componetGrape;
	
	//모든 부품의 수
	int totalComponentNumber;

	// 부품들의 id를 만들어주는 변수
	// 지금까지 생성한 부품의 수로 받음


public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	void setinputValue(bool _inputValue, int componentnumber);
	void getOutputValue(int ComponentNumber);
	
	//새로운 component Id 생성 해줌


	//부품 추가	
	ID_COMPONENT addInputPin();
	ID_COMPONENT addOutputPin();
	ID_COMPONENT addWire();
	ID_COMPONENT addANDGate();
	ID_COMPONENT addORGate();
	ID_COMPONENT addNORGate();
	ID_COMPONENT addNANDGate();
	ID_COMPONENT addNOTGate();
	ID_COMPONENT addXORGate();
	
	//부품삭제
	void deleteInputPin(ID_COMPONENT inputPinID);
	void deleteOutputPin(ID_COMPONENT outputPinID);
	void deleteComponent(ID_COMPONENT componentID);
	
	//연결되지않은 부품을 연결함
	bool connectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	
	//연결된 부품을 분리함
	bool disConnectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);











};