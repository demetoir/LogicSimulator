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

enum COMPONENT_DIRECTION {
	EAST,WEST,NORTH,SOUTH
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
	}
	//가장 왼쪽 위 의 기준 좌표
	int x,y;
	COMPONENT_ID id;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CString label;
	
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
	ITEM_ETC
};

enum OPERATION_MODE {
	OPERATION_MODE_NONE,
	OPERATION_MODE_ADDING_COMPONENT,
	OPERATION_MODE_SELECT_COMPONENT,
	OPERATION_MODE_CONNECTING_COMPONENT
};

class CMFCLogicSimulatorDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	CMainFrame m_MainFrmInDoc;
	CFileView m_FileViewInDoc;
	CViewTree m_FileViewTreeInDoc;
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCLogicSimulatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


public : 
	//엔진을 저장할 변수
	CLibraryBox logicSimulatorEngine;
	//엔진 데이터들
	LIBRARY_BOX_DATA engineDumpData;


	//뷰에서 사용되어질 정보들
	vector <COMPONENT_DATA> engineComponentData;

	//트리뷰에서 선택한 부품정보
	TOOLBOX_ITEM_TYPE currentSelectedItem;

	//부품을 추가한다
	bool addComponentToEngine(int _x,int _y);

	TOOLBOX_ITEM_TYPE getSelectedItemInToolBox(HTREEITEM hItem);

	//트리뷰에서 선택한 부품의 플래그로  COMPONENT_TYPE를 알아낸다
	COMPONENT_TYPE getComponentTypeByToolBoxItem(TOOLBOX_ITEM_TYPE type);

	COMPONENT_TYPE getCurrentSelectedComponentType();

	OPERATION_MODE operationMode;


};
