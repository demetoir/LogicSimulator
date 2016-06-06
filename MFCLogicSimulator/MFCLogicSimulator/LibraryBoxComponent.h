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

//부품의 터미널 타입
enum TERMINAL_TYPE {
	TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT,
	TERMINAL_TYPE_OUTPUT, TERMINAL_TYPE_WIRE
};

//component 타입
enum COMPONENT_TYPE {
	COMPONENT_TYPE_NONE,
	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

//부품들의 아이디
#define COMPONENT_ID int 
//vector 의 기본 사이즈
#define VECTOR_INIT_SIZE 10
//루프 카운트를 위한 최대 제한
#define LOOP_LIMIT 200

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

//라이브러리 박스를 로드,세이브할 구조체
struct LIBRARY_BOX_DATA {


	//라이브러리 박스의 인풋핀과 아웃풋 핀을 저장하는 벡터 리스트
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;

	vector < COMPONENT_ID > inputClockVector;

	//부품간을 연결나타내는 무방향 그래프의 인접리스트 
	vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;

	//부품들이 가지는 타입을 저장하는 벡터
	vector< COMPONENT_TYPE >  componentTypeVector;

	//부품들의 아이디를 저장하는 벡터
	vector < bool > componentIDVector;


	//bool isOscillation;
	//bool isLibraryBoxOutputValueChanged;

	//중첩된 라이브러리 박스
	vector < LIBRARY_BOX_DATA > internalLibraryBoxData;

};

class CLibraryBox :public CComponentObject {
#define LOOP_LIMIT 200
#define ADJ_LIST vector< vector < COMPONENT_CONENTION_INFO > >
private:
	int numberOfComponent;
	//부품들을 담을 벡터 객체들
	vector< CComponentObject* > componentVector;

	//라이브러리 박스의 인풋핀과 아웃풋 핀을 저장하는 벡터 리스트
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;
	vector < COMPONENT_ID > inputClockVector;

	//부품간을 연결나타내는 무방향 그래프의 인접리스트 
	ADJ_LIST inputGraph;
	ADJ_LIST outputGraph;
	
	//부품들이 가지는 타입을 저장하는 벡터
	vector< COMPONENT_TYPE >  componentTypeVector;

	//부품들의 아이디를 저장하는 벡터
	vector < bool > componentIDVector;
	//현재 지금 회로가 진동하는지 확인하는 플래그
	bool isOscillation;

	//현재 회로가 출력값이 바뀌었는지 확인하는 플래그
	bool isLibraryBoxOutputValueChanged;

	//회로를 갱신한다
	bool updateCircuit();

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	bool amIInsideBox;

	//부품의 아이디를 만들어줌
	COMPONENT_ID makeNewComponetID(COMPONENT_TYPE componentType);
	//부품의 아이디를 삭제함
	void deleteComponentID(COMPONENT_ID deleteId);
	
	//라이브러리 박스를 로드함
	bool loadLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData);
	//라이브러리 박스를 세이브함
	bool saveLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData);
	
	//부품하나에 아웃풋 getter
	bool getComponentOutputValue(COMPONENT_ID ID, int index);
	
	//현재 회로가 진동하는지 확인함
	bool checkOscillation();
	
	//부품 추가 실패시 false 반환
	bool addComponent(COMPONENT_INFO& componentInfo);	
	//라이브러리 박스를 추가하는 함수 오버로딩됨
	bool addComponent(COMPONENT_INFO& componentInfo, LIBRARY_BOX_DATA& libBoxdata);
	//부품삭제
	bool deleteComponent(COMPONENT_ID componentID);
	
	//부품 연결 
	bool connnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);
	//부품 분리
	bool disconnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);

	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index) ;
	virtual bool getOutputValue(int index) ;
	virtual bool update();

	//모든 부품을 초기값으로 돌림
	virtual void reset();

	bool setClockValue(int index, bool  _value);
	bool getClockValue(int index);
	int numberOfClock();

	CComponentObject* getComponentObject(int index);

	bool isPossibleConnection(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);

	void swapCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);
	void copyCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO& source, COMPONENT_CONENTION_INFO& destination);
	ADJ_LIST* getOutputGrahp();
	ADJ_LIST* getInputGrahp();

	//모든 정보를 삭제한다
	void deleteObject();

	void setOffOscillation();
};