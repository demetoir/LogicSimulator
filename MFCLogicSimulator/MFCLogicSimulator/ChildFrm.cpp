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

// ChildFrm.cpp : CChildFrame 클래스의 구현
//

#include "stdafx.h"
#include "MFCLogicSimulator.h"
#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"
#include "MFCLogicSimulatorView.h"
#include "FileView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_CHECKOUTPUT, &CChildFrame::OnUpdateCheckoutput)
	ON_COMMAND(ID_CHECKOUTPUT, &CChildFrame::OnCheckoutput)
	ON_COMMAND(ID_CHECKPROPERTIES, &CChildFrame::OnCheckproperties)
	ON_UPDATE_COMMAND_UI(ID_CHECKPROPERTIES, &CChildFrame::OnUpdateCheckproperties)
	ON_COMMAND(ID_CHECKTOOLBOX, &CChildFrame::OnChecktoolbox)
	ON_UPDATE_COMMAND_UI(ID_CHECKTOOLBOX, &CChildFrame::OnUpdateChecktoolbox)
	ON_COMMAND(ID_BUTTONSTOP, &CChildFrame::OnButtonstop)
	ON_UPDATE_COMMAND_UI(ID_BUTTONSTOP, &CChildFrame::OnUpdateButtonstop)
	ON_COMMAND(ID_BUTTONCONTINUE, &CChildFrame::OnButtoncontinue)
	ON_UPDATE_COMMAND_UI(ID_BUTTONCONTINUE, &CChildFrame::OnUpdateButtoncontinue)
	ON_COMMAND(ID_BUTTONACT, &CChildFrame::OnButtonExcutingMode)
	ON_UPDATE_COMMAND_UI(ID_BUTTONACT, &CChildFrame::OnUpdateButtonExcutingMode)
	ON_COMMAND(ID_BUTTONEDIT, &CChildFrame::OnButtonEditMode)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEDIT, &CChildFrame::OnUpdateButtonEditMode)
	ON_COMMAND(ID_EDIT_COPY, &CChildFrame::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CChildFrame::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CChildFrame::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CChildFrame::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, &CChildFrame::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CChildFrame::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CChildFrame::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CChildFrame::OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CChildFrame::OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CChildFrame::OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_REDO, &CChildFrame::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CChildFrame::OnUpdateEditRedo)
	ON_COMMAND(ID_SAVE_LIBRARYBOX, &CChildFrame::OnSaveLibrarybox)
	ON_UPDATE_COMMAND_UI(ID_SAVE_LIBRARYBOX, &CChildFrame::OnUpdateSaveLibrarybox)
	ON_COMMAND(ID_LOAD_LIBRARYBOX, &CChildFrame::OnLoadLibrarybox)
	ON_UPDATE_COMMAND_UI(ID_LOAD_LIBRARYBOX, &CChildFrame::OnUpdateLoadLibrarybox)
	ON_COMMAND(ID_CLEAN_LOG, &CChildFrame::OnCleanLog)
	ON_UPDATE_COMMAND_UI(ID_CLEAN_LOG, &CChildFrame::OnUpdateCleanLog)
	ON_COMMAND(ID_COMP_DELETE, &CChildFrame::OnComponentDelete)
	ON_UPDATE_COMMAND_UI(ID_COMP_DELETE, &CChildFrame::OnUpdateComponentDelete)
	ON_COMMAND(ID_UNCONECT, &CChildFrame::OnUnconnect)
	ON_UPDATE_COMMAND_UI(ID_UNCONECT, &CChildFrame::OnUpdateUnconnect)
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

CChildFrame::CChildFrame()
{
	selectedComponentID = 0;
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 진단

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 메시지 처리기

void CChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 인쇄 미리 보기 모드를 닫습니다.
	}
}

void CChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}


/*************** Ribbon check box 처리기 ***************/
/* out put wnd on/off 처리기 */
void CChildFrame::OnCheckoutput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
void CChildFrame::OnUpdateCheckoutput(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}


/* properties wnd on/off 처리기 */
void CChildFrame::OnCheckproperties()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
void CChildFrame::OnUpdateCheckproperties(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}


/* tool box wnd on/off 처리기 */
void CChildFrame::OnChecktoolbox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
void CChildFrame::OnUpdateChecktoolbox(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}
/*************** Ribbon check box 처리기 *****************/





/*************** Ribbon button 처리기 *****************/
/* 멈춤 button 처리기 */
void CChildFrame::OnButtonstop()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->isRunningMode = false;
	pDoc->isCurcuitOcillate = false;
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	pView->stopUpdating();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	str.Format(_T("in rebbon menu : stop updating curcuit \n"));
	pOutput->addBuildWindowString(str);

}
void CChildFrame::OnUpdateButtonstop(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();


	if (pDoc->isCurcuitOcillate == true) {
		pCmdUI->SetCheck(1);

	}
	if (pDoc->isRunningMode == false) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
}


/* 계속 button 처리기 */
void CChildFrame::OnButtoncontinue()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	
	pView->startUpdating();
	pDoc->isRunningMode = true;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	str.Format(_T("in rebbon menu : updating curcuit \n"));
	pOutput->addBuildWindowString(str);
}
void CChildFrame::OnUpdateButtoncontinue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	
	if (pDoc->isCurcuitOcillate == true) {
		pCmdUI->SetCheck(0);
		pDoc->isRunningMode = false;
	}
	if (pDoc->isRunningMode == true) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}

}


/* 실행모드 botton 처리기 */
void CChildFrame::OnButtonExcutingMode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_VAlUE_CHANGE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	str.Format(_T("in rebbon menu : mode change -> changing componnent value\n"));
	pOutput->addBuildWindowString(str);

}
void CChildFrame::OnUpdateButtonExcutingMode(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);


	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	if (pDoc->operationMode == OPERATION_MODE_VAlUE_CHANGE) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
}


/* 편집모드 botton 처리기 */
void CChildFrame::OnButtonEditMode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_NONE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	str.Format(_T("in rebbon menu : mode change -> edit mode\n"));
	pOutput->addBuildWindowString(str);
}
void CChildFrame::OnUpdateButtonEditMode(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	if (pDoc->operationMode != OPERATION_MODE_VAlUE_CHANGE) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}

}
/*************** Ribbon button 처리기 *****************/




/*************** Ribbon 클립보드 처리기 *****************/
// https://msdn.microsoft.com/ko-kr/library/80db3kax.aspx
void CChildFrame::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	selectedComponentID = pDoc->selectedComponentID;
	int id = selectedComponentID;
	x = pDoc->engineComponentData[id].x;
	y = pDoc->engineComponentData[id].y;
	selectedComponentToolboxItemIndex  = pDoc->toolboxItemData[id];


	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	// Remove the current Clipboard contents
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}
	// Get the currently selected data
	CloseClipboard();
}
void CChildFrame::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditPaste()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	if (selectedComponentID <= 0) {
		return;
	}			
	pDoc->addComponentToEngine(x + 30, y + 30, selectedComponentToolboxItemIndex);

	pChild->GetActiveView()->Invalidate();
}
void CChildFrame::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditCut()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	selectedComponentID = pDoc->selectedComponentID;
	int id = selectedComponentID;
	x = pDoc->engineComponentData[id].x;
	y = pDoc->engineComponentData[id].y;
	selectedComponentToolboxItemIndex = pDoc->toolboxItemData[id];
	pDoc->deleteComponentToEngine(id);
	pChild->GetActiveView()->Invalidate();
}
void CChildFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditSelectAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("select all"));
}
void CChildFrame::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
/*************** Ribbon 클립보드 처리기 *****************/





/*************** Ribbon redo, undo 처리기 *****************/
void CChildFrame::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("undo"));
}
void CChildFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditRedo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("redo"));
}
void CChildFrame::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
/*************** Ribbon redo, undo 처리기 *****************/



/*************** Ribbon library box control *****************/
void CChildFrame::OnSaveLibrarybox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("save lib box"));
}
void CChildFrame::OnUpdateSaveLibrarybox(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnLoadLibrarybox()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CFileView *pFileView = (CFileView*)pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();

	CString str;
	CFileDialog load_dlg(true);
	CString PathName;
	CString fileName;
	str.Format(_T("in rebbon menu : try load library box\n"), pDoc->selectedComponentID);
	pOutput->addBuildWindowString(str);

	if (load_dlg.DoModal() == IDOK) {
		PathName = load_dlg.GetPathName();
		fileName = load_dlg.GetFileName();
		//AfxMessageBox(PathName);
	}

	bool isSuccessReadFile = false;
	CFile  librayboxFile;

	vector <COMPONENT_DATA> dummy; 

	LIBRARY_BOX_DATA coreData;
	
	if (librayboxFile.Open(PathName, CFile::modeRead)) {
		CArchive ar(&librayboxFile, CArchive::load);
		try {
			pDoc->loadEngineComponentData(ar, &dummy);
			pDoc->loadEngineCoreData(ar,coreData);
			pFileView->addCoreData(coreData);
			isSuccessReadFile = true;
			str.Format(_T("in rebbon menu : load library core data  to toolBox\n"), pDoc->selectedComponentID);
			pOutput->addBuildWindowString(str);
		}
		catch (CFileException *fe) {
			// 예외가 발생하면 메세지박스를 통하여 사용자에게 알린다.
			fe->ReportError();
		}
		catch (CArchiveException *ae) {
			// 예외가 발생하면 메세지박스를 통하여 사용자에게 알린다.
			ae->ReportError();
		}
		// CArchive 를 닫는다.
		ar.Close();
		// 파일을 닫는다.
		librayboxFile.Close();
	}


	
	str.Format(_T("in rebbon menu : try delete component ->ID : %d \n"), pDoc->selectedComponentID);
	pOutput->addBuildWindowString(str);


	if (isSuccessReadFile == true) {
		pFileView->addLibraryBox(fileName);
		str.Format(_T("in rebbon menu : try add libbox to toolBox\n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
	}
	else {
		str.Format(_T("in rebbon menu : fail load library box -> readfile fail\n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
	}

	
}
void CChildFrame::OnUpdateLoadLibrarybox(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
/*************** Ribbon library box control END *****************/



/*************** Ribbon output wnd control *****************/
void CChildFrame::OnCleanLog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	//CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	//CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	//CFileView *pFileView = (CFileView*)pFrame->getCFileView();
	//CViewTree* pToolbox = pFileView->getCFileViewTree();
	pOutput->resetBuildWindowString();
	AfxMessageBox(_T("Log clear"));
}
void CChildFrame::OnUpdateCleanLog(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CChildFrame::OnComponentDelete()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CString str;
	
	if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
		str.Format(_T("in rebbon menu : try delete component ->ID : %d \n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
		pDoc->deleteComponentToEngine(pDoc->selectedComponentID);
		pView->Invalidate();
	}
	else {
		str.Format(_T("in rebbon menu : fail to delete component -> component not selected\n"));
		pOutput->addBuildWindowString(str);
	}

}
void CChildFrame::OnUpdateComponentDelete(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CChildFrame::OnUnconnect()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CString str;


	str.Format(_T("in rebbon menu : try disconnect\n"));
	pOutput->addBuildWindowString(str);
	pDoc->disconectComponent();
	pView->Invalidate();


}
void CChildFrame::OnUpdateUnconnect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
/*************** Ribbon output wnd control END*****************/


