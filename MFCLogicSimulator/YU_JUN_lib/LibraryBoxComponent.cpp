#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//컴포넌트를 담을벡터
	componentVector.resize(VECTOR_INIT_SIZE, NULL);



	//컴포넌트 타입을 저장하는 벡터
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//컴포넌트 아이디을 저장하는 
	componentIDVector.resize(VECTOR_INIT_SIZE, false);

	//연결하는 방향 그래프	
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
	numberOfComponent = 0;
	isOscillation = false;
	isLibraryBoxOutputValueChanged = false;

}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{

}

CLibraryBox::~CLibraryBox()
{
	//동적 할당되는 부분을 모두 해제함
	for (int i = 0; i < componentVector.size(); i++) {
		if (componentIDVector[i] == true) {
			delete componentVector[i];
		}
	}
}

//새로운 컴포넌트 아이디를 생성해줌
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	for (int i = 1; i < componentTypeVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = true;
			componentTypeVector[i] = componentType;
			return i;
		}
	}
	componentIDVector.push_back(true);
	componentTypeVector.push_back(componentType);
	return (int)(componentTypeVector.size() - 1);
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
	return componentVector[inputPinID]->getInputValue(0);
	return false;
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = outputPinIDVector[_outPutPinNumber];
 	return componentVector[outputPinID]->getOutputValue(0);
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
	if (inputGraph.size() <= newComponentID) {
		inputGraph.resize(inputGraph.size() + 3);
	}
	if (outputGraph.size() <= newComponentID) {
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
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		break;

	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///대충...
		break;

		//output component

	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
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

	inputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfInput(), empty);
	outputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfOutput(), empty);
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
	delete componentVector[_componentID];
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
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
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
	if (outputGraph[A.componentID][A.terminalNumber].componentID != -1 ||
		inputGraph[B.componentID][B.terminalNumber].componentID != -1) {
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




bool CLibraryBox::updateCircuit()
{
	if (isOscillation == true) {
		return false;
	}

 	queue< pair< int, int > > Q;

	vector<int> checktime;
	vector<int> countCheck;
	checktime.resize(componentIDVector.size(), 0);
	countCheck.resize(componentIDVector.size(), 0);
	int time = 0;
	int countLimit = 1000;
	CComponentObject* curComponent;
	CComponentObject* preComponent;
	COMPONENT_CONENTION_INFO preConectionInfo;

	//시작점이 될 부품을 큐에다가 집어넣음
	int nextID;
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		nextID = outputGraph[inputPinIDVector[i]][0].componentID;
		if (nextID == -1) {
			continue;
		}
		Q.push(make_pair(time, nextID));
		
		
		checktime[inputPinIDVector[i]] = time;
		countCheck[inputPinIDVector[i]] += 1;

		time += 1;
	}

	int curtime, curID, preID, preTerminalNumber;
	while (!Q.empty()) {
		
		curtime = Q.front().first;
		curID = Q.front().second;
		Q.pop();
		//최근의 정보가 아닐떄 그냥 넘김
		if (checktime[curID] > curtime) { continue; }

		//진동이 발생하엿다.
		if (countCheck[curID] >= countLimit) {
			isOscillation = true;
			return true;

		}
		//시간은 흐른다
		time += 1;
		

		//현재 부품의 값을 갱신함
		curComponent = componentVector[curID];
		bool val = false;
		bool isUpdated = false;
		//갱신해도 달라지지 않으면 넘어감
		for (int i = 0; i < curComponent->numberOfInput(); i++) {
			//현재 부품으로 들어가는 값을 구함
			preID = inputGraph[curID][i].componentID;
			preTerminalNumber = inputGraph[curID][i].terminalNumber;
			val = componentVector[preID]->getOutputValue(preTerminalNumber);

			//들어가는 부품으로 값이 바뀌는지 검사함
			if (curComponent->setInputValue(i, val)) {
				isUpdated = true;
			}
		}



		//다른값이 들어오면 다른 부품으로 전달함
		//output 값이 바뀌면 출력으로 나가는 부품을 큐에 집어넣음
		
		if (isUpdated == true) {
			// 아웃풋 핀의 값이 달라짐 
			if (componentTypeVector[curID] == COMPONENT_TYPE_OUTPUT_PIN) {
				isLibraryBoxOutputValueChanged = true;
				continue;
			}
			//다음 부품으로 넘어감
			for (int i = 0; i < curComponent->numberOfOutput(); i++) {
				nextID = outputGraph[curID][i].componentID;				
				if (nextID == -1) {
					continue;
				}
				
				Q.push(make_pair(time, nextID));
				checktime[inputPinIDVector[i]] = time;
				countCheck[inputPinIDVector[i]] += 1;

				time += 1;
			}
		}
	}

	return isLibraryBoxOutputValueChanged;
}

int CLibraryBox::numberOfInput()
{
	return inputPinIDVector.size();
}

int CLibraryBox::numberOfOutput()
{
	return (int)outputPinIDVector.size();
}

bool CLibraryBox::setInputValue(int index, bool _value)
{
	componentVector[inputPinIDVector[index]]->setInputValue(0,_value);
	return false;
}

bool CLibraryBox::getInputValue(int index)
{
	return false;
}

bool CLibraryBox::getOutputValue(int index)
{
	return false;
}

bool CLibraryBox::update()
{
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


