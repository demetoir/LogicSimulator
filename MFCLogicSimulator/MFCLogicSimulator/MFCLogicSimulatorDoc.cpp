// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCLogicSimulatorDoc.cpp : CMFCLogicSimulatorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"

#include <propkey.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLogicSimulatorDoc

IMPLEMENT_DYNCREATE(CMFCLogicSimulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCLogicSimulatorDoc, CDocument)
END_MESSAGE_MAP()


// CMFCLogicSimulatorDoc 생성/소멸


//문서를 만들면서 라이브러리 엔진을 넣는다
CMFCLogicSimulatorDoc::CMFCLogicSimulatorDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	engineComponentData.resize(10);
	operationMode = OPERATION_MODE_NONE;
	selectedComponentID = 0;
	isRunningMode = false;
	isCurcuitOcillate = false;


	CLibraryBox norGate;
	make_NANDGATE(norGate);
	norGate.saveLibraryBoxData(norGateData);

	CLibraryBox nandGate;
	make_NANDGATE(nandGate);
	nandGate.saveLibraryBoxData(nandGateData);
}

int CMFCLogicSimulatorDoc::getSelectedItemIndexInToolBox(HTREEITEM hItem)
{
	// mainframe에서 fileview의 트리 정보 조회
	// http://www.dreamy.pe.kr/zbxe/CodeClip/18117

	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileViewInDoc = p_MainFrm->getCFileView();
	CViewTree* p_ToolboxInDoc = p_FileViewInDoc->getCFileViewTree();

	int indexOfItem = 0;
	HTREEITEM hComp = p_ToolboxInDoc->GetChildItem(NULL);
	while (hComp)
	{
		if (hComp == hItem) break;
		hComp = p_ToolboxInDoc->GetNextItem(hComp, TVGN_NEXTVISIBLE);
		++indexOfItem;
	}
	return indexOfItem;
}

CMFCLogicSimulatorDoc::~CMFCLogicSimulatorDoc()
{
}

BOOL CMFCLogicSimulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCLogicSimulatorDoc serialization

void CMFCLogicSimulatorDoc::Serialize(CArchive& ar)
{
	////엔진 데이터들
	//LIBRARY_BOX_DATA engineDumpData;
	////뷰에서 사용되어질 정보들
	//vector <COMPONENT_DATA> engineComponentData;

	//파일 이름을 얻는다
	CFile* pFile = ar.GetFile();
	CString fileName = pFile->GetFileName();

	if (ar.IsStoring())
	{
		//MessageBox(0, fileName, _T("store"), 0);
		// TODO: 여기에 저장 코드를 추가합니다.

		LIBRARY_BOX_DATA data;
		
		//데이터의 사이즈를 가져온다
		storeEngineComponentData(ar,&engineComponentData);
		logicSimulatorEngine.saveLibraryBoxData(data);
		storeEngineCoreData(ar,data);
		storeEngineToolboxitemList(ar, &toolboxItemData);
	}
	else
	{

		//MessageBox(0, fileName, _T("load"), 0);
		// TODO: 여기에 로딩 코드를 추가합니다.
		LIBRARY_BOX_DATA data;
		loadEngineComponentData(ar,&engineComponentData);
		loadEngineCoreData(ar,data);
		logicSimulatorEngine.loadLibraryBoxData(data);
		toolboxItemData.resize(engineComponentData.size());
		loadEngineToolboxitemList(ar, &toolboxItemData);

	}
}



int CMFCLogicSimulatorDoc::addComponentToEngine(int _x, int _y, int ToolBoxItemIndex)
{
	COMPONENT_TYPE selectedType = getComponentTypeByToolBoxItemIndex(ToolBoxItemIndex);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CFileView *pFileView = (CFileView*)pFrame->getCFileView();
	CString str;
	COMPONENT_INFO addingComponentInfo(selectedType);
	int ret = 0;
	if (selectedType == COMPONENT_TYPE_LIBRARY_BOX) {
		if (ToolBoxItemIndex == ITEM_DFF) {

		}
		else if (ToolBoxItemIndex == ITEM_JKFF) {

		}
		else if (ToolBoxItemIndex == ITEM_TFF) {

		}
		else if (ToolBoxItemIndex == ITEM_NOR) {
			ret = logicSimulatorEngine.addComponent(addingComponentInfo, norGateData);
		}
		else if (ToolBoxItemIndex == ITEM_NAND) {
			ret = logicSimulatorEngine.addComponent(addingComponentInfo, nandGateData);
		}
		//사용자 정의 라이브러리 박스일때
		else {
			LIBRARY_BOX_DATA userDefineLibraryboxCoreData;
			pFileView->getCoreData(userDefineLibraryboxCoreData, ToolBoxItemIndex - (ITEM_LIBRARYBOX+1));
			ret = logicSimulatorEngine.addComponent(addingComponentInfo, userDefineLibraryboxCoreData);
		}
	}
	else {
		ret = logicSimulatorEngine.addComponent(addingComponentInfo);
	}

	if (ret == false) {
		str.Format(_T("in mfc logicsimulator doc : add component fail -> not support component\n"),
			addingComponentInfo.componentID, selectedType, _x, _y);
		pOutput->addBuildWindowString(str);
		return -1;
	}


	//사이즈가 모자르면 확장한다
	if (addingComponentInfo.componentID >= engineComponentData.size()) {
		engineComponentData.resize(engineComponentData.size() + 10);
	}
	//도큐먼트 데이터에 집어넣는다
	engineComponentData[addingComponentInfo.componentID].id = addingComponentInfo.componentID;
	engineComponentData[addingComponentInfo.componentID].type = selectedType;
	engineComponentData[addingComponentInfo.componentID].x = _x;
	engineComponentData[addingComponentInfo.componentID].y = _y;
	engineComponentData[addingComponentInfo.componentID].direction = DEFAULT_VALUE_ADDING_COMPONENT_DIRECTION;
	CString label;
	label.Format(_T("ID :%d"), addingComponentInfo.componentID);
	engineComponentData[addingComponentInfo.componentID].label = label;
	
	if (addingComponentInfo.componentID >= toolboxItemData.size()) {
		toolboxItemData.resize(toolboxItemData.size() + 10);
	}
	toolboxItemData[addingComponentInfo.componentID] = ToolBoxItemIndex;


	if (selectedType == COMPONENT_TYPE_LIBRARY_BOX) {
		if (ToolBoxItemIndex == ITEM_DFF) {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_DFF;
			
		}
		else if (ToolBoxItemIndex == ITEM_JKFF) {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_JKFF;
		}
		else if (ToolBoxItemIndex == ITEM_TFF) {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_TFF;
		}
		else if (ToolBoxItemIndex == ITEM_NOR) {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_NOR;
		}
		else if (ToolBoxItemIndex == ITEM_NAND) {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_NAND;
			
		}
		//사용자 정의 라이브러리 박스일때
		else {
			engineComponentData[addingComponentInfo.componentID].libraryBoxType = LIBRARYBOX_TYPE_USER_DEFINE;
		}
	}
	
	str.Format(_T("in mfc logicsimulator doc : add component, ID : %d\n, type : %d (x,y) = (%d,%d),"),
		addingComponentInfo.componentID, selectedType, _x, _y);
	pOutput->addBuildWindowString(str);
	return addingComponentInfo.componentID;
}

void CMFCLogicSimulatorDoc::deleteComponentToEngine(int id)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	int ret;


	str.Format(_T("in CMFCLogicSimulatorDoc : delete component ID : %d\n"),
		id);
	pOutput->addBuildWindowString(str);
	ret = logicSimulatorEngine.deleteComponent(id);
	if (ret == true) { 
		str.Format(_T("in CMFCLogicSimulatorDoc : delete success\n")); 
		engineComponentData[id] = COMPONENT_DATA();
		operationMode = OPERATION_MODE_NONE;
		selectedComponentID = -1;
	}
	else { str.Format(_T("in CMFCLogicSimulatorDoc : delete fail\n")); }
	pOutput->addBuildWindowString(str);

	return;
}

bool CMFCLogicSimulatorDoc::connectComponent(COMPONENT_CONENTION_INFO & A, COMPONENT_CONENTION_INFO & B)
{
	bool AToBDirection;
	bool BToADirection;
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	bool ret = false;
	CString str;

	AToBDirection = logicSimulatorEngine.connnectComponent(A, B);
	if (AToBDirection == true) {
		str.Format(_T("in mfc logicsimulator doc : connect component ID : %d to ID: %d\n"),
			B.componentID, A.componentID);
		pOutput->addBuildWindowString(str);
		str.Format(_T("ID :%d type: %d terminal number : %d -> ID : %d type : %d terminal number : %d \n"),
			A.componentID, A.terminalType, A.terminalNumber,
			B.componentID, B.terminalType, B.terminalNumber);
		pOutput->addBuildWindowString(str);
		ret = true;
	}	
	
	BToADirection = logicSimulatorEngine.connnectComponent(B, A);
	if (BToADirection == true) {
		str.Format(_T("in mfc logicsimulator doc : connect component ID : %d to ID: %d\n"),
			B.componentID, A.componentID);
		pOutput->addBuildWindowString(str);
		str.Format(_T("ID :%d type: %d terminal number : %d -> ID : %d type : %d terminal number : %d \n"),
			B.componentID, B.terminalType, B.terminalNumber,
			A.componentID, A.terminalType, A.terminalNumber);
		pOutput->addBuildWindowString(str);
		ret = true;
	}
	
	if (ret == false) {
	str.Format(_T("in mfc logicsimulator doc : connect component fail\n"));
		pOutput->addBuildWindowString(str);
	}
	return ret;
}

void CMFCLogicSimulatorDoc::disconectComponent()
{	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;	
	int ret;
	if (operationMode == OPERATION_MODE_SELECT_WIRE) {
		str.Format(_T("in CMFCLogicSimulatorDoc : delete Connection \nID : %d terminal type :%d teminal number : %d <-> ID : %d terminal type :%d teminal number : %d\n"),
			selectedconnectionInfoA.componentID, selectedconnectionInfoA.terminalType,
			selectedconnectionInfoA.terminalNumber,
			selectedconnectionInfoB.componentID, selectedconnectionInfoB.terminalType,
			selectedconnectionInfoB.terminalNumber);
		pOutput->addBuildWindowString(str);
		ret = logicSimulatorEngine.disconnectComponent(selectedconnectionInfoA, selectedconnectionInfoB);
		if (ret == false) { str.Format(_T("in CMFCLogicSimulatorDoc : disconnection success\n")); }
		else { str.Format(_T("in CMFCLogicSimulatorDoc : disconnection fail\n")); }
		pOutput->addBuildWindowString(str);
		operationMode = OPERATION_MODE_NONE;
	}
	else {
		str.Format(_T("in CMFCLogicSimulatorDoc : wire is not selected\n"));
		pOutput->addBuildWindowString(str);
	}
	return ;
}

COMPONENT_TYPE CMFCLogicSimulatorDoc::getComponentTypeByToolBoxItemIndex(int type)
{
	COMPONENT_TYPE ret = COMPONENT_TYPE_LIBRARY_BOX;
	switch (type) {
	case FOLDER_ROOT:
		ret = COMPONENT_TYPE_NONE;
		break;
		//wire
	case  ITEM_WIRE:
		ret = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_PIN:
		ret = COMPONENT_TYPE_INPUT_PIN;
		break;
	case  ITEM_PROBE:
		ret = COMPONENT_TYPE_OUTPUT_PIN;
		break;

		//gate
	case  ITEM_AND:
		ret = COMPONENT_TYPE_AND_GATE;
		break;
	case  ITEM_OR:
		ret = COMPONENT_TYPE_OR_GATE;
		break;
	case  ITEM_XOR:
		ret = COMPONENT_TYPE_XOR_GATE;
		break;
	case  ITEM_NOT:
		ret = COMPONENT_TYPE_NOT_GATE;
		break;

		//input
	case  ITEM_1BITBUTIN:
		ret = COMPONENT_TYPE_ONE_BIT_SWITCH;
		break;
	case  ITEM_CLOCK:
		ret = COMPONENT_TYPE_CLOCK;
		break;

		//output
	case  ITEM_1BITBUTOUT:
		ret = COMPONENT_TYPE_ONE_BIT_LAMP;
		break;
	case  ITEM_7SEGMENT:
		ret = COMPONENT_TYPE_7SEGMENT;
		break;
	}
	return ret;
}

COMPONENT_TYPE CMFCLogicSimulatorDoc::getCurrentSelectedComponentType()
{
	COMPONENT_TYPE ret = getComponentTypeByToolBoxItemIndex(currentSelectedItemIndex);
	return ret;
}

LIBRARYBOX_TYPE CMFCLogicSimulatorDoc::getCurrentSelectedComponentlibraryBoxType()
{

	int type = getComponentTypeByToolBoxItemIndex(currentSelectedItemIndex);
	LIBRARYBOX_TYPE ret = LIBRARYBOX_TYPE_NONE;
	if (type != COMPONENT_TYPE_LIBRARY_BOX) {
		return ret;
	}
	if (currentSelectedItemIndex >= ITEM_LIBRARYBOX) {
		return LIBRARYBOX_TYPE_USER_DEFINE;
	}

	switch (currentSelectedItemIndex) {
	case ITEM_DFF:
		ret = LIBRARYBOX_TYPE_DFF;
		break;
		//wire
	case  ITEM_JKFF:
		ret = LIBRARYBOX_TYPE_JKFF;
		break;
	case  ITEM_TFF:
		ret = LIBRARYBOX_TYPE_TFF;
		break;
	case  ITEM_NOR:
		ret = LIBRARYBOX_TYPE_NOR;
		break;
	case  ITEM_NAND:
		ret = LIBRARYBOX_TYPE_NAND;
		break;
	}
	return ret;
}




void CMFCLogicSimulatorDoc::make_NANDGATE(CLibraryBox & box)
{
	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	//1
	box.addComponent(outputpin1);
	//2
	box.addComponent(wire2);
	//3
	box.addComponent(andgate);
	//4
	box.addComponent(wire3);
	//5
	box.addComponent(wire1);
	//6
	box.addComponent(notgate);
	//7
	box.addComponent(inputpin1);
	//8
	box.addComponent(inputpin2);
	//9
	box.addComponent(wire4);

	COMPONENT_CONENTION_INFO B, A;
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}
}

void CMFCLogicSimulatorDoc::make_NORGATE(CLibraryBox & box)
{
	COMPONENT_INFO andgate(COMPONENT_TYPE_OR_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(andgate);
	box.addComponent(wire3);
	box.addComponent(notgate);
	box.addComponent(wire4);
	box.addComponent(outputpin1);

	COMPONENT_CONENTION_INFO B, A;
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}
}




void CMFCLogicSimulatorDoc::storeEngineComponentData(CArchive & ar, vector <COMPONENT_DATA>* engineComponentData)
{
	COMPONENT_DATA *pData;
	int size = (*engineComponentData).size();
	ar << size;

	for (int i = 0; i < size; i++) {
		pData = &((*engineComponentData)[i]);
		ar << (int)(pData->x);
		ar << (int)(pData->y);
		ar << (int)(pData->clockEdge);
		ar << (int)(pData->hz);
		ar << (int)(pData->id);
		ar << pData->label;
		ar << (int)(pData->type);
		ar << (int)(pData->direction);
		ar << (int)(pData->libraryBoxType);
	}
	size = 0;
	
	return;
}

void CMFCLogicSimulatorDoc::loadEngineComponentData(CArchive & ar, vector <COMPONENT_DATA>* engineComponentData)
{
	COMPONENT_DATA *pData;
	int size;
	ar >> size;
	(*engineComponentData).resize(size);

	int enumTempValue;
	for (int i = 0; i < size; i++) {
		pData = &((*engineComponentData)[i]);
		ar >> pData->x;
		ar >> pData->y;
		ar >> pData->clockEdge;
		ar >> pData->hz;
		ar >> pData->id;
		ar >> pData->label;
		ar >> enumTempValue;
		pData->type = (COMPONENT_TYPE)enumTempValue;
		ar >> enumTempValue;
		pData->direction = (COMPONENT_DIRECTION)enumTempValue;
		ar >> enumTempValue;
		pData->libraryBoxType = (LIBRARYBOX_TYPE)enumTempValue;
	}
	size = 0;
	return;
}

void CMFCLogicSimulatorDoc::storeEngineCoreData(CArchive & ar, LIBRARY_BOX_DATA& data)
{


	int val;
	//vector < bool > componentIDVector;
	val = ((int)data.componentIDVector.size());
	ar << val;
	for (int i = 0; i < data.componentIDVector.size(); i++) {
		val = ((int)data.componentIDVector[i]);
		ar << val;
	}

	//vector< COMPONENT_ID > inputPinIDVector;
	val=((int)data.inputPinIDVector.size());
	ar << val; 
	for (int i = 0; i < data.inputPinIDVector.size(); i++) {
		val = ((int)data.inputPinIDVector[i]);
		ar << val;
	}

	//vector< COMPONENT_ID > outputPinIDVector;
	ar << (int)data.outputPinIDVector.size();
	for (int i = 0; i < data.outputPinIDVector.size(); i++) {
		ar << (int)data.outputPinIDVector[i];
	}
	//vector < COMPONENT_ID > inputClockVector;
	ar << (int)data.inputClockVector.size();
	for (int i = 0; i < data.inputClockVector.size(); i++) {
		ar << (int)data.inputClockVector[i];
	}

	//vector< COMPONENT_TYPE >  componentTypeVector;
	ar << (int)data.componentTypeVector.size();
	for (int i = 0; i < data.componentTypeVector.size(); i++) {
		ar << (int)data.componentTypeVector[i];
	}

	//vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	ar << (int)data.inputGraph.size();
	for (int i = 0; i < data.inputGraph.size(); i++) {
		ar << (int)data.inputGraph[i].size();
		for (int j = 0; j < data.inputGraph[i].size(); j++) {
			ar << (int)data.inputGraph[i][j].componentID;			
			ar << (int)data.inputGraph[i][j].terminalNumber;
			ar << (int)data.inputGraph[i][j].terminalType;
		}
	}

	//vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;
	ar << (int)data.outputGraph.size();
	for (int i = 0; i < data.outputGraph.size(); i++) {
		ar << (int)data.outputGraph[i].size();
		for (int j = 0; j < data.outputGraph[i].size(); j++) {
			ar << (int)data.outputGraph[i][j].componentID;			
			ar << (int)data.outputGraph[i][j].terminalNumber;
			ar << (int)data.outputGraph[i][j].terminalType;
		}
	}

	//vector < LIBRARY_BOX_DATA > internalLibraryBoxData;
	ar << (int)data.internalLibraryBoxData.size();
	for (int i = 0; i < data.internalLibraryBoxData.size(); i++) {
		storeEngineCoreData(ar, data.internalLibraryBoxData[i]);
	}
}

void CMFCLogicSimulatorDoc::loadEngineCoreData(CArchive & ar, LIBRARY_BOX_DATA& data)
{
	int enumTempValue;
	int size;

	//vector < bool > componentIDVector;
	size = 0;
	ar >> size;
	data.componentIDVector.resize(size);
	for (int i = 0; i < data.componentIDVector.size(); i++) {
		ar >> enumTempValue;
		data.componentIDVector[i] = enumTempValue;
	}

	//vector< COMPONENT_ID > inputPinIDVector;
	size = 0;
	ar >> size;
	data.inputPinIDVector.resize(size);
	for (int i = 0; i < data.inputPinIDVector.size(); i++) {
		ar >> enumTempValue;
		data.inputPinIDVector[i] = (COMPONENT_ID)enumTempValue;
	}

	//vector< COMPONENT_ID > outputPinIDVector;
	
	ar >> size;
	data.outputPinIDVector.resize(size);
	for (int i = 0; i < data.outputPinIDVector.size(); i++) {
		ar >> data.outputPinIDVector[i];
	}

	//vector < COMPONENT_ID > inputClockVector;
	ar >> size;
	data.inputClockVector.resize(size);
	for (int i = 0; i < data.inputClockVector.size(); i++) {
		ar >> data.inputClockVector[i];
	}

	//vector< COMPONENT_TYPE >  componentTypeVector;
	ar >> size; 
	data.componentTypeVector.resize(size);
	for (int i = 0; i < data.componentTypeVector.size(); i++) {
		ar >> enumTempValue;
		data.componentTypeVector[i] = (COMPONENT_TYPE)enumTempValue;
	}

	int ASize, BSize;
	//vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	ar >> ASize;
	data.inputGraph.resize(ASize);
	for (int i = 0; i < data.inputGraph.size(); i++) {
		ar >> BSize;
		data.inputGraph[i].resize(BSize);
		for (int j = 0; j < data.inputGraph[i].size(); j++) {
			ar >> data.inputGraph[i][j].componentID;			
			ar >> data.inputGraph[i][j].terminalNumber;
			ar >> enumTempValue;
			data.inputGraph[i][j].terminalType = (TERMINAL_TYPE)enumTempValue;
		}
	}

	//vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;
	ar >> ASize;
	data.outputGraph.resize(ASize);
	for (int i = 0; i < data.outputGraph.size(); i++) {
		ar >> BSize;
		data.outputGraph[i].resize(BSize);
		for (int j = 0; j < data.outputGraph[i].size(); j++) {
			ar >> data.outputGraph[i][j].componentID;
			ar >> data.outputGraph[i][j].terminalNumber;
			ar >> enumTempValue;
			data.outputGraph[i][j].terminalType = (TERMINAL_TYPE)enumTempValue;
		}
	}

	//vector < LIBRARY_BOX_DATA > internalLibraryBoxData;
	ar >> size;
	data.internalLibraryBoxData.resize(size);
	for (int i = 0; i < data.internalLibraryBoxData.size(); i++) {
		loadEngineCoreData(ar, data.internalLibraryBoxData[i]);
	}
}

void CMFCLogicSimulatorDoc::storeEngineToolboxitemList(CArchive & ar, vector<int>* ToolboxitemList)
{
	int Data;
	int size = (*ToolboxitemList).size();
	ar << size;

	for (int i = 0; i < size; i++) {
		Data = (*ToolboxitemList)[i];
		ar << Data;

	}
	size = 0;

	return;
}

void CMFCLogicSimulatorDoc::loadEngineToolboxitemList(CArchive & ar, vector<int>* ToolboxitemList)
{
	int Data;
	int size;
	ar >> size;
	(*ToolboxitemList).resize(size);
	for (int i = 0; i < size; i++) {
		ar >> Data;
		(*ToolboxitemList)[i] = Data;
	}
	size = 0;

	return;

}

bool CMFCLogicSimulatorDoc::checkConnectionWireToWire(COMPONENT_CONENTION_INFO & A, COMPONENT_CONENTION_INFO & B)
{
	//부품간 직접 연결하려고 할때
	if (A.terminalType != COMPONENT_TYPE_WIRE &&
		B.terminalType != COMPONENT_TYPE_WIRE) {
		
	}
	return false;
}


void CMFCLogicSimulatorDoc::getStringByCOMPONENT_TYPE(COMPONENT_TYPE compType, CString& CS)
{
	switch (compType) {
	case COMPONENT_TYPE_NONE:
		CS = _T("none");
		break;
	case COMPONENT_TYPE_INPUT_PIN:
		CS = _T("Input pin");
		break;
	case COMPONENT_TYPE_CLOCK:
		CS = _T("Clock");
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		CS = _T("One bit switch");
		break;
	case COMPONENT_TYPE_AND_GATE:
		CS = _T("AND");
		break;
	case COMPONENT_TYPE_OR_GATE:
		CS = _T("OR");
		break;
	case COMPONENT_TYPE_NOT_GATE:
		CS = _T("INVERTOR");
		break;
	case COMPONENT_TYPE_XOR_GATE:
		CS = _T("XOR");
		break;
	case COMPONENT_TYPE_WIRE:
		CS = _T("Wire");
		break;
	case COMPONENT_TYPE_7SEGMENT:
		CS = _T("7-Segment");
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		CS = _T("Output pin");
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		CS = _T("One bit lamp");
		break;
	case COMPONENT_TYPE_LIBRARY_BOX:
		CS = _T("Lib box");
		break;
	default:
		CS = _T("no exist type");
	}

}

void CMFCLogicSimulatorDoc::getStringByCOMPONENT_DIRECTION(COMPONENT_DIRECTION direct, CString & CS)
{
	switch (direct)
	{
	case EAST:
		CS = _T("East");
		break;
	case SOUTH:
		CS = _T("South");
		break;
	case WEST:
		CS = _T("West");
		break;
	case NORTH:
		CS = _T("North");
		break;
	default:
		CS = _T("No direction");
		break;
	}
}






#ifdef _DEBUG
void CMFCLogicSimulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCLogicSimulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCLogicSimulatorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCLogicSimulatorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCLogicSimulatorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}


#endif // SHARED_HANDLERS



