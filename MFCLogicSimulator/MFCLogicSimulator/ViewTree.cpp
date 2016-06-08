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
	ON_MESSAGE(UM_UNSELECT_ITEM_IN_TREEVIEW, &CViewTree::OnUnselectItem)
	ON_WM_CONTEXTMENU()

	ON_WM_LBUTTONDOWN()

//	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)

	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CViewTree::OnTvnSelchanging)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
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
	
	CFileView* pFileView = p_MainFrm->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	
	// 트리 컨트롤 아이템 인덱스
	// goo.gl/mdFKLz
	int indexOfItem = 0;


	HTREEITEM hItem = pToolbox->GetChildItem(NULL);
	RECT rect;

	while (hItem)
	{
		this->GetItemRect(hItem, &rect, 0);

		//선택한 것의 상자 안에 들어 가있음
		if (rect.left <= point.x && point.x <= rect.right
			&&rect.top <= point.y && point.y <= rect.bottom) {
			//폴더를 또 선택하면 아무일도 안일어난다

			//아무것도 아닌상태일때
			if (pDoc->operationMode == OPERATION_MODE_NONE) {
				if (isSelectedItemFolder(pDoc->getSelectedItemIndexInToolBox(hItem)) == false) {
					setItemStateON(hItem);
				}
			}
			//추가 모드일떄
			else if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
				if (pDoc->currentSelectedItemIndex == pDoc->getSelectedItemIndexInToolBox(hItem)) {
					//추가하는 부품을 해제 하고 
					SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW, 100, 100);
				}
				else {
					//다시 선택한다
					SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW, 100, 100);
					if (isSelectedItemFolder(pDoc->getSelectedItemIndexInToolBox(hItem)) == false) {
						setItemStateON(hItem);
					}
				}
			}
			//연결 모드일떄
			else if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
				//연결 모드를 취소한다
				setItemStateON(hItem);
			}
			//부품 선택모드일때
			else if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
				setItemStateON(hItem);

			}
			break;
		}

		hItem = pToolbox->GetNextItem(hItem, TVGN_NEXTVISIBLE);
	}
	(pChild->GetActiveView())->Invalidate();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


//선택 해제 메세지를 처리한다
afx_msg LRESULT CViewTree::OnUnselectItem(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pMainFrm->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	HTREEITEM treeItem = pToolbox->GetChildItem(NULL);

	while (treeItem)
	{
		this->SetItemState(treeItem, ~TVIS_SELECTED, TVIS_SELECTED);
		treeItem = pToolbox->GetNextItem(treeItem, TVGN_NEXTVISIBLE);
	}
	pDoc->operationMode = OPERATION_MODE_NONE;
	pDoc->currentSelectedItemIndex = FOLDER_ROOT;
	CString str;
	str.Format(_T("in tree view : unselect adding item\n"));
	pOutput->addBuildWindowString(str);
	return 0;
}

//재선택 메세지를 처리한다

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




void CViewTree::OnTvnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//
	//https://msdn.microsoft.com/ko-kr/library/a9a9f1t7.aspx
	//*pResult 이거를 1로 세팅해야한다
	*pResult = 1;
}

void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 1;
}

void CViewTree::setItemStateON(HTREEITEM hItem)
{
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	pDoc->operationMode = OPERATION_MODE_ADDING_COMPONENT;
	pDoc->currentSelectedItemIndex = pDoc->getSelectedItemIndexInToolBox(hItem);

	CString str;
	str.Format(_T("in tree view : select adding item \n"));
	pOutput->addBuildWindowString(str);
}

