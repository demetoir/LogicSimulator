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
	ON_COMMAND(ID_BUTTONACT, &CChildFrame::OnButtonact)
	ON_UPDATE_COMMAND_UI(ID_BUTTONACT, &CChildFrame::OnUpdateButtonact)
	ON_COMMAND(ID_BUTTONEDIT, &CChildFrame::OnButtonedit)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEDIT, &CChildFrame::OnUpdateButtonedit)
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
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

CChildFrame::CChildFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
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
void CChildFrame::OnButtonstop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateButtonstop(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);

}


void CChildFrame::OnButtoncontinue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateButtoncontinue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}

void CChildFrame::OnButtonact()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateButtonact(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CChildFrame::OnButtonedit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateButtonedit(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}
/*************** Ribbon button 처리기 *****************/




/*************** Ribbon 클립보드 처리기 *****************/
void CChildFrame::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CChildFrame::OnEditCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildFrame::OnEditSelectAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
}


void CChildFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CChildFrame::OnEditRedo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildFrame::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
/*************** Ribbon redo, undo 처리기 *****************/
