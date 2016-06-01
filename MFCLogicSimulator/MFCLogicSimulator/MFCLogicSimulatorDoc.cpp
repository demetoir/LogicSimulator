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
	currentSelectedItem = -1;
}

int CMFCLogicSimulatorDoc::itemSelectedInDoc()
{	
	// mainframe에서 fileview의 트리 정보 조회
	// http://www.dreamy.pe.kr/zbxe/CodeClip/18117

	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();

	CFileView* p_FileViewInDoc = p_MainFrm->getCFileView();

	CViewTree* p_ToolboxInDoc = p_FileViewInDoc->getCFileViewTree();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz
	int indexOfItem = 0;

	HTREEITEM hItem = p_ToolboxInDoc->GetSelectedItem();
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
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.


	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCLogicSimulatorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
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


bool CMFCLogicSimulatorDoc::addComponentToEngine(int _x, int _y)
{
	//부품 선택 모드가 아니면 거짓을 반환함
	if (currentSelectedItem < 1 ) {
		return false;
	}

	//부품선택 모드를 해제한다
	

	currentSelectedItem;
	engineComponentData;
	COMPONENT_TYPE selectedType; 

	//부품 타입을 알아낸다
	switch (currentSelectedItem ) {

		//wire
	case  ITEM_WIRE:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_PIN:
		selectedType = COMPONENT_TYPE_INPUT_PIN;
		break;
	case  ITEM_PROBE:
		selectedType = COMPONENT_TYPE_OUTPUT_PIN;
		break;

		//gate
	case  ITEM_AND:
		selectedType = COMPONENT_TYPE_AND_GATE;
		break;
	case  ITEM_NAND:
		selectedType = COMPONENT_TYPE_NAND_GATE;
		break;
	case  ITEM_OR:
		selectedType = COMPONENT_TYPE_OR_GATE;
		break;
	case  ITEM_NOR:
		selectedType = COMPONENT_TYPE_NOR_GATE;
		break;
	case  ITEM_XOR:
		selectedType = COMPONENT_TYPE_XOR_GATE;
		break;
	case  ITEM_NOT:
		selectedType = COMPONENT_TYPE_NOT_GATE;
		break;

		//flipflop
	case  ITEM_DFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_JKFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_TFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;

		//input
	case  ITEM_1BITBUTIN:
		selectedType = COMPONENT_TYPE_ONE_BIT_SWITCH;
		break;
	case  ITEM_CLOCK:
		selectedType = COMPONENT_TYPE_CLOCK;
		break;

		//output
	case  ITEM_1BITBUTOUT:
		selectedType = COMPONENT_TYPE_ONE_BIT_LAMP;
		break;
	case  ITEM_7SEGMENT:
		selectedType = COMPONENT_TYPE_7SEGMENT;
		break;


	case  ITEM_ETC:
		break;

	//만들수 없는 타입은 만들지 않고 거짓을 반환한다
	default :
		return false;
		break;
	}
	
	// 테스트 용
	COMPONENT_INFO addComponent;
	addComponent.componentType = selectedType;
	
	//지원하지 않는 목록일떼
	if (logicSimulatorEngine.addComponent(addComponent) == false) {
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		COutputWnd* pOutput = pFrame->getCOutputWnd();
		CString str;
		str.Format(_T("in mfc logicsimulator doc : add component fail -> not support component\n"),
			addComponent.componentID, selectedType, _x, _y);
		pOutput->addBuildWindowString(str);
		return false;
	}
	
	//사이즈가 모자르면 확장한다
	if (addComponent.componentID >= engineComponentData.size()) {
		engineComponentData.resize(engineComponentData.size() + 10);
	}
	//도큐먼트 데이터에 집어넣는다
	engineComponentData[addComponent.componentID].id = addComponent.componentID;
	engineComponentData[addComponent.componentID].type = selectedType;
	engineComponentData[addComponent.componentID].x = _x;
	engineComponentData[addComponent.componentID].y = _y;
	engineComponentData[addComponent.componentID].direction = EAST;
	engineComponentData[addComponent.componentID].label = "";
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	str.Format(_T("in mfc logicsimulator doc : add component, ID : %d\n, type : %d (x,y) = (%d,%d),"), 
		addComponent.componentID, selectedType,_x,_y);
	pOutput->addBuildWindowString(str);
	return true;
	

}

// CMFCLogicSimulatorDoc 진단

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


// CMFCLogicSimulatorDoc 명령