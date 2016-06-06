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
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "MFCLogicSimulator.h"
#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"
#include "ChildFrm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
	LIBRARY_BOX_DATA dummy;
	coreDataList.push_back(dummy);
	

}

CFileView::~CFileView()
{
}

void CFileView::addLibraryBox(CString LibraryBoxName)
{
	m_wndFileView.InsertItem(LibraryBoxName, 1, 2, hLib);
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	//ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 메시지 처리기

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 뷰를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	
	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("도구 상자를 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 뷰 이미지를 로드합니다.
	/* IDB_FILE_VIEW 리소스의 16픽셀 단위로 끊어서 사용한다. */
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);
	
	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 정적 트리 뷰 데이터를 채웁니다.
	FillFileView();
	AdjustLayout();



	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{	// tool box data
	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("Logic Simulator"), 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	/*
		0 폴더 | 1,2 기타 | 3,4 and | 5,6 nand | 7,8 or |
		9,10 nor | 11,12 xor | 13,14 not | 15,16 FF
	*/

	HTREEITEM hWire = m_wndFileView.InsertItem(_T("Wire"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("Wire"), 1, 2, hWire);
	m_wndFileView.InsertItem(_T("Pin"), 1, 2, hWire);
	m_wndFileView.InsertItem(_T("Probe"), 1, 2, hWire);

	HTREEITEM hLog = m_wndFileView.InsertItem(_T("Logic Gate"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("AND"), 3, 4, hLog);
	m_wndFileView.InsertItem(_T("NAND"), 5, 6, hLog);
	m_wndFileView.InsertItem(_T("OR"), 7, 8, hLog);
	m_wndFileView.InsertItem(_T("NOR"), 9, 10, hLog);
	m_wndFileView.InsertItem(_T("XOR"), 11, 12, hLog);
	m_wndFileView.InsertItem(_T("NOT"), 13, 14, hLog);

	HTREEITEM hFlip = m_wndFileView.InsertItem(_T("Flip-flop"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("D-FF"), 15, 16, hFlip);
	m_wndFileView.InsertItem(_T("JK-FF"), 15, 16, hFlip);
	m_wndFileView.InsertItem(_T("T-FF"), 15, 16, hFlip);

	HTREEITEM hInp = m_wndFileView.InsertItem(_T("Input"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("1 Bit input switch"), 1, 2, hInp);
	m_wndFileView.InsertItem(_T("Clock"), 1, 2, hInp);

	HTREEITEM hOut = m_wndFileView.InsertItem(_T("Output"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("1 Bit out put lamp"), 1, 2, hOut);
	m_wndFileView.InsertItem(_T("7-segment"), 1, 2, hOut);

	hLib = m_wndFileView.InsertItem(_T("Library Box"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("lib box test"), 1, 2, hLib);


	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hWire, TVE_EXPAND);
	m_wndFileView.Expand(hLog, TVE_EXPAND);
	m_wndFileView.Expand(hFlip, TVE_EXPAND);
	m_wndFileView.Expand(hInp, TVE_EXPAND);
	m_wndFileView.Expand(hOut, TVE_EXPAND);
	m_wndFileView.Expand(hLib, TVE_EXPAND);

}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 클릭한 항목을 선택합니다.
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

//void CFileView::OnProperties()
//{
//	AfxMessageBox(_T("속성...."));
//
//}

void CFileView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnFileOpenWith()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnDummyCompile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);
	m_FileViewImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("비트맵을 로드할 수 없습니다. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);
	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

CViewTree * CFileView::getCFileViewTree()
{
	return &m_wndFileView;
}

void CFileView::addCoreData(LIBRARY_BOX_DATA & coreData)
{
	coreDataList.push_back(coreData);
}

void CFileView::getCoreData(LIBRARY_BOX_DATA & coreData, int index)
{
	coreData = LIBRARY_BOX_DATA(coreDataList[index]);
}

void CFileView::initCoreData()
{
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);
	CString currentExcuteFilePath = path;
	int i = currentExcuteFilePath.ReverseFind('\\');
	currentExcuteFilePath = currentExcuteFilePath.Left(i);
	AfxMessageBox(_T("load Core data"));
	CString coreDataFilePath = currentExcuteFilePath +
		CString(_T("\\MFCLogicSimulatorCoreData\\*.ls"));

	//검색 클래스
	CFileFind finder;

	//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	BOOL bWorking = finder.FindFile(coreDataFilePath); //

	CString filepath;
	CString fileName;
	CString massageName,massagePath;
	while (bWorking)
	{
		//다음 파일 / 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();
		//파일 일때
		if (finder.IsArchived()){
			CString _fileName = finder.GetFileName();
			// 현재폴더 상위폴더 썸네일파일은 제외
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db")) continue;
			filepath = finder.GetFilePath();
			fileName = finder.GetFileName();
			loadCoreData(filepath, fileName);
		}	
	}

	return ;

}

void CFileView::loadCoreData(CString PathName,CString fileName)
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


	bool isSuccessReadFile = false;
	CFile  librayboxFile;

	vector <COMPONENT_DATA> dummy;

	LIBRARY_BOX_DATA coreData;

	if (librayboxFile.Open(PathName, CFile::modeRead)) {
		CArchive ar(&librayboxFile, CArchive::load);
		try {
			pDoc->loadEngineComponentData(ar, &dummy);
			pDoc->loadEngineCoreData(ar, coreData);
			addCoreData(coreData);
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

	if (isSuccessReadFile == true) {
		pFileView->addLibraryBox(fileName);
		str.Format(_T("in file view : load success\n"));
		pOutput->addBuildWindowString(str);
	}
	else {
		str.Format(_T("in file view : load success\n"));
		pOutput->addBuildWindowString(str);
	}




}


