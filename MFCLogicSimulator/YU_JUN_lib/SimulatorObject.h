#pragma once
//

//터미널 타입
enum TERMINAL_TYPE { TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT, TERMINAL_TYPE_OUTPUT };


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
		componentID = 0;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_CONENTION_INFO(COMPONENT_ID _componentId, TERMINAL_TYPE _terminalType, int _terminalNumber) {
		componentID = 0;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};



class CSimulatorObject {
private:

public:		
	CSimulatorObject();
	CSimulatorObject(CSimulatorObject& obj);
	virtual ~CSimulatorObject();
};