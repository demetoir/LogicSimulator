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

// ChildFrm.h : CChildFrame 클래스의 인터페이스
//

#pragma once

#include "stdafx.h"
// CMDIChildWndEx 문서
// https://msdn.microsoft.com/ko-kr/library/bb984294.aspx
class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
	int selectedComponentID;
	int x,y;
	int selectedComponentToolboxItemIndex;

	

	
// 특성입니다.
public:
	/* check box, button 이벤트 처리 변수 추가 요망 */
// 작업입니다.
public:

// 재정의입니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateCheckoutput(CCmdUI *pCmdUI);
	afx_msg void OnCheckoutput();
	afx_msg void OnCheckproperties();
	afx_msg void OnUpdateCheckproperties(CCmdUI *pCmdUI);
	afx_msg void OnChecktoolbox();
	afx_msg void OnUpdateChecktoolbox(CCmdUI *pCmdUI);
	afx_msg void OnButtonstop();
	afx_msg void OnUpdateButtonstop(CCmdUI *pCmdUI);
	afx_msg void OnButtoncontinue();
	afx_msg void OnUpdateButtoncontinue(CCmdUI *pCmdUI);
	afx_msg void OnButtonExcutingMode();
	afx_msg void OnUpdateButtonExcutingMode(CCmdUI *pCmdUI);
	afx_msg void OnButtonEditMode();
	afx_msg void OnUpdateButtonEditMode(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnSaveLibrarybox();
	afx_msg void OnUpdateSaveLibrarybox(CCmdUI *pCmdUI);
	afx_msg void OnLoadLibrarybox();
	afx_msg void OnUpdateLoadLibrarybox(CCmdUI *pCmdUI);
	afx_msg void OnCleanLog();
	afx_msg void OnUpdateCleanLog(CCmdUI *pCmdUI);
	afx_msg void OnComponentDelete();
	afx_msg void OnUpdateComponentDelete(CCmdUI *pCmdUI);
	afx_msg void OnUnconnect();
	afx_msg void OnUpdateUnconnect(CCmdUI *pCmdUI);
};
