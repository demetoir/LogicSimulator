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

//input component 헤더 추가
#include "InputPinComponent.h"
#include "ClockComponent.h"
#include "OneBitSwitch.h"

//output pin 헤더 추가
#include "OutputPin.h"
#include "7SegmentComponent.h"
#include "OneBitLampComponent.h"
#include <vector>

//component type 열거형
enum COMPONENT_TYPE { COMPONENT_TYPE_INPUT_PIN,COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX,
	COMPONENT_TYPE_NONE
};

#define COMPONENT_ID int 

//보류
//추가할 component의 구조체 
struct COMPONENT_INFO {
	COMPONENT_INFO() {
		componentID = 0;
		componentType = COMPONENT_TYPE_NONE;
		x = 0;
		y = 0;
		direction = DIRECTION_EAST;
		label = std::string("");
	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;
	int x, y;
	enum DIRECTION direction;
	std::string label;

};

//연결할 component의 구조체
struct COMPONENT_CONENTION_INFO {
	COMPONENT_CONENTION_INFO() {
		componentID = COMPONENT_TYPE_NONE;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};


struct LIBRARY_BOX_DATA {
	LIBRARY_BOX_DATA() {

	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;


	//CSimulatorObject 정보
	std::string componentName;
	int numberOfInputTerminal;
	int numberOfOutputTerminal;

	//CComponentObject 정보
	int x, y;
	enum DIRECTION direction;
	std::string label;


};


class CLibraryBox :public CComponentObject {
private:
	//부품들을 담을 벡터 객체들
	std::vector<CSimulatorObject*> componentList;
	std::vector<COMPONENT_ID> inputPinIDList;
	std::vector<COMPONENT_ID> outputPinIDList;

	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connnectionInfo;

	//부품간의 그래프를표현할 2중 vector
	std::vector< std::vector<int> > componetGraph;

	//부품들의 ID를 저장하는 벡터
	std::vector< COMPONENT_TYPE >  componentIDList;

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	COMPONENT_ID getNewComponetID(COMPONENT_TYPE componentType);
	void deleteComponentID(COMPONENT_ID deleteId);


	//라이브러리 박스를 로드함
	void loadLibrarybox(std::vector<LIBRARY_BOX_DATA>& LibraryBoxData);
	//라이브러리 박스를 세이브함
	void saveLibrarybox(std::vector<LIBRARY_BOX_DATA>& _componentList);

	//인풋 핀 하나에대한 getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);

	//아웃풋 핀 하나에대한 getter
	bool getSingleOutputPinValue(int _outputPinNumber);
	

	//부품 추가 실패시 false 반환
	bool addComponent(COMPONENT_INFO& componentInfo);
	
	//부품삭제
	void deleteInputPin(COMPONENT_ID inputPinID);
	void deleteOutputPin(COMPONENT_ID outputPinID);
	bool deleteComponent(COMPONENT_ID componentID);
	
	//연결되지않은 부품을 연결함
	bool connectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);
	
	//연결된 부품을 분리함
	bool disconnectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);

	//라이브러리 박스 내부회로 갱신 
	bool updateCircuit();

};