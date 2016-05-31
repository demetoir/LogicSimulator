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
#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"
#include "MFCLogicSimulatorView.h"
#include "MFCLogicSimulator.h"
#include "ChildFrm.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{

}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	//	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()

	ON_WM_CONTEXTMENU()
	//	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 메시지 처리기

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	/* 마우스 올렸을 때 */
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	return bRes;
}

//트리 뷰에서 선택하면 선택 정보를 도큐먼트로 넘겨준다
//void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	CTreeCtrl::OnLButtonDown(nFlags, point);
//}


int CViewTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CTreeCtrl m_treeCtr;



	return 0;
}





void CViewTree::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}




void CViewTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();

	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	HTREEITEM hComp = p_Toolbox->GetChildItem(NULL);

	int itemIndex = pDoc->itemSelectedInDoc();
	//아이템이 있고 체크박스에 이벤트가 발생하면
	if (itemIndex != FOLDER_ROOT&&itemIndex == pDoc->currentSelectedComponent) {
		//같은걸 선택하면 체크를 해제한다	
		int state, selecterimage;
		//this->GetItemImage(hItem, image, selecterimage);
		state = this->GetItemState(hItem, TVIS_SELECTED);
		this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
		
		//->SetItemImage(hItem, image, selecterimage);
		pDoc->currentSelectedComponent = 0;
	}


	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}


void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();

	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz

	HTREEITEM hItem = p_Toolbox->GetSelectedItem();


	int itemIndex = pDoc->itemSelectedInDoc();

	
	int state;
	state = this->GetItemState(hItem, TVIS_SELECTED);
	if (state == TVIS_SELECTED) {
		this->SetItemState(hItem, ~TVIS_SELECTED, TVIS_SELECTED);
	}
	else {
		this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	}

	CTreeCtrl::OnLButtonDown(nFlags, point);
}
