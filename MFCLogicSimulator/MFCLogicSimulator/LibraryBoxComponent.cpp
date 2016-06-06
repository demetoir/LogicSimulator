#include "stdafx.h"
#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//컴포넌트를 담을벡터
	componentVector.resize(VECTOR_INIT_SIZE, NULL);
	//컴포넌트 타입을 저장하는 벡터
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//컴포넌트 아이디을 저장하는 
	componentIDVector.resize(VECTOR_INIT_SIZE, false);

	amIInsideBox = false;
	//연결하는 방향 그래프	
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
	//부품의 전체 갯수
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
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true) {
			delete componentVector[i];
		}
	}
}

//새로운 컴포넌트 아이디를 생성해줌
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	int ret = 0;
	for (int i = 1; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = true;
			componentTypeVector[i] = componentType;
			ret = i;
			break;
		}
	}
	if (ret == 0) {
		ret = componentIDVector.size();
		componentIDVector.push_back(true);
		componentTypeVector.resize(componentIDVector.size());
		componentTypeVector[ret] = componentType;		
	}
	return ret;
}

//컴포넌트 아이디를 삭제함
void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentTypeVector[deleteId] = COMPONENT_TYPE_NONE;
	componentIDVector[deleteId] = false;
}


bool CLibraryBox::loadLibraryBoxData(LIBRARY_BOX_DATA & libraryBoxData)
{	


	//그래프 정보를 로드함
	inputGraph.resize(libraryBoxData.inputGraph.size());
	for (int i = 0; i < libraryBoxData.inputGraph.size(); i++) {
		inputGraph[i].resize(libraryBoxData.inputGraph[i].size());
		for (int j = 0; j < libraryBoxData.inputGraph[i].size(); j++) {
			inputGraph[i][j].componentID  = libraryBoxData.inputGraph[i][j].componentID;
			inputGraph[i][j].terminalNumber = libraryBoxData.inputGraph[i][j].terminalNumber;
			inputGraph[i][j].terminalType = libraryBoxData.inputGraph[i][j].terminalType;
		}
	}
	outputGraph.resize(libraryBoxData.outputGraph.size());
	for (int i = 0; i < libraryBoxData.outputGraph.size(); i++) {
		outputGraph[i].resize(libraryBoxData.outputGraph[i].size());
		for (int j = 0; j < libraryBoxData.outputGraph[i].size(); j++) {
			outputGraph[i][j].componentID = libraryBoxData.outputGraph[i][j].componentID;
			outputGraph[i][j].terminalNumber = libraryBoxData.outputGraph[i][j].terminalNumber;
			outputGraph[i][j].terminalType = libraryBoxData.outputGraph[i][j].terminalType;
		}
	}

	int curLibboxInfo = 0;
	//부품들의 ID와 부품의 타입으로 라이브러리 박스에 추가한다.
	//먼저 쓰지 않는 ID를 못쓰게 막아놓는다
	COMPONENT_INFO loadInfo;
	componentIDVector.resize(libraryBoxData.componentIDVector.size());
	componentTypeVector.resize(libraryBoxData.componentIDVector.size());
	for (int i = 0; i < libraryBoxData.componentIDVector.size(); i++) {
		if (libraryBoxData.componentIDVector[i] == false) {
			componentIDVector[i] = true;
		}
		else {
			loadInfo.componentID = 0;
			loadInfo.componentType = libraryBoxData.componentTypeVector[i];
			//라이브러리 박스일경우 따로 추가함
			if (loadInfo.componentType == COMPONENT_TYPE_LIBRARY_BOX) {
				addComponent(loadInfo, libraryBoxData.internalLibraryBoxData[curLibboxInfo]);
				curLibboxInfo += 1;
				((CLibraryBox*)componentVector[i])->amIInsideBox = true;
			}
			else {
				addComponent(loadInfo);
			}
		}
	}
	//막아놓은 ID를 해제함
	for (int i = 0; i < libraryBoxData.componentIDVector.size(); i++) {
		if (libraryBoxData.componentIDVector[i] == false) {
			componentIDVector[i] = false;
		}
	}

	isOscillation = false;
	isLibraryBoxOutputValueChanged = false;

	//라이브러리 박스의 인풋핀과 아웃풋 핀 clock핀을 저장하는 벡터 리스트
	inputPinIDVector.resize(libraryBoxData.inputPinIDVector.size(),0);
	for (int i = 0; i < libraryBoxData.inputPinIDVector.size(); i++) {
		inputPinIDVector[i] = libraryBoxData.inputPinIDVector[i];
	}
	outputPinIDVector.resize(libraryBoxData.outputPinIDVector.size(), 0);
	for (int i = 0; i < libraryBoxData.outputPinIDVector.size(); i++) {
		outputPinIDVector[i] = libraryBoxData.outputPinIDVector[i];
	}
	inputClockVector.resize(libraryBoxData.inputClockVector.size(), 0);
	for (int i = 0; i < libraryBoxData.inputClockVector.size(); i++) {
		inputClockVector[i] = libraryBoxData.inputClockVector[i];
	}
	return true;
}

//라이브러리 박스를 저장함
bool CLibraryBox::saveLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData)
{


	//라이브러리 박스의 인풋핀과 아웃풋 ,clock핀을 저장
	libraryBoxData.inputPinIDVector.resize(inputPinIDVector.size());
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		libraryBoxData.inputPinIDVector[i] = inputPinIDVector[i];
	}
	libraryBoxData.outputPinIDVector.resize(outputPinIDVector.size());
	for (int i = 0; i < outputPinIDVector.size(); i++) {
		libraryBoxData.outputPinIDVector[i] = outputPinIDVector[i];
	}
	libraryBoxData.inputClockVector.resize(inputClockVector.size());
	for (int i = 0; i < inputClockVector.size(); i++) {
		libraryBoxData.inputClockVector[i] = inputClockVector[i];
	}

	//부품간의 그래프를 저장함
	libraryBoxData.inputGraph.resize(inputGraph.size());
	for (int i = 0; i < inputGraph.size(); i++) {
		libraryBoxData.inputGraph[i].resize(inputGraph[i].size());
		for (int j = 0; j < inputGraph[i].size(); j++) {
			libraryBoxData.inputGraph[i][j].componentID = inputGraph[i][j].componentID;
			libraryBoxData.inputGraph[i][j].terminalNumber = inputGraph[i][j].terminalNumber;
			libraryBoxData.inputGraph[i][j].terminalType = inputGraph[i][j].terminalType;
		}
	}
	libraryBoxData.outputGraph.resize(outputGraph.size());
	for (int i = 0; i < outputGraph.size(); i++) {
		libraryBoxData.outputGraph[i].resize(outputGraph[i].size());
		for (int j = 0; j < outputGraph[i].size(); j++) {
			libraryBoxData.outputGraph[i][j].componentID = outputGraph[i][j].componentID;
			libraryBoxData.outputGraph[i][j].terminalNumber = outputGraph[i][j].terminalNumber;
			libraryBoxData.outputGraph[i][j].terminalType = outputGraph[i][j].terminalType;
		}
	}

	//부품들이 가지는 타입을 저장
	libraryBoxData.componentTypeVector.resize(componentTypeVector.size());
	for (int i = 0; i < componentTypeVector.size(); i++) {
		libraryBoxData.componentTypeVector[i] = componentTypeVector[i];
	}

	//부품들의 아이디를 저장
	libraryBoxData.componentIDVector.resize(componentIDVector.size());
	for (int i = 0; i < componentIDVector.size(); i++) {
		libraryBoxData.componentIDVector[i] = componentIDVector[i];
	}

	//내부 라이브러리 박스 의 정보를 저장함
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true && componentTypeVector[i] == COMPONENT_TYPE_LIBRARY_BOX) {
			LIBRARY_BOX_DATA libData;
			//내부 라이브러리 박스 정보를 libdata에 저장함
			((CLibraryBox*)componentVector[i])->saveLibraryBoxData(libData);
			//저장할 데이터 에 집어넣음
			libraryBoxData.internalLibraryBoxData.push_back(libData);
		}
	}
	return true;
}

bool CLibraryBox::getComponentOutputValue(COMPONENT_ID ID, int index)
{
	return componentVector[ID]->getOutputValue(index);
}

bool CLibraryBox::checkOscillation()
{
	return isOscillation;
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
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentVector[newComponentID] = new COneBitSwitchComponent();
		break;
	case COMPONENT_TYPE_CLOCK:
		inputClockVector.push_back(newComponentID);
		componentVector[newComponentID] = new CClockComponent();
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
		break;

		//output component
	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentVector[newComponentID] = new COneBitLampComponent();
		break;
	case COMPONENT_TYPE_7SEGMENT:
		componentVector[newComponentID] = new C7SegmentComponent();
		break;

		//지원하는 종류의 부픔이 아님 
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

bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo, LIBRARY_BOX_DATA & libBoxdata)
{
	//라이브러리 박스 가 아닐경우
	if (componentInfo.componentType != COMPONENT_TYPE_LIBRARY_BOX) {
		return false;
	}

	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;
	COMPONENT_CONENTION_INFO empty;

	//아이디를 할당해줌
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//부품들의 저장할공간을 늘려줌
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 3);
	}

	//라이브러리 부품을 할당하고 정보를 로드함
	componentVector[newComponentID] = new CLibraryBox();
	((CLibraryBox*)componentVector[newComponentID])->loadLibraryBoxData(libBoxdata);


	if (inputGraph.size() <= newComponentID) {
		inputGraph.resize(inputGraph.size() + 3);
	}
	inputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfInput(), empty);
	
	if (outputGraph.size() <= newComponentID) {
		outputGraph.resize(outputGraph.size() + 3);
	}
	outputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfOutput(), empty);
	
	if (componentTypeVector.size() <= newComponentID) {
		componentTypeVector.resize(componentTypeVector.size() + 3);
	}
	componentTypeVector[newComponentID] = newComponentType;

	//부품수 증가함
	numberOfComponent += 1;

	//자기가 안에 있는건지 구분하기
	((CLibraryBox*)componentVector[newComponentID])->amIInsideBox = true;

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
		if (info->componentID <= 0) { continue; }
		outputGraph[info->componentID][info->terminalNumber].componentID = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}
	//지울부품의 아웃풋단자에 연결된 부풉의 간선을 제거함
	for (int i = 0; i < outputGraph[_componentID].size(); i++) {
		info = &outputGraph[_componentID][i];
		if (info->componentID <= 0) { continue; }
		inputGraph[info->componentID][info->terminalNumber].componentID = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}

	//지워지는 부품의 그래프와 터미널 정보를 갱신함
	COMPONENT_CONENTION_INFO deleteinfo;
	inputGraph[_componentID].clear();
	outputGraph[_componentID].clear();

	//input pin 또는 output pin ,clock 이면 각각의 핀벡터에서 삭제한다
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
			if (outputPinIDVector[i] == _componentID) {
				outputPinIDVector.erase(outputPinIDVector.begin() + i);
				break;
			}
		}
	}
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_CLOCK) {
		for (int i = 0; i < inputClockVector.size(); i++) {
			if (inputClockVector[i] == _componentID) {
				inputClockVector.erase(inputClockVector.begin() + i);
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


bool CLibraryBox::connnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB)
{
	
	//올바르지 않은 연결
	if (isPossibleConnection(componentA, componentB) == false) {
		return false;
	 }

	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;
	if (componentA.terminalType == TERMINAL_TYPE_INPUT &&
		componentB.terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB.componentID;
		A.terminalNumber = componentB.terminalNumber;
		A.terminalType = componentB.terminalType;
		B.componentID = componentA.componentID;
		B.terminalNumber = componentA.terminalNumber;
		B.terminalType = componentA.terminalType;;
	}
	else {
		B.componentID = componentB.componentID;
		B.terminalNumber = componentB.terminalNumber;
		B.terminalType = componentB.terminalType;
		A.componentID = componentA.componentID;
		A.terminalNumber = componentA.terminalNumber;
		A.terminalType = componentA.terminalType;;
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

bool CLibraryBox::disconnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	////A->B 로가는거
	//output -> input
	if (componentA.terminalType == TERMINAL_TYPE_INPUT &&
		componentB.terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB.componentID;
		A.terminalNumber = componentB.terminalNumber;
		A.terminalType = componentB.terminalType;
		B.componentID = componentA.componentID;
		B.terminalNumber = componentA.terminalNumber;
		B.terminalType = componentA.terminalType;;
	}
	else {
		B.componentID = componentB.componentID;
		B.terminalNumber = componentB.terminalNumber;
		B.terminalType = componentB.terminalType;
		A.componentID = componentA.componentID;
		A.terminalNumber = componentA.terminalNumber;
		A.terminalType = componentA.terminalType;;
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

	////게이트와 게이트를 분리하려 할떄 또는
	////줄과 줄을 분리하려 할때
	//if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
	//	componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
	//	(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
	//		componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
	//	return false;
	//}

	//존재 하지 않는 단자에 분리하려할때
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//이미 연결한 단자에 또 분리하려 할떄
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		inputGraph[B.componentID][B.terminalNumber].componentID == -1) {
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
	int nextID;
 	queue< pair< int, int > > Q;
	vector<int> checktime;
	checktime.resize(componentIDVector.size(), 0);
	vector<int> countCheck;
	countCheck.resize(componentIDVector.size(), 0);
	int time = 0;
	CComponentObject* curComponent;
	COMPONENT_CONENTION_INFO preConectionInfo;	

	//부품들을 큐에다가 집어넣음	
	for (int i = 1; i < componentIDVector.size(); i++) {
		//존재하지 않는 부품일때 넘어간다
		if (componentIDVector[i] == false) { continue; }
		int curID = i;
	
		bool isCanPushToQueue = false;
		//현재 선택 한부품에  output 으로 이어진게 하나도 없을떄 넘어간다
		for (int j = 0; j < componentVector[curID]->numberOfOutput(); j++) {
			if (outputGraph[curID][j].componentID != -1) {
				isCanPushToQueue = true;
				break;
			}
		}

		//큐에다가 집어넣음
		if (isCanPushToQueue == true) { 
			Q.push(make_pair(time, curID));
			checktime[curID] = time;
			countCheck[curID] += 1;
			time += 1;	
		}

	}	

	int curtime, curID, preID, preTerminalNumber;
	while (!Q.empty()) {		
		curtime = Q.front().first;
		curID = Q.front().second;
		Q.pop();

		//최근의 정보가 아닐떄 그냥 넘김
		if (checktime[curID] > curtime) { continue; }

		//진동이 발생하엿다.
		if (countCheck[curID] >= LOOP_LIMIT) {
			isOscillation = true;
			return true;
		}
		//시간은 흐른다
		time += 1;
		if (amIInsideBox == false) {
			//printf("cur ID :%d cur type : %d time : %d \n", curID, componentTypeVector[curID], curtime);
		}

		//현재 부품 객체
		curComponent = componentVector[curID];

		//현재 부품의 값을 갱신함
		bool val = false;
		bool isUpdated = false;
		//갱신해도 달라지지 않으면 넘어감
		for (int i = 0; i < curComponent->numberOfInput(); i++) {
			//현재 부품으로 들어가는 값을 구함
			preID = inputGraph[curID][i].componentID;

			//현재부품에 지금 단자에 연결된게 없을떄
			if (preID == -1) {
				val = false;
			}
			//연결된것이있으면 거기서 값을 가져옴
			else {
				preTerminalNumber = inputGraph[curID][i].terminalNumber;
				val = componentVector[preID]->getOutputValue(preTerminalNumber);
			}			

			//들어가는 부품으로 값이 바뀌는지 검사함
			if (curComponent->setInputValue(i, val)) {
				isUpdated = true;
			}
		}
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

				//다음 부품이 없을떄
				if (nextID == -1) {
					continue;
				}

				if (amIInsideBox == false) {
					//printf("##cur ID :%d nextID : %d\n", curID, nextID);
				}
				Q.push(make_pair(time, nextID));
				checktime[nextID] = time;
				countCheck[nextID] += 1;
				time += 1;
			}
		}
	}

	return isLibraryBoxOutputValueChanged;
}

int CLibraryBox::numberOfInput()
{
	return (int)inputPinIDVector.size();
}

int CLibraryBox::numberOfOutput()
{
	return (int)outputPinIDVector.size();
}

bool CLibraryBox::setInputValue(int index, bool _value)
{
	bool val = componentVector[inputPinIDVector[index]]->setInputValue(0,_value);
	if (amIInsideBox == true) {
		update();
	}
	return val;
}

bool CLibraryBox::getInputValue(int index)
{
	return componentVector[inputPinIDVector[index]]->getInputValue(0);
}

bool CLibraryBox::getOutputValue(int index)
{
	return componentVector[outputPinIDVector[index]]->getOutputValue(0);
}

bool CLibraryBox::update()
{
	updateCircuit();
	return isOscillation;
}

void CLibraryBox::reset()
{
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == false) { continue; }
		componentVector[i]->reset();
	}
	isOscillation = false;
}

bool CLibraryBox::setClockValue(int index, bool _value)
{
	componentVector[inputClockVector[index]]->setInputValue(0,_value);
	if (amIInsideBox == true) {
		update();
	}
	return false;
}

bool CLibraryBox::getClockValue(int index)
{
	return componentVector[inputClockVector[index]]->getOutputValue(0);
}

int CLibraryBox::numberOfClock()
{
	return (int)inputClockVector.size();
}

CComponentObject * CLibraryBox::getComponentObject(int index)
{
	return componentVector[index];
}

bool CLibraryBox::isPossibleConnection(COMPONENT_CONENTION_INFO & componentA, COMPONENT_CONENTION_INFO & componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	copyCOMPONENT_CONENTION_INFO(componentA, A);
	copyCOMPONENT_CONENTION_INFO(componentB, B);

	////A->B 로가는거
	//output -> input
	if (A.terminalType == TERMINAL_TYPE_INPUT &&
		B.terminalType == TERMINAL_TYPE_OUTPUT) {
		swapCOMPONENT_CONENTION_INFO(A, B);
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
	//if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
	//	componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
	//	(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
	//		componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
	//	return false;
	//}

	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ) {
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

	return true;
}

void CLibraryBox::swapCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO & A, COMPONENT_CONENTION_INFO & B)
{
	COMPONENT_CONENTION_INFO temp;
	copyCOMPONENT_CONENTION_INFO(A, temp);
	copyCOMPONENT_CONENTION_INFO(B, A);
	copyCOMPONENT_CONENTION_INFO(temp, B);
}

void CLibraryBox::copyCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO & source, COMPONENT_CONENTION_INFO & destination)
{
	destination.componentID = source.componentID;
	destination.terminalType = source.terminalType;
	destination.terminalNumber = source.terminalNumber;
}

ADJ_LIST* CLibraryBox::getOutputGrahp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return &outputGraph;
}

ADJ_LIST * CLibraryBox::getInputGrahp()
{
	return &inputGraph;
}

void CLibraryBox::deleteObject()
{
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true) {
			deleteComponent(i);
		}
	}
}

void CLibraryBox::setOffOscillation()
{
	isOscillation = false;
}
