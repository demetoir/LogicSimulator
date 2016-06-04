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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MFCLogicSimulator.h"

#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"
#include "ChildFrm.h"
#include "FileView.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChangeMSG) // 프로퍼티 변경검색목적
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 메시지 처리기

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

CPropertiesToolBar * CPropertiesWnd::getProperties()
{
	return &m_wndToolBar;
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
	// 속성창 1번쨰 버튼 핸들러
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
	// 속성창 2번쨰 버튼 핸들러
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 속성창 3번째 버튼 핸들러
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 속성창 4번째 버튼 핸들러
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	/* 속성창 설정 옵션 */
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	/******************** 분류: 게이트 설정 시작 ************************/
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("부품 설정"));
	/* 클럭 엣지 방향(상승, 하강) */
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("클럭 엣지 방향"), (_variant_t) true,
		_T("true = 상승, false = 하강")));

	/* 디버깅용 부품 id */
	CMFCPropertyGridProperty* pPropID = new CMFCPropertyGridProperty(_T("부품 id"),
		_T("")/* 생성된 게이트 이름을 설정하고자 함 */, _T("디버그용 부품 id 출력창"));
	pPropID->AllowEdit(FALSE);

	/* 게이트 종류 설정 */
	CMFCPropertyGridProperty* pPropComp = new CMFCPropertyGridProperty(_T("부품 종류"),
		_T("")/* 생성된 게이트 이름을 설정하고자 함 */, _T("Logic gate 중 하나를 지정합니다."));
	pPropComp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pPropID);
	pGroup1->AddSubItem(pPropComp);

	/* 게이트 방향 설정 */
	CMFCPropertyGridProperty* pPropDirc = new CMFCPropertyGridProperty(_T("게이트 방향"),
		_T("동")/* 생성된 게이트 이름을 설정하고자 함 */, _T("부품 방향을 지정합니다."));
	pPropDirc->AddOption(_T("동"));
	pPropDirc->AddOption(_T("서"));
	pPropDirc->AddOption(_T("남"));
	pPropDirc->AddOption(_T("북"));
	pPropDirc->AllowEdit(FALSE);

	pGroup1->AddSubItem(pPropDirc);
	/* 부품 라벨 설정 */
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("라벨"),
		(_variant_t)_T("라벨을 지정하세요."), _T("게이트의 라벨을 지정합니다.")));
	m_wndPropList.AddProperty(pGroup1);

	/* 게이트 크기 설정 */
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("부품 위치"), 0, TRUE);
	pSize->AllowEdit(FALSE);

	CMFCPropertyGridProperty* pPropXY = new CMFCPropertyGridProperty(_T("x좌표"), (_variant_t) 0l, _T("부품 x좌표"));
	pSize->AddSubItem(pPropXY);
	pPropXY->AllowEdit(FALSE);

	pPropXY = new CMFCPropertyGridProperty( _T("y좌표"), (_variant_t) 0l, _T("부품 y좌표"));
	pSize->AddSubItem(pPropXY);
	pPropXY->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pSize);
	/******************** 분류: 게이트 설정 끝 ************************/
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}
/* properties 수정시 호출 */
LRESULT CPropertiesWnd::OnPropertyChangeMSG(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty * pProperty = (CMFCPropertyGridProperty *)lParam;

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//CFileView* pFileView = pFrame->getCFileView();
	//CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_SELECT_COMPONENT;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	str.Format(_T("in properties wnd menu : changed properties value\n"));
	pOutput->addBuildWindowString(str);

	// Note: the return value is not used.
	return(0);
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	//m_wndObjectCombo.SetFont(&m_fntPropList);
}