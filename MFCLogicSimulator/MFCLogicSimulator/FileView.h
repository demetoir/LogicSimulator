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

#pragma once
#include "ViewTree.h"
#include "LibraryBoxComponent.h"
class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};
// CDockablePane 문서
// https://msdn.microsoft.com/ko-kr/library/bb984433.aspx
class CFileView : public CDockablePane
{
// 생성입니다.
public:
	CFileView();
	//HTREEITEM selectedItem;
	//HTREEITEM nextItem;
	void AdjustLayout();
	void OnChangeVisualStyle();
	//HTREEITEM getItemSelected() const;
	//HTREEITEM getChildItem(HTREEITEM hItem) const;
	//HTREEITEM getNextItem(HTREEITEM n_Item, UINT n_Flag) const;
	CViewTree* getCFileViewTree();
	void addCoreData(LIBRARY_BOX_DATA& coreData);
	void getCoreData(LIBRARY_BOX_DATA& coreData, int index);

	void initCoreData();
	void loadCoreData(CString PathName, CString fileName);

// 특성입니다.
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;
	HTREEITEM hLib;
	vector <LIBRARY_BOX_DATA> coreDataList;

	void FillFileView();



public:
	virtual ~CFileView();
	void addLibraryBox(CString LibraryBoxName);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

