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

//세이브 로드 할 구조체
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

	//라이브러리 박스의 인풋핀과 아웃풋 핀을 저장하는 벡터 리스트
	std::vector<COMPONENT_ID> inputPinIDList;
	std::vector<COMPONENT_ID> outputPinIDList;

	//부품간을 연결나타내는 방향 그래프의 인접리스트  
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connnectionGraph;

	//부품에 어떤 단자가 사용중인지 알려주는 이차원 벡터
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connectedTerminalInfo;
	
	//부품들이 가지는 타입을 저장하는 벡터
	std::vector< COMPONENT_TYPE >  componentTypeList;


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
	bool deleteComponent(COMPONENT_ID componentID);
	
	//연결되지않은 부품과 와이어를 연결함
	bool connectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);
	
	//와이어와 연결된 부품을 분리함
	bool disconnectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);

	//wireA 에 juntion을 만들고 거기 에다가 wireB를 연결함
	bool connectWireAndWire(COMPONENT_CONENTION_INFO& wireA, COMPONENT_CONENTION_INFO& wireB);

	//wireA 에 juntion을 제거하고 wireB를 분리함
	bool disconnectWireAndWire(COMPONENT_CONENTION_INFO& wireA, COMPONENT_CONENTION_INFO& wireB);

	//라이브러리 박스 내부회로 갱신 
	bool updateCircuit();

};