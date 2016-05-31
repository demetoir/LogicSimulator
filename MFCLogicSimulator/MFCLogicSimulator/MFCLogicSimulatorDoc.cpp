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
	component_data.resize(10);
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

/*
int indexOfItem = 0;
CFileView* p_FileViewInDoc;
p_FileViewInDoc = (CFileView*) &m_FileViewInDoc;
ASSERT_VALID(p_FileViewInDoc);


HTREEITEM hItem = p_FileViewInDoc->getItemSelected();
HTREEITEM hComp = p_FileViewInDoc->getChildItem(NULL);

while (hComp)
{
if (hComp == hItem) break;
hComp = p_FileViewInDoc->getNextItem(hComp, TVGN_NEXT);
++indexOfItem;
}

switch (indexOfItem)
{
case 1:
AfxMessageBox(_T("item num 1"));
case 2:
AfxMessageBox(_T("item num 2"));
case 3:
AfxMessageBox(_T("item num 3"));
case 4:
AfxMessageBox(_T("item num 4"));
case 5:
AfxMessageBox(_T("item num 5"));
case 6:
AfxMessageBox(_T("item num 6"));
default:
AfxMessageBox(_T("item select switch err"));
break;
}
*/