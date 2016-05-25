#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//컴포넌트를 담을벡터
	componentVector.resize(VECTOR_INIT_SIZE);

	inputPinIDVector.resize(VECTOR_INIT_SIZE);
	outputPinIDVector.resize(VECTOR_INIT_SIZE);

	//컴포넌트 타입을 저장하는 벡터
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//컴포넌트 아이디을 저장하는 
	componentIDVector.resize(VECTOR_INIT_SIZE,false);

	//연결하는 무방향 그래프
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{

}

CLibraryBox::~CLibraryBox()
{
	//동적 할당되는 부분을 모두 해제함
	for (int i = 0; i < componentVector.size(); i++) {
		if (componentIDVector[i] == true ) {
			delete componentVector[i];
		}
	}
}

//새로운 컴포넌트 아이디를 생성해줌
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	for (int i = 1; i < componentTypeVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = false;
			componentTypeVector[i] = componentType;
			return i;
		}
	}
	componentIDVector.push_back(true);
	componentTypeVector.push_back(componentType);
	return componentTypeVector.size()-1;
}

//컴포넌트 아이디를 삭제함
void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentTypeVector[deleteId] = COMPONENT_TYPE_NONE;
	componentIDVector[deleteId] = false;
}


//라이브러리 박스의 input output pin에대한 getter setter
void CLibraryBox::setSingleInputPinValue(bool _inputValue, int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
}

bool CLibraryBox::getSingleInputPinValue(int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = inputPinIDVector[_outPutPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[outputPinID]);
	CInputPinComponent* outputPinObject = ((CInputPinComponent*)componentObject);
}

bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo)
{
	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;
	
	//아이디를 할당해줌
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//부품들의 저장할공간과 그래프의 용량을 더 추가 해야 할경우 확장함
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 10);
		inputGraph.resize(inputGraph.size() + 10);
		outputGraph.resize(outputGraph.size() + 10);
	}

	switch (newComponentType)
	{
		// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new CInputPinComponent();
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(INPUT_PIN_OUTPUT_VALUE_SIZE+1);
		break;
	case COMPONENT_TYPE_CLOCK:
		componentVector[newComponentID] = new CClockComponent();
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(CLOCK_COMPONENT_OUTPUT_VALUE_SIZE+1);
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentVector[newComponentID] = new COneBitSwitchComponent();		
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE);
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		inputGraph[newComponentID].resize(AND_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(AND_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		inputGraph[newComponentID].resize(OR_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(OR_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		inputGraph[newComponentID].resize(NOT_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(NOT_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		inputGraph[newComponentID].resize(XOR_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(XOR_GATE_OUTPUT_VALUE_SIZE);
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///대충...
		inputGraph[newComponentID].resize(5);
		outputGraph[newComponentID].resize(5);
		break;

		//output component
	case COMPONENT_TYPE_7SEGMENT:
		componentVector[newComponentID] = new C7SegmentComponent();
		inputGraph[newComponentID].resize(SEVEN_SEGMENT_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		inputGraph[newComponentID].resize(OUTPUT_PIN_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentVector[newComponentID] = new COneBitLampComponent();
		inputGraph[newComponentID].resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
		break;


	//라이브러리 박스 나중에함
	case COMPONENT_TYPE_LIBRARY_BOX:	 
		break;
	//생성할수없음
	default:
		deleteComponentID(newComponentID);
		return false;
		break;
	}



	//생성 성공
	return true;
}


//재구현 
bool CLibraryBox::deleteComponent(COMPONENT_ID _componentID)
{
	//존재하지 않은 부품을 삭제하려고 하면 false 반환
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//연결된 부품을 찾아서 연결된부품에서 지우려는 부품의 연결을 끊고 사용하는 단자를 갱신함
	
	//연결된 반편 부품의 그래프와 터미널 정보를 갱신함
	

	//지워지는 부품의 그래프와 터미널 정보를 갱신함


	//컴포넌트 아이디 삭제

	return true;
}

bool CLibraryBox::connectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// 존재하지 않는 부품이랑 연결하려할떄 연결못하게함
	if (componentTypeVector[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* connectionInfo;
	// 연결하려는 부품의 단자가 이미사용중인지 검사
	for (int i = 0; i < connectedTerminalInfo[ComponentInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[ComponentInfo.componentID][i];
		if (connectionInfo->componentID == ComponentInfo.componentID &&
			connectionInfo->terminalNumber == ComponentInfo.terminalNumber&&
			connectionInfo->terminalType == ComponentInfo.terminalType) {
			return false;
		}
	}
	// 연결하려는 줄의 단자가 이미 사용중인자 검사
	for (int i = 0; i < connectedTerminalInfo[wireInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[wireInfo.componentID][i];
		if (connectionInfo->componentID == wireInfo.componentID &&
			connectionInfo->terminalNumber == wireInfo.terminalNumber&&
			connectionInfo->terminalType == wireInfo.terminalType) {
			return false;
		}
	}

	//양뱡향으로 연결함
	connnectionGraph[ComponentInfo.componentID].push_back(wireInfo);
	connectedTerminalInfo[ComponentInfo.componentID].push_back(ComponentInfo);
	connnectionGraph[wireInfo.componentID].push_back(ComponentInfo);
	connectedTerminalInfo[wireInfo.componentID].push_back(wireInfo);
	return true;
}

bool CLibraryBox::disconnectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// 존재하지 않는 부품이랑 분리하려할떄 연결못하게함
	if (componentTypeVector[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* currrentComponent;
	//부품에서 와이어방향으로 연결된것을 끊음
	for (int i = 0; i < connnectionGraph[ComponentInfo.componentID].size(); i++) {
		currrentComponent = &connnectionGraph[ComponentInfo.componentID][i];
		if (currrentComponent->componentID == wireInfo.componentID &&
			currrentComponent->terminalNumber == wireInfo.terminalNumber &&
			currrentComponent->terminalType == wireInfo.terminalType) {
			connnectionGraph[ComponentInfo.componentID].erase(connnectionGraph[ComponentInfo.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* currrentWire;
	//와이어에서 부품 방향으로 연결된것을 끊음
	for (int i = 0; i < connnectionGraph[wireInfo.componentID].size(); i++) {
		currrentWire = &connnectionGraph[wireInfo.componentID][i];
		if (currrentWire->componentID == ComponentInfo.componentID &&
			currrentWire->terminalNumber == ComponentInfo.terminalNumber &&
			currrentWire->terminalType == ComponentInfo.terminalType) {
			connnectionGraph[wireInfo.componentID].erase(connnectionGraph[wireInfo.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* connectionInfo;
	//사용했던 부품의 단자의 목록을 갱신함
	for (int i = 0; i < connectedTerminalInfo[ComponentInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[ComponentInfo.componentID][i];
		if (connectionInfo->componentID == ComponentInfo.componentID &&
			connectionInfo->terminalNumber == ComponentInfo.terminalNumber &&
			connectionInfo->terminalType == ComponentInfo.terminalType) {
			connectedTerminalInfo[ComponentInfo.componentID].erase(connectedTerminalInfo[ComponentInfo.componentID].begin() + i);
			break;
		}
	}

	//사용했던 와이어의 단자를 갱신함
	for (int i = 0; i < connectedTerminalInfo[wireInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[wireInfo.componentID][i];
		if (connectionInfo->componentID == wireInfo.componentID &&
			connectionInfo->terminalNumber == wireInfo.terminalNumber &&
			connectionInfo->terminalType == wireInfo.terminalType) {
			connectedTerminalInfo[wireInfo.componentID].erase(connectedTerminalInfo[wireInfo.componentID].begin() + i);
			break;
		}
	}

	return true;
}

bool CLibraryBox::connectWireAndWire(COMPONENT_CONENTION_INFO & wireA, COMPONENT_CONENTION_INFO & wireB)
{
	//둘중 하나라도 존재하지않는 부품일떄
	if (componentTypeVector[wireA.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireB.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}
	COMPONENT_CONENTION_INFO* wire;
	//이미 연결했었는지 확인함
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		wire = &connnectionGraph[wireA.componentID][i];
		if (wire->componentID == wireB.componentID &&
			wire->terminalNumber == wireB.terminalNumber &&
			wire->terminalType == wireB.terminalType) {
			return false;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		wire = &connnectionGraph[wireB.componentID][i];
		if (wire->componentID == wireA.componentID &&
			wire->terminalNumber == wireA.terminalNumber &&
			wire->terminalType == wireA.terminalType) {
			return false;
		}
	}

	//연결함
	connnectionGraph[wireA.componentID].push_back(wireB);
	connnectionGraph[wireB.componentID].push_back(wireA);
	connectedTerminalInfo[wireA.componentID].push_back(wireA);
	connectedTerminalInfo[wireB.componentID].push_back(wireB);

	return true;
}

bool CLibraryBox::disconnectWireAndWire(COMPONENT_CONENTION_INFO & wireA, COMPONENT_CONENTION_INFO & wireB)
{
	//존재하지 와이어를 분리하려는지 검사함
	if (componentTypeVector[wireA.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireB.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//연결 그래프에서 서로 와이어를 분리함
	COMPONENT_CONENTION_INFO* currentWire;
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		currentWire = &connnectionGraph[wireA.componentID][i];
		if (currentWire->componentID == wireB.componentID &&
			currentWire->terminalNumber == wireB.terminalNumber &&
			currentWire->terminalType == wireB.terminalType) {
			connnectionGraph[wireA.componentID].erase(connnectionGraph[wireA.componentID].begin() + i);
break;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		currentWire = &connnectionGraph[wireB.componentID][i];
		if (currentWire->componentID == wireA.componentID &&
			currentWire->terminalNumber == wireA.terminalNumber &&
			currentWire->terminalType == wireA.terminalType) {
			connnectionGraph[wireB.componentID].erase(connnectionGraph[wireB.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* terminalInfo;
	//서로 사용하는 단자를 갱신함
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		terminalInfo = &connnectionGraph[wireA.componentID][i];
		if (terminalInfo->componentID == wireA.componentID &&
			terminalInfo->terminalNumber == wireA.terminalNumber &&
			terminalInfo->terminalType == wireA.terminalType) {
			connnectionGraph[wireA.componentID].erase(connnectionGraph[wireA.componentID].begin() + i);
			break;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		terminalInfo = &connnectionGraph[wireB.componentID][i];
		if (terminalInfo->componentID == wireB.componentID &&
			terminalInfo->terminalNumber == wireB.terminalNumber &&
			terminalInfo->terminalType == wireB.terminalType) {
			connnectionGraph[wireB.componentID].erase(connnectionGraph[wireB.componentID].begin() + i);
			break;
		}
	}

	return true;
}



/*
메모
그래프 객체를 필요한 받아와서 정해주기함
vector 로 하지만 일일이 찾아서 삭제 하지말고 그냥 다만들어놓고 하기


*/
/*윈프 과제 메모
갱신하는방법 bfs 돌려서 한다

//따로 검사함... 에러 처리해줌:
와이어 충돌은 와이어 내에서 처리.. wire 에서
->와이어에 인풋단자에 연결된 아웃풋 부품이 2개 인지 검사함
시작 인풋을 큐에 넣을떄 충돌되는 와이어는 체크해서
연결되지 않게 함
충돌하는 와이어에대한 정보를 저장하는 벡터를 만들어놓음
와이어 자체에 상태에 충돌상태를 추가한다

진동에러 잡는방법:
여러번 돌림?...
돌면서 사이클을 검사해버린다
.......
따로 경로 트리를 만들어서 사이클이 발생하면 중지 해버림?
..
->dfs를 돌린다?
경로를 dequeue에 저장 하고 돌린다
..

여러개의 정션된 와이어를 하나로 취급한다
와이어를 잘구성해야한다

갱신하는 함수안에서 순서
초기화
1 충돌되는 와이어를 검사한다
2 진동검사를 한다 진동하면 예외 발생
3 직접 갱신하는 함수돌린다




*/
bool CLibraryBox::updateCircuit()
{

	//와이어간에는 양뱡향이다
	//부품과 와이어간의 단방향으로감
	//와이어의 output 타입이단자에서 부품의 input 타입 단자로 연결하면 방향은 와이어에서 부품으로 
	//부품의 output 타입의 단자에서 와이어의 input 타입의 단자로 연결하면 방향은 부품에서 와이로 

	//만약 진동 회로 이면 멈추그만한다...

	//bfs 방식으로 한다
	std::queue<COMPONENT_ID> queue;
	std::vector< std::vector<bool> > componentValueVector;

	//값을 저장해놓음
	//필요한 사이즈 많큼 할당해놓음
	componentValueVector.resize(componentTypeVector.size());


	for (int i = 0; i < componentTypeVector.size(); i++) {




	}

	//시작점인 인풋핀의 component id 를 큐에다가 넣는다
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		queue.push(inputPinIDVector[i]);
	}


	//큐를 돌면서 부품들의 내부정보를 갱신한다
	while (queue.empty()) {




	}
	//탐색을 할떄 아웃풋 방향으로 들어가면 더 멈춤
	//또는 인풋으로 들어갔는데 나오는 아웃풋이 달라지면  달라지는 아웃풋에대해
	//큐에 추가한다
	//와이어는 인풋 아웃풋이 상관이없음

	//오큘레이션 디텍션 어떻게 해야함?


	return false;
}

void CLibraryBox::printstatus()
{
	printf("\n");
	printf("################################\n");
	printf("simultor status \n");
	printf("################################\n");

	//현재 들어있는 컴포넌트들을 과 상태값을 출력한다;

	for (int i = 0; i < componentTypeVector.size(); i++) {
		//없는거는 생략함
		if (componentTypeVector[i] == COMPONENT_TYPE_NONE){
			continue;
		}
		printf("componentID : %d component type: %d\n", i, componentTypeVector[i]);
		printf("component information:\n");
		//줄일때
		COMPONENT_CONENTION_INFO* info;
		printf("using terminal infoation:\n");
		for (int j = 0; j<connectedTerminalInfo[i].size(); j++) {
			info = &connectedTerminalInfo[i][j];
			printf("terminal type : %d  terminal number : %d\n", 
				info->terminalType, info->terminalNumber);
		}
		printf("connnected info\n");
		for (int j = 0; j<connnectionGraph[i].size(); j++) {
			info = &connnectionGraph[i][j];
			printf("connnected to component ID : %d, terminal type : %d	terminal number : %d\n",
				info->componentID, info->terminalType, info->terminalNumber);
		}
		printf("\n");
	}




	printf("################################\n");
	printf("end\n");
	printf("################################\n");
	printf("\n\n");
}


