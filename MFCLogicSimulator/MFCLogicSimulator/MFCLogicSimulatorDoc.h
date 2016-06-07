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

// MFCLogicSimulatorDoc.h : CMFCLogicSimulatorDoc 클래스의 인터페이스
//


#pragma once
#include "MainFrm.h"
#include "LibraryBoxComponent.h"
class CMainFrame;
using std::vector;
using std::pair;
using std::make_pair;
#define DEFAULT_VALUE_ADDING_COMPONENT_DIRECTION EAST 

enum LIBRARYBOX_TYPE {
	LIBRARYBOX_TYPE_NONE,
	LIBRARYBOX_TYPE_NAND,
	LIBRARYBOX_TYPE_NOR,
	LIBRARYBOX_TYPE_TFF, 
	LIBRARYBOX_TYPE_JKFF,
	LIBRARYBOX_TYPE_DFF,
	LIBRARYBOX_TYPE_USER_DEFINE
};

enum COMPONENT_DIRECTION {
	EAST,SOUTH,WEST,NORTH
};

//도큐먼트에서 사용할 부품정보 구조체
struct COMPONENT_DATA {
	COMPONENT_DATA() {
		x = 0;
		y = 0;
		id = -1;
		type = COMPONENT_TYPE_NONE;
		direction = EAST;	
		label = "";
		hz = 10;
		clockEdge = true;
		libraryBoxType = LIBRARYBOX_TYPE_NONE;
	}
	//가장 왼쪽 위 의 기준 좌표
	int x,y;
	int hz;
	BOOL clockEdge;
	COMPONENT_ID id;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CString label;
	LIBRARYBOX_TYPE libraryBoxType;
};

enum TOOLBOX_ITEM_TYPE {
	FOLDER_ROOT,
	FOLDER_WIRE,
	ITEM_WIRE, ITEM_PIN, ITEM_PROBE,
	FOLDER_GATE,
	ITEM_AND, ITEM_NAND, ITEM_OR,
	ITEM_NOR, ITEM_XOR, ITEM_NOT,
	FOLDER_FF,
	ITEM_DFF, ITEM_JKFF, ITEM_TFF,
	FOLDER_INPUT,
	ITEM_1BITBUTIN, ITEM_CLOCK,
	FOLDER_OUTPUT,
	ITEM_1BITBUTOUT, ITEM_7SEGMENT,
	ITEM_LIBRARYBOX
};

enum OPERATION_MODE {
	OPERATION_MODE_NONE,
	OPERATION_MODE_ADDING_COMPONENT,
	OPERATION_MODE_SELECT_COMPONENT,
	OPERATION_MODE_CONNECTING_COMPONENT,
	OPERATION_MODE_VAlUE_CHANGE,
	OPERATION_MODE_SELECT_WIRE
};



class CMFCLogicSimulatorDoc : public CDocument
{
	protected: // serialization에서만 만들어집니다.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual ~CMFCLogicSimulatorDoc();

public : 
	//엔진을 저장할 변수
	CLibraryBox logicSimulatorEngine;
	//엔진 데이터들
	LIBRARY_BOX_DATA engineCoreData;
	//뷰에서 사용되어질 정보들
	vector <COMPONENT_DATA> engineComponentData;
	vector<int > toolboxItemData;

	LIBRARY_BOX_DATA nandGateData;
	LIBRARY_BOX_DATA norGateData;

	//트리뷰에서 선택한 부품정보
	int currentSelectedItemIndex;
	bool isRunningMode;
	int selectedComponentID;
	bool isCurcuitOcillate;
	COMPONENT_CONENTION_INFO selectedconnectionInfoA;
	COMPONENT_CONENTION_INFO selectedconnectionInfoB;
	OPERATION_MODE operationMode;
	



	//부품을 추가한다
	int addComponentToEngine(int _x,int _y, int itemIndex);
	void deleteComponentToEngine(int id);


	//부품을 서로 연결한다
	bool connectComponent(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);
	//부품을 서로 연결해제한다
	void disconectComponent();

	int getSelectedItemIndexInToolBox(HTREEITEM hItem);
	//트리뷰에서 선택한 부품의 플래그로  COMPONENT_TYPE를 알아낸다
	COMPONENT_TYPE getComponentTypeByToolBoxItemIndex(int type);
	COMPONENT_TYPE getCurrentSelectedComponentType();
	LIBRARYBOX_TYPE getCurrentSelectedComponentlibraryBoxType();
	void getStringByCOMPONENT_DIRECTION(COMPONENT_DIRECTION direct, CString & CS);
	void getStringByCOMPONENT_TYPE(COMPONENT_TYPE compType, CString & CS);
	
	void make_NORGATE(CLibraryBox& box);
    void make_NANDGATE(CLibraryBox& box);		

	void storeEngineComponentData(CArchive& ar, vector <COMPONENT_DATA>* engineComponentData);
	void loadEngineComponentData(CArchive& ar, vector <COMPONENT_DATA>* engineComponentData);
	void storeEngineCoreData(CArchive& ar, LIBRARY_BOX_DATA& data);
	void loadEngineCoreData(CArchive& ar, LIBRARY_BOX_DATA& data);

	void storeEngineToolboxitemList(CArchive& ar, vector <int>* ToolboxitemList);
	void loadEngineToolboxitemList(CArchive& ar, vector <int>* ToolboxitemList);



	bool checkConnectionWireToWire(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);




#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()


};
