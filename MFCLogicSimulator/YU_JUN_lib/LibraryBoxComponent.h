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

//component type 열거형
enum COMPONENT_TYPE { COMPONENT_TYPE_INPUT_PIN,COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

//추가할 component의 구조체
struct COMPONENT_INFO {
	COMPONENT_TYPE componentType;
	int x, y;
	enum DIRECTION direction;
	ID_COMPONENT componentID;
};

//연결할 component의 구조체
struct CONNECTING_COMPONENT_INFO {
	ID_COMPONENT componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};

struct LIBRARY_BOX_DATA {

};


class CLibraryBox :public CComponentObject {
private:
	//부품들을 담을 벡터 객체들
	std::vector<CComponentObject> logicGateList;
	std::vector<InputPinComponent> inputList;
	std::vector<COutputPin> outputList;
	std::vector<CWireComponent> wireList;

	//부품간의 그래프를표현할 2중 vector
	std::vector< std::vector<int> > componetGraph;

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	//라이브러리 박스를 로드함
	void loadLibrarybox(LIBRARY_BOX_DATA componentList);
	//라이브러리 박스를 세이브함
	LIBRARY_BOX_DATA saveLibrarybox();

	//인풋 핀 하나에대한 getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);

	//아웃풋 핀 하나에대한 getter
	void getSingleOutputPinValue(int _inputPinNumber);
	

	//부품 추가 실패시 false 반환
	bool addComponent(COMPONENT_INFO& componentInfo);
	
	//부품삭제
	void deleteInputPin(ID_COMPONENT inputPinID);
	void deleteOutputPin(ID_COMPONENT outputPinID);
	void deleteComponent(ID_COMPONENT componentID);
	
	//연결되지않은 부품을 연결함
	bool connectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	bool connectComponentAToB(CONNECTING_COMPONENT_INFO& AConponentInfo, CONNECTING_COMPONENT_INFO& BConponentInfo);
	
	//연결된 부품을 분리함
	bool disconnectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	bool disconnectComponentAToB(CONNECTING_COMPONENT_INFO& AConponentInfo, CONNECTING_COMPONENT_INFO& BConponentInfo);

	//라이브러리 박스 내부회로 갱신 
	bool updateCircuit();

};