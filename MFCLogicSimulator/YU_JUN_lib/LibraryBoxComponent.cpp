#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//컴포넌트를 담을벡터
	componentVector.resize(VECTOR_INIT_SIZE,NULL);

	inputPinIDVector.resize(VECTOR_INIT_SIZE);
	outputPinIDVector.resize(VECTOR_INIT_SIZE);

	//컴포넌트 타입을 저장하는 벡터
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//컴포넌트 아이디을 저장하는 
	componentIDVector.resize(VECTOR_INIT_SIZE,false);

	//연결하는 방향 그래프	
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
	numberOfComponent = 0;
	isOscillation = false;
	
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
	return false;
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = inputPinIDVector[_outPutPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[outputPinID]);
	CInputPinComponent* outputPinObject = ((CInputPinComponent*)componentObject);
	return false;
}



// 부품 추가
bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo)
{
	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;

	COMPONENT_CONENTION_INFO empty;

	//아이디를 할당해줌
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//부품들의 저장할공간과 그래프의 용량을 더 추가 해야 할경우 확장함
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 3);
	}
	if (inputGraph.size() <= newComponentID){
		inputGraph.resize(inputGraph.size() + 3);
	}
	if (outputGraph.size()<=newComponentID){
		outputGraph.resize(outputGraph.size() + 3);
	}
	if (componentTypeVector.size() <= newComponentID) {
		componentTypeVector.resize(componentTypeVector.size() + 3);
	}

	switch (newComponentType)
	{
		// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new CInputPinComponent();
		
		inputGraph[newComponentID].resize(INPUT_PIN_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(INPUT_PIN_OUTPUT_SIZE, empty);
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		inputGraph[newComponentID].resize(ANDGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(ANDGATE_OUTPUT_SIZE, empty);
		printf("%d\n", componentVector[newComponentID]->getOutputValue());

		break;
	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		inputGraph[newComponentID].resize(ORGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(ORGATE_OUTPUT_SIZE, empty);
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		inputGraph[newComponentID].resize(NOTGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(NOTGATE_OUTPUT_SIZE, empty);
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		inputGraph[newComponentID].resize(XORGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(XORGATE_OUTPUT_SIZE, empty);
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///대충...
		inputGraph[newComponentID].resize(1, empty);
		outputGraph[newComponentID].resize(10, empty);
		break;

		//output component

	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		inputGraph[newComponentID].resize(OUTPUT_PIN_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(OUTPUT_PIN_OUTPUT_SIZE, empty);
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

	componentTypeVector[newComponentID] = newComponentType;
	numberOfComponent += 1;

	//생성 성공
	return true;
}

//부품 삭제일때
bool CLibraryBox::deleteComponent(COMPONENT_ID _componentID)
{
	//존재하지 않은 부품을 삭제하려고 하면 false 반환
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* info;
	//연결된 부품을 찾아서 연결된부품에서 지우려는 부품의 연결을 끊고 사용하는 단자를 갱신함
	//지울 부품의 인풋 단자에 연결된 부품의 간선을 제거함
	for (int i = 0; i < inputGraph[_componentID].size(); i++) {
		info = &inputGraph[_componentID][i];
		outputGraph[info->componentID][info->terminalNumber].componentID = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}
	//지울부품의 아웃풋단자에 연결된 부풉의 간선을 제거함
	for (int i = 0; i < outputGraph[_componentID].size(); i++) {
		info = &outputGraph[_componentID][i];
		inputGraph[info->componentID][info->terminalNumber].componentID = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}

	//지워지는 부품의 그래프와 터미널 정보를 갱신함
	COMPONENT_CONENTION_INFO deleteinfo;
	inputGraph[_componentID].resize(inputGraph[_componentID].size(), deleteinfo);
	outputGraph[_componentID].resize(outputGraph[_componentID].size(), deleteinfo);

	//input pin 또는 output pin 이면 각각의 핀벡터에서 삭제한다
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_INPUT_PIN) {
		for (int i = 0; i < inputPinIDVector.size(); i++) {
			if (inputPinIDVector[i] == _componentID) {
				inputPinIDVector.erase(inputPinIDVector.begin() + i);
				break;
			}
		}
	}
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_OUTPUT_PIN) {
		for (int i = 0; i < outputPinIDVector.size(); i++) {
			if (inputPinIDVector[i] == _componentID) {
				outputPinIDVector.erase(outputPinIDVector.begin() + i);
				break;
			}			
		}
	}
	
	componentTypeVector[_componentID] = COMPONENT_TYPE_NONE;
	//컴포넌트 아이디 삭제
	deleteComponentID(_componentID);

	numberOfComponent -= 1;
	return true;
}

bool CLibraryBox::connnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;
	
	////A->B 로가는거
	//output -> input
	if (componentA->terminalType == TERMINAL_TYPE_INPUT &&
		componentB->terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB->componentID;
		A.terminalNumber = componentB->terminalNumber;
		A.terminalType = componentB->terminalType;
		B.componentID = componentA->componentID;
		B.terminalNumber = componentA->terminalNumber;
		B.terminalType = componentA->terminalType;;
	}
	else {
		B.componentID = componentB->componentID;
		B.terminalNumber = componentB->terminalNumber;
		B.terminalType = componentB->terminalType;
		A.componentID = componentA->componentID;
		A.terminalNumber = componentA->terminalNumber;
		A.terminalType = componentA->terminalType;;
	}
	
	//같은 종류의 단자를 연결하려함
	if (A.terminalType == B.terminalType) {
		return false;
	}

	//존재하지 않는 부품을 연결하려 할떄
	if (A.componentID >= componentIDVector.size() ||
		componentIDVector[A.componentID] == false ||
		B.componentID >= componentIDVector.size() ||
		componentIDVector[B.componentID] == false) {
		return false;
	}

	//게이트와 게이트를 연결하려 할떄 또는
	//줄과 줄을 연결하려 할때
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) || 
		(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
			componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
		return false;
	}

	//존재 하지 않는 단자에 연결하려할때
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//이미 연결한 단자에 또 연결하려 할떄
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		outputGraph[B.componentID][B.terminalNumber].componentID == -1) {
		return false;
	}


	////A->B 로가는거
	//output -> input
	//방향 그래프 간선을 만들어줌
	inputGraph[B.componentID][B.terminalNumber].componentID = A.componentID;
	inputGraph[B.componentID][B.terminalNumber].terminalNumber = A.terminalNumber;
	inputGraph[B.componentID][B.terminalNumber].terminalType = A.terminalType;

	outputGraph[A.componentID][A.terminalNumber].componentID = B.componentID;
	outputGraph[A.componentID][A.terminalNumber].terminalNumber = B.terminalNumber;
	outputGraph[A.componentID][A.terminalNumber].terminalType = B.terminalType;


	return true;
}

bool CLibraryBox::disconnectComponent(COMPONENT_CONENTION_INFO * componentA, COMPONENT_CONENTION_INFO * componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	////A->B 로가는거
	//output -> input
	if (componentA->terminalType == TERMINAL_TYPE_INPUT &&
		componentB->terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB->componentID;
		A.terminalNumber = componentB->terminalNumber;
		A.terminalType = componentB->terminalType;
		B.componentID = componentA->componentID;
		B.terminalNumber = componentA->terminalNumber;
		B.terminalType = componentA->terminalType;;
	}
	else {
		B.componentID = componentB->componentID;
		B.terminalNumber = componentB->terminalNumber;
		B.terminalType = componentB->terminalType;
		A.componentID = componentA->componentID;
		A.terminalNumber = componentA->terminalNumber;
		A.terminalType = componentA->terminalType;;
	}

	//같은 종류의 단자를 분리하려함
	if (A.terminalType == B.terminalType) {
		return false;
	}

	//존재하지 않는 부품을 분리하려 할떄
	if (A.componentID >= componentIDVector.size() ||
		componentIDVector[A.componentID] == false ||
		B.componentID >= componentIDVector.size() ||
		componentIDVector[B.componentID] == false) {
		return false;
	}

	//게이트와 게이트를 분리하려 할떄 또는
	//줄과 줄을 분리하려 할때
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
		(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
			componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
		return false;
	}
	
	//존재 하지 않는 단자에 분리하려할때
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//이미 연결한 단자에 또 분리하려 할떄
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		outputGraph[B.componentID][B.terminalNumber].componentID == -1) {
		return false;
	}
	//A      -> B
	//output -> input
	inputGraph[B.componentID][B.terminalNumber].componentID = -1;
	inputGraph[B.componentID][B.terminalNumber].terminalNumber = -1;
	inputGraph[B.componentID][B.terminalNumber].terminalType = TERMINAL_TYPE_NONE;

	outputGraph[A.componentID][A.terminalNumber].componentID = -1;
	outputGraph[A.componentID][A.terminalNumber].terminalNumber = -1;
	outputGraph[A.componentID][A.terminalNumber].terminalType = TERMINAL_TYPE_NONE;
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




ishavecycle = false

def dfs(curV,inputvalue,terminalNumber):
global ishavecycle
//노드의 값을 갱신한다
component[curV].setvalue(inputvalue,terminalNumber)

//현재 노드가 줄이다
if component[curV] = WIRE:
int val = component[curV].getvalue()
for next in outG[curV]:
dfs(nextV,val,nextTerminal)
if isHaveCycle == True:
return

//현재 노드가 부품일때
else:
outputValue = component[curV].getvalue()
//상태를 검사한다
if ouputValue in map[curV]:
//사이클을 찾아냄
ishavecycle = True
retern
for next in outG[curV]:
val = component[curV].getval(currnetTerminal)
dfs(nextV,val,currnetTerminal)
if ishaveCycle == True:
return


return




*/
bool CLibraryBox::updateCircuit()
{
	if (isOscillation == true) {
		return false;
	}


	//와이어간에는 양뱡향이다
	//부품과 와이어간의 단방향으로감
	//와이어의 output 타입이단자에서 부품의 input 타입 단자로 연결하면 방향은 와이어에서 부품으로 
	//부품의 output 타입의 단자에서 와이어의 input 타입의 단자로 연결하면 방향은 부품에서 와이로 

	//만약 진동 회로 이면 멈추그만한다...

	//bfs 방식으로 한다
	//bfs 를 위한 queue
	//pair = (time,componentID)
	queue< pair< int, int > > Q;

	vector<int> checktime;
	checktime.resize(componentIDVector.size(), 0);
	int time = 0;
	int timeLimit = 123456;
	CComponentObject* curComponent;
	//시작점이 될 부품을 큐에다가 집어넣음
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		time += 1;
		Q.push(make_pair(time, inputPinIDVector[i]));
		checktime[inputPinIDVector[i]] = time;		
	}
	int curtime, curID;
	while (!Q.empty()) {
		
		curtime= Q.front().first;
		curID = Q.front().second;
		Q.pop();
		//최근의 정보가 아닐떄 그냥 넘김
		if (checktime[curID] > curtime) { continue; }
		
		//시간은 흐른다
		time += 1;
		

		//현재 부품의 값을 갱신함
		curComponent = componentVector[curID];

		//갱신해도 달라지지 않으면 넘어감

		//다른값이 들어오면 다른 부품으로 전달함



	}

	return false;
}

//
//void CLibraryBox::printstatus()
//{
//	printf("\n");
//	printf("################################\n");
//	printf("simultor status \n");
//	printf("################################\n");
//
//	//현재 들어있는 컴포넌트들을 과 상태값을 출력한다;
//
//	for (int i = 0; i < componentTypeVector.size(); i++) {
//		//없는거는 생략함
//		if (componentTypeVector[i] == COMPONENT_TYPE_NONE){
//			continue;
//		}
//		printf("componentID : %d component type: %d\n", i, componentTypeVector[i]);
//		printf("component information:\n");
//		//줄일때
//		COMPONENT_CONENTION_INFO* info;
//		printf("using terminal infoation:\n");
//		for (int j = 0; j<connectedTerminalInfo[i].size(); j++) {
//			info = &connectedTerminalInfo[i][j];
//			printf("terminal type : %d  terminal number : %d\n", 
//				info->terminalType, info->terminalNumber);
//		}
//		printf("connnected info\n");
//		for (int j = 0; j<connnectionGraph[i].size(); j++) {
//			info = &connnectionGraph[i][j];
//			printf("connnected to component ID : %d, terminal type : %d	terminal number : %d\n",
//				info->componentID, info->terminalType, info->terminalNumber);
//		}
//		printf("\n");
//	}
//
//
//
//
//	printf("################################\n");
//	printf("end\n");
//	printf("################################\n");
//	printf("\n\n");
//}


