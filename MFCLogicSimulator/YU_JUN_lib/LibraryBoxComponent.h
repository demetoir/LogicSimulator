#pragma once
//조상 클래스 추가
#include "ComponentObject.h"

//논리 게이트 헤더 헤더추가
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
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
#include <queue>
using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
//디버깅용 출력하는거
#include <stdio.h>


enum TERMINAL_TYPE {
	TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT,
	TERMINAL_TYPE_OUTPUT, TERMINAL_TYPE_WIRE
};


//component 타입
enum COMPONENT_TYPE {
	COMPONENT_TYPE_NONE,
	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

#define COMPONENT_ID int 




//연결할 component의 구조체
struct COMPONENT_CONENTION_INFO {
	COMPONENT_CONENTION_INFO() {
		componentID = -1;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_CONENTION_INFO(COMPONENT_ID _componentId, TERMINAL_TYPE _terminalType, int _terminalNumber) {
		componentID = _componentId;
		terminalType = _terminalType;
		terminalNumber = _terminalNumber;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};


#define VECTOR_INIT_SIZE 10

//추가할 component의 구조체 
struct COMPONENT_INFO {
	COMPONENT_INFO() {
		componentID = 0;
		componentType = COMPONENT_TYPE_NONE;
	}
	COMPONENT_INFO(COMPONENT_TYPE type) {
		componentID = 0;
		componentType = type;
	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;
};


//보류
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
#define INPUT_PIN_INPUT_SIZE 0
#define INPUT_PIN_OUTPUT_SIZE 1
#define ANDGATE_INPUT_SIZE 2
#define ANDGATE_OUTPUT_SIZE 1
#define ORGATE_INPUT_SIZE 2
#define ORGATE_OUTPUT_SIZE 1
#define NOTGATE_INPUT_SIZE 1
#define NOTGATE_OUTPUT_SIZE 1
#define XORGATE_INPUT_SIZE 2
#define XORGATE_OUTPUT_SIZE 1
#define OUTPUT_PIN_INPUT_SIZE 1
#define OUTPUT_PIN_OUTPUT_SIZE 0 

private:
	int numberOfComponent;
	//부품들을 담을 벡터 객체들
	vector< CComponentObject* > componentVector;

	//라이브러리 박스의 인풋핀과 아웃풋 핀을 저장하는 벡터 리스트
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;

	//부품간을 연결나타내는 무방향 그래프의 인접리스트 
	vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;
	
	//부품들이 가지는 타입을 저장하는 벡터
	vector< COMPONENT_TYPE >  componentTypeVector;

	//부품들의 아이디를 저장하는 벡터
	vector < bool > componentIDVector;
	bool isOscillation;
	bool isLibraryBoxOutputValueChanged;
public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	

	//부품의 아이디를 만들어줌
	COMPONENT_ID makeNewComponetID(COMPONENT_TYPE componentType);
	//부품의 아이디를 삭제함
	void deleteComponentID(COMPONENT_ID deleteId);
	
	//라이브러리 박스를 로드함
	void loadLibrarybox(vector<LIBRARY_BOX_DATA>& LibraryBoxData);
	//라이브러리 박스를 세이브함
	void saveLibrarybox(vector<LIBRARY_BOX_DATA>& _componentList);

	//인풋 핀 하나에대한 getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);
	//아웃풋 핀 하나에대한 getter
	bool getSingleOutputPinValue(int _outputPinNumber);
	
	//부품 추가 실패시 false 반환
	bool addComponent(COMPONENT_INFO& componentInfo);	
	//부품삭제
	bool deleteComponent(COMPONENT_ID componentID);
	
	bool connnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB);

	bool disconnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB);

	//라이브러리 박스 내부회로 갱신 
	bool updateCircuit();
	
	//보여주기여용 상태 정보 출력해주는 프로그램
	void printstatus();

	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index) ;
	virtual bool getOutputValue(int index) ;
	virtual bool update();
};