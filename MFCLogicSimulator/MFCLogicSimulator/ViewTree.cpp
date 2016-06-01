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
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CViewTree::OnTvnItemChanged)
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGING, &CViewTree::OnTvnItemChanging)
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CViewTree::OnTvnItemChanged)
ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
//	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CViewTree::OnTvnSelchanging)
ON_MESSAGE(UM_UNSELECT_ITEM, &CViewTree::OnUnselectItem)
ON_MESSAGE(UM_RESELECT_ITEM, &CViewTree::OnReselectItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 메시지 처리기


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


//선택했던거랑 같은거면 해제한다
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
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();
	RECT rect;
	this->GetItemRect(hItem, &rect, 0);

	//선택한 것의 상자 안에 들어 가있음
	if (rect.left <= point.x && point.x <= rect.right
		&&rect.top <= point.y && point.y <= rect.bottom) {
		//폴더를 또 선택하면 아무일도 안일어난다

		//이전의 선택 한것을 다시 선택 하려 할때
		if (pDoc->currentSelectedItem == -1) {
			SendMessage(UM_RESELECT_ITEM, 100, 100);
		}
		//현재 선택된것을 해제하려 할때
		else if (itemIndex == pDoc->currentSelectedItem) {

			SendMessage(UM_UNSELECT_ITEM, 100, 100);
		}
	}
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


//선택된 값이 변경되면 도큐먼트의 값도 변경한다
void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	if (pDoc == NULL)return;
	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz

	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	CString str;


	//폴더를 처음 선택 하면 아무것도 안한다
	if (isSelectedItemFolder(itemIndex)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
	}
	else {
		pDoc->currentSelectedItem = itemIndex;
		str.Format(_T("in tree view : item %d selected\n"), itemIndex);
		pOutput->addBuildWindowString(str);

	}
}

void CViewTree::unseletectItem()
{


}




//선택 해제 메세지를 처리한다
afx_msg LRESULT CViewTree::OnUnselectItem(WPARAM wParam, LPARAM lParam)
{

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	pDoc->currentSelectedItem = -1;
	this->SetItemState(hItem, ~TVIS_SELECTED, TVIS_SELECTED);

	CString str;
	if (isSelectedItemFolder(pDoc->currentSelectedItem)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
		return 0;
	}

	str.Format(_T("in tree view : item %d unselected\n"), itemIndex);
	pOutput->addBuildWindowString(str);

	return 0;
}

//재선택 메세지를 처리한다
afx_msg LRESULT CViewTree::OnReselectItem(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	pDoc->currentSelectedItem = itemIndex;
	this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);

	CString str;

	if (isSelectedItemFolder(pDoc->currentSelectedItem)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
		return 0;
	}
	
	str.Format(_T("in tree view : item %d reselected\n"), itemIndex);
	pOutput->addBuildWindowString(str);

	return 0;
}

//선택한 아이템이 폴더인지 확인한다
bool CViewTree::isSelectedItemFolder(int selecteItem)
{
	if (selecteItem == FOLDER_ROOT || selecteItem == FOLDER_FF || selecteItem == FOLDER_GATE
		|| selecteItem == FOLDER_INPUT || selecteItem == FOLDER_OUTPUT || selecteItem == FOLDER_WIRE
		) {
		return true;
	}



	return false;
}
