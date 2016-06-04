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

// MFCLogicSimulatorView.cpp : CMFCLogicSimulatorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"

#include "FileView.h" // tree item 관련하여 추가
#include "PropertiesWnd.h" // 속성창 옵션 수정 관련하여 추가

#include "ViewTree.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include"OutputPin.h"
#include "PropertiesWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLogicSimulatorView

IMPLEMENT_DYNCREATE(CMFCLogicSimulatorView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCLogicSimulatorView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCLogicSimulatorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCLogicSimulatorView 생성/소멸



CMFCLogicSimulatorView::CMFCLogicSimulatorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	isHighlightComponentMode = false;
	isHighlightTerminalPin = false;
	currentSelectedTerminalPoint.x = 0;
	currentSelectedTerminalPoint.y = 0;
}

CMFCLogicSimulatorView::~CMFCLogicSimulatorView()
{

}

BOOL CMFCLogicSimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}



void CMFCLogicSimulatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


}

void CMFCLogicSimulatorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void CMFCLogicSimulatorView::OnInitialUpdate()
{
	GetClientRect(&rlClientRect);
	CSize sizeTotal;
	// 뷰의 전체 크기 계산(정의)
	sizeTotal.cx = SIZE_OF_VIEW_X;
	sizeTotal.cy = SIZE_OF_VIEW_Y;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

BOOL CMFCLogicSimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCLogicSimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCLogicSimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCLogicSimulatorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCLogicSimulatorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	// popup menu 비활성화 상태
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CMFCLogicSimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// logic doc 포인터 가져옴
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	SELECTED_TERMINAL_INFO selectedTerminalInfo;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);	

	//지금 부품 추가 모드이면
	switch (pDoc->operationMode) {
	case OPERATION_MODE_ADDING_COMPONENT: {
		//보정할 좌표를 가져온다

		//선택한 부품을 도큐에 추가한다
		pDoc->addComponentToEngine(point.x + nHorzScroll, point.y + nVertScroll);
		pDoc->operationMode = OPERATION_MODE_NONE;
		//tree view 부품 선택모드를 해제하는 메세지를 날린다		
		((pFrame->getCFileView())->getCFileViewTree())->SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW);
		
		Invalidate();
		break;}

		//지금 부품 선택 모드라면
		//부품을 
	case OPERATION_MODE_SELECT_COMPONENT: {
		int newIndex;
		newIndex = checkMouesPointOnComponent();
		//선택이 취소됨
		if (newIndex <=0) {
			highlightComponentIndex = 0;
			pDoc->operationMode = OPERATION_MODE_NONE;

		}
		// 다른 부품을 선택함
		else if (newIndex != highlightComponentIndex) {
			highlightComponentIndex = newIndex;
		}
		
		//만약 부품을 선택하면 부품 선택 모드로 변경한다
		//선택한 부품을 하이라이트 한다

		//만약 부품의 단자를 선택하면 단자를 하이라이트 한다

		Invalidate();
		break;}
	
	case OPERATION_MODE_CONNECTING_COMPONENT: {
		bool isInTerminalPin = checkMouesPointOnTerminalPin(selectedTerminalInfo);
		//다른곳을 클릭하였다 해제한다
		if (isInTerminalPin == true) {
			checkMouesPointOnTerminalPin(selectedTerminalInfo);
			//연결가능하면
			pDoc->connectComponent(selectedTerminalInfo,
				firstSelectedTerminalPin);
		}
		//정리한다
		pDoc->operationMode = OPERATION_MODE_NONE;
		oldSelectedTerminalPoint.x = 0;
		oldSelectedTerminalPoint.y = 0;
		currentSelectedTerminalPoint.x = 0;
		currentSelectedTerminalPoint.y = 0;
		copyTerminalInfo(dummy_SELECTED_TERMINAL_INFO, firstSelectedTerminalPin);
		copyTerminalInfo(dummy_SELECTED_TERMINAL_INFO, secondSelectedTerminalPin);

		Invalidate();
		break;}

	case OPERATION_MODE_NONE: {
		//마우스가 화면의 부품을 선택함

		highlightComponentIndex = checkMouesPointOnComponent();
		if (highlightComponentIndex > 0) {
			pDoc->operationMode = OPERATION_MODE_SELECT_COMPONENT;
			Invalidate();
		}
		
		//핀을 클릭함 연결 모드로 전환한다
		bool isInTerminalPin  = checkMouesPointOnTerminalPin(selectedTerminalInfo);
		if (isInTerminalPin == true) {
			pDoc->operationMode = OPERATION_MODE_CONNECTING_COMPONENT;
			copyTerminalInfo(selectedTerminalInfo, firstSelectedTerminalPin);
			oldSelectedTerminalPoint.x = currentSelectedTerminalPoint.x;
			oldSelectedTerminalPoint.y = currentSelectedTerminalPoint.y;
			Invalidate();
		}
		break; }
	default: {


		break;}
	}
	

	CScrollView::OnLButtonDown(nFlags, point);
}

void CMFCLogicSimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonUp(nFlags, point);
}

//이것을 해야한다 참고자료
//http://adnoctum.tistory.com/149
void CMFCLogicSimulatorView::OnPaint()
{
	CPaintDC dc(this);

	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap newBitmap;
	CBitmap *pOldBitmap;
	SELECTED_TERMINAL_INFO dummyInfo;


	//더블버퍼링을 하기 위해 버퍼역할을 할 비트맵을 지정한다
	memDC.CreateCompatibleDC(&dc);
	newBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&newBitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);


	//메모리에다가 그리기시작
	{
		// 뷰 스크롤 및 크기 조정
		// https://msdn.microsoft.com/ko-kr/library/cc468151(v=vs.71).aspx
		// http://eachan.tistory.com/3
		/* 스크롤바 컨트롤 */ {
			int nVertScroll = GetScrollPos(SB_VERT);
			int nHorzScroll = GetScrollPos(SB_HORZ);

			CPoint scrollpos = GetScrollPosition();
			memDC.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom, &memDC, 0, 0, SRCCOPY);
		}
		/* 스크롤바 컨트롤 끝 */

			//그리기 시작
		{
			//부품들을 그린다
			drawComponent(memDC);
			//와이어들을 그림
			drawConnectedWire(memDC);

			//추가 모드일때만 한다
			//부품 추가 모드일떄 움직이면서 보여주는거
			if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
				drawAddingComponent(memDC);
			}
			if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
				//화면에 있는 선택 한부품을 강조하는거
				drawHighlightSelectedComponent(memDC);
			}
			
			if (isHighlightTerminalPin == true) {
				drawHighlightComponentTerminalPin(memDC);
			}

			if (ishighlightConnectedWire == true) {
				drawHighlightSelectedconnectedWire(memDC);
			}

			if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
				drawConnectingWire(memDC);
			}


			//화면에 메세지를 띄어주는것
			drawMassage(memDC);
		}
	}

	//그리기 종료

	//버퍼 역할을 하는 비트맵을 화면으로 출력한다
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	dc.SelectObject(pOldBitmap);
	newBitmap.DeleteObject();
	ReleaseDC(&memDC);
	DeleteDC(memDC);




}

void CMFCLogicSimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);

	//부품 추가 모드 일때 선택한 부품의 좌표를 갱신한다

	//마우스가 부품위에 있는경우 부품을 강조한다

	//마우스가부품의 단자 위에 있으면  단자를 강조한다
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
		Invalidate();
	}
	if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {

		//마우스가 눌린 상태에서 움직이면 정보를 갱신한다
		if ((nFlags & MK_LBUTTON) == MK_LBUTTON){

			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			int nVertScroll = GetScrollPos(SB_VERT);
			int nHorzScroll = GetScrollPos(SB_HORZ);
			COMPONENT_DATA* highlightComponent;
			highlightComponent = &pDoc->engineComponentData[highlightComponentIndex];
			highlightComponent->x = point.x+ nHorzScroll;
			highlightComponent->y = point.y+ nVertScroll;
			Invalidate();
		}



	}
	SELECTED_TERMINAL_INFO dummyInfo;

	bool oldval = isHighlightTerminalPin;
	isHighlightTerminalPin = checkMouesPointOnTerminalPin(dummyInfo);
	if (oldval != isHighlightTerminalPin) {
		Invalidate();
	}

	oldval = ishighlightConnectedWire;
	ishighlightConnectedWire=checkMousePointOnConnectedWire();
	if (oldval != ishighlightConnectedWire) {
		Invalidate();
	}

	if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
		Invalidate();
	}

}

void CMFCLogicSimulatorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}
void CMFCLogicSimulatorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}

//이것을 해야한다
//http://adnoctum.tistory.com/149
BOOL CMFCLogicSimulatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
}

// CMFCLogicSimulatorView 진단

#ifdef _DEBUG
void CMFCLogicSimulatorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCLogicSimulatorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCLogicSimulatorDoc)));
	return (CMFCLogicSimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCLogicSimulatorView 메시지 처리기




//각부품을 그릴때에 방향추가가 필요하다
void CMFCLogicSimulatorView::drawComponent(CDC &DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;
	CComponentObject* currentObject;

	CBitmap terminalPin;
	BITMAP terminalPinInfo;

	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		//존재하지 않는것은 넘어간다
		if (pDoc->engineComponentData[i].id <= 0) {
			continue;
		}

		//그릴 부품의 객체를 가져온다
		currentObject = pDoc->logicSimulatorEngine.getComponentObject(i);
		//그려줄 좌표를 보정한다
		x = pDoc->engineComponentData[i].x - nHorzScroll;
		y = pDoc->engineComponentData[i].y - nVertScroll;
		type = pDoc->engineComponentData[i].type;
		direction = pDoc->engineComponentData[i].direction;
		//세븐 세그먼트는 따로 구현한다
		

		//타입에 맞는 부품의 비트맵 아이디를 가져오고 로드한다
		componentBitmap.LoadBitmapW(getBitmapIDByComponentType(type, direction));
		componentBitmap.GetBitmap(&bitmapInfo);

		// 터미널 핀을 그린다
		drawComponentTermialPin(DC, x, y, direction, bitmapInfo.bmWidth, bitmapInfo.bmHeight,
			currentObject->numberOfInput(), currentObject->numberOfOutput());

		//부품을 그린다
		oldBitmap = memDC.SelectObject(&componentBitmap);
		DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBitmap);

		//가져온 비트맵을 제거한다
		componentBitmap.DeleteObject();
		
	}
}

void CMFCLogicSimulatorView::drawConnectedWire(CDC & DC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	ADJ_LIST* Grahp;
	Grahp = pDoc->logicSimulatorEngine.getConnectionGrahp();
	COMPONENT_DATA* pCurrentComponent;

	CPen pen;
	pen.CreatePen(PS_DOT, 5, RGB(0, 0, 0));
	CPen* oldPen = DC.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = DC.SelectObject(&brush);
	int curID;
	int nextID;
	CPoint A, B;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].id <= 0) { continue; }
		pCurrentComponent = &pDoc->engineComponentData[i];
		curID = pCurrentComponent->id;
		
		for (int j = 0; j<(*Grahp)[i].size(); j++) {
			nextID = (*Grahp)[i][j].componentID;
			if (nextID <= 0) { continue; }
			
			//output 단자의 좌표를 가져온다
			getOutputTerminalPoint(curID,A, j);

			//input 단자의 좌표를 가져온다
			getInputTerminalPoint(nextID, B, (*Grahp)[i][j].terminalNumber);

			//좌표를 보정한다
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;
			//연결할 선을 그린다			
			DC.MoveTo(A);
			DC.LineTo(B);
		}
	}
	DC.SelectObject(oldBrush);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawAddingComponent(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	COMPONENT_TYPE type;
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;
	CComponentObject* currentObject;

	//마우스의좌표를 가져온다
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	//그려줄 좌표를 보정한다

	x = point.x;
	y = point.y;


	type = pDoc->getCurrentSelectedComponentType();
	if (type == COMPONENT_TYPE_NONE)
		return;

	//타입에 맞는 부품의 비트맵 아이디를 가져오고 로드한다
	componentBitmap.LoadBitmapW(getBitmapIDByComponentType(type,EAST));
	componentBitmap.GetBitmap(&bitmapInfo);

	//부품을 그린다
	oldBitmap = memDC.SelectObject(&componentBitmap);
	DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

	//가져온 비트맵을 제거한다
	componentBitmap.DeleteObject();

}

void CMFCLogicSimulatorView::drawHighlightSelectedComponent(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	CBitmap bitmap;
	BITMAP bitmapInfo;

	COMPONENT_DATA* currentComponent;
	currentComponent = &pDoc->engineComponentData[highlightComponentIndex];
	x = currentComponent->x - nHorzScroll;
	y = currentComponent->y - nVertScroll;
	currentComponent->type;

	if (currentComponent->type == COMPONENT_TYPE_LIBRARY_BOX) {

	}
	else if (currentComponent->type == COMPONENT_TYPE_7SEGMENT) {

	}
	else {
		drawHighlightComponentBody(DC, x, y, 75, 75);
	}


}

void CMFCLogicSimulatorView::drawHighlightSelectedconnectedWire(CDC & DC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));   //빨간색 팬생성
	CPen* oldPen = DC.SelectObject(&pen); 

	DC.Polyline(selectedConnectedWirePoints,4);
	DC.MoveTo(selectedConnectedWirePoints[3]);
	DC.LineTo(selectedConnectedWirePoints[0]);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawMassage(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

void CMFCLogicSimulatorView::drawHighlightComponentBody(CDC& DC, int x, int y, int bitmapWidth, int bitmapHeight)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));    // 빨간색 펜 생성
	CPen* oldPen = DC.SelectObject(&pen);

	DC.MoveTo(x - HIGHLIGHT_EDGE_GAP, y - HIGHLIGHT_EDGE_GAP);
	DC.LineTo(x + HIGHLIGHT_EDGE_GAP + bitmapWidth, y - HIGHLIGHT_EDGE_GAP);
	DC.LineTo(x + HIGHLIGHT_EDGE_GAP + bitmapWidth, y + HIGHLIGHT_EDGE_GAP + bitmapHeight);
	DC.LineTo(x - HIGHLIGHT_EDGE_GAP, y + HIGHLIGHT_EDGE_GAP + bitmapHeight);
	DC.LineTo(x - HIGHLIGHT_EDGE_GAP, y - HIGHLIGHT_EDGE_GAP);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawHighlightComponentTerminalPin(CDC & DC)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x = currentSelectedTerminalPoint.x - nHorzScroll;
	int y = currentSelectedTerminalPoint.y - nVertScroll;

	CPen pen;
	CPen* oldPen;
	//인풋핀을 그린다
	pen.CreatePen(PS_SOLID, 2, RGB(153, 0, 0255));    // 펜 생성
	oldPen = DC.SelectObject(&pen);
	DC.Ellipse(x - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE,
		x + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE);
	DC.SelectObject(oldPen);
	pen.DeleteObject();
}

void CMFCLogicSimulatorView::drawComponentTermialPin(CDC & DC, int x, int y, COMPONENT_DIRECTION direction, 
	int componentWidth, int componentHeight, int numberOfInputTerminal, int numberOfOutputTerminal)
{
	CPen pen;
	CPen* oldPen;

	int inputTerminalGap, outputTerminalGap;
	int a, b;
	switch (direction) {
	case EAST: {
		inputTerminalGap = componentHeight / (numberOfInputTerminal + 1);
		outputTerminalGap = componentHeight / (numberOfOutputTerminal + 1);

		//인풋핀을 그린다
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x - 10;
			b = y + inputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a + 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		//부품의 아웃풋 핀을 그린다
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + componentWidth + 10;
			b = y + outputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a - 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	case SOUTH: {
		inputTerminalGap = componentWidth / (numberOfInputTerminal + 1);
		outputTerminalGap = componentWidth / (numberOfOutputTerminal + 1);

		//인풋핀을 그린다
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + inputTerminalGap * curI;
			b = y + -10;
			DC.MoveTo(a, b);
			DC.LineTo(a , b+30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		//부품의 아웃풋 핀을 그린다
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + outputTerminalGap * curI;
			b = y + componentHeight+10;
			DC.MoveTo(a, b);
			DC.LineTo(a , b-30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	case WEST: {
		inputTerminalGap = componentHeight / (numberOfInputTerminal + 1);
		outputTerminalGap = componentHeight / (numberOfOutputTerminal + 1);

		//인풋핀을 그린다
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + componentWidth + 10;
			b = y + inputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a - 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		//부품의 아웃풋 핀을 그린다
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x - 10;
			b = y + outputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a + 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();


		break;
	}
	case NORTH: {
		inputTerminalGap = componentWidth / (numberOfInputTerminal + 1);
		outputTerminalGap = componentWidth / (numberOfOutputTerminal + 1);

		//인풋핀을 그린다
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + inputTerminalGap * curI;
			b = y + componentHeight + 10;
			DC.MoveTo(a, b);
			DC.LineTo(a, b - 30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // 빨간색 펜 생성
		oldPen = DC.SelectObject(&pen);
		//부품의 아웃풋 핀을 그린다
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + outputTerminalGap * curI;
			b = y - 10;
			DC.MoveTo(a, b);
			DC.LineTo(a, b + 30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	default:
		break;
	}
}

void CMFCLogicSimulatorView::drawComponentBody(CDC & DC, int x, int y, COMPONENT_DIRECTION direction,
	int componentWidth, int componentHeight)
{
	switch (direction) {
	case EAST:
		break;
	case SOUTH:
		break;
	case WEST:
		break;
	case NORTH:
		break;
	default:
		break;
	}

}

void CMFCLogicSimulatorView::drawConnectingWire(CDC & DC)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	point.x ;
	point.y ;

	CPen pen;
	pen.CreatePen(PS_DOT, 5, RGB(0, 0, 0));    
	CPen* oldPen = DC.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = DC.SelectObject(&brush);

	int x = oldSelectedTerminalPoint.x - nHorzScroll;
	int y = oldSelectedTerminalPoint.y - nVertScroll;
	//원을그린다
	DC.Ellipse(x- CONNECTING_WIRE_ELLIPSE_HALF_SIZE, 
		y - CONNECTING_WIRE_ELLIPSE_HALF_SIZE,
		x + CONNECTING_WIRE_ELLIPSE_HALF_SIZE,
		y + CONNECTING_WIRE_ELLIPSE_HALF_SIZE);	

	DC.SelectObject(oldBrush);
	DC.MoveTo(x,y);
	DC.LineTo(point.x, point.y);
	DC.SelectObject(oldPen);
}




int CMFCLogicSimulatorView::getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction)
{
	////엔진에서 사용하는 부품 타입 열거형
	//enum COMPONENT_TYPE {
	//	COMPONENT_TYPE_NONE,
	//	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	//	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE, COMPONENT_TYPE_XOR_GATE,
	//	COMPONENT_TYPE_WIRE,
	//	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	//	COMPONENT_TYPE_LIBRARY_BOX
	//};
//리소스에서 사용되는 비트맵 아이디
	switch (_type) {

	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		return IDB_SWITCH_OFF_E;
		break;

	case COMPONENT_TYPE_ONE_BIT_LAMP:
		return IDB_LAMP_OFF_E;
		break;
	case COMPONENT_TYPE_CLOCK:
		return IDB_CLOCK_E;
		break ;
		 
	//case COMPONENT_TYPE_7SEGMENT:
	//	return IDB_ONE_BIT_SWITCH_OFF;
	//	break;




	case COMPONENT_TYPE_AND_GATE:
		return IDB_GATE_AND_E+ direction;
		break;
	case COMPONENT_TYPE_OR_GATE :
		return IDB_GATE_OR_E + direction;
		break;
	case COMPONENT_TYPE_NOT_GATE:
		return IDB_INVERTOR_E + direction;
		break;
	case COMPONENT_TYPE_XOR_GATE:
		return IDB_GATE_XOR_E + direction;
		break;

	case COMPONENT_TYPE_INPUT_PIN:
		return IDB_PIN_ON_E;
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		return IDB_PROBE_OFF_E ;
		break;

	case COMPONENT_TYPE_WIRE:
		return IDB_COPPER_WIRE;
		break;
		

	case COMPONENT_TYPE_LIBRARY_BOX:
		return IDB_LIBBOX_E + direction;
		break;


	//
	//
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_DFF;
	//		break;
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_JKFF;
	//		break;
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_TFF;
	//		break;



		//#define IDB_FF_DFF                      327
		//#define IDB_FF_JKFF                     328
		//#define IDB_FF_TFF                      329
		//
		//#define IDB_GATE_NAND                   332
		//#define IDB_GATE_NOR                    333
	default:
		return -1;
	}
	return 0;
}

void CMFCLogicSimulatorView::getConnnectedWirePoints(CPoint* points, CPoint A, CPoint B)
{
	int dx, dy;
	int x = A.x;
	int y = A.y;
	int w = B.x - A.x;
	int h = B.y - A.y;

	double angle;
	double theta = w ? atan(double(h) / double(w)) : sin(h)* PI / 2.0;

	if (theta < 0) {
		angle = (theta + PI / 2.0);
	}
	angle = (theta + PI / 2.0);
	dx = int(HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH* cos(angle));
	dy = int(HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH* sin(angle));

	points[0] = CPoint(x + dx, y + dy);
	points[1] = CPoint(x - dx, y - dy);
	points[2] = CPoint(x - dx + w, y - dy +h);
	points[3] = CPoint(x + dx + w, y + dy + h);
}

int CMFCLogicSimulatorView::getComponentHeight(COMPONENT_TYPE type)
{
	//세그먼트일때
	if (type == COMPONENT_TYPE_7SEGMENT) {
		return 120;
	}
	else if (type == COMPONENT_TYPE_LIBRARY_BOX) {
		return 120;
	}
	else {
		return 75;
	}
}

int CMFCLogicSimulatorView::getComponentWidth(COMPONENT_TYPE type)
{
	//세그먼트일때
	if (type == COMPONENT_TYPE_7SEGMENT) {
		return 75;
	}
	else if (type == COMPONENT_TYPE_LIBRARY_BOX) {
		return 75;
	}
	else {
		return 75;
	}
}

void CMFCLogicSimulatorView::getInputTerminalPoint(int id, CPoint &point, int index)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int inputTerminalGap;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	point.x += nHorzScroll;
	point.y += nVertScroll;

	currentObject = pDoc->logicSimulatorEngine.getComponentObject(id);
	int numberOfInputTerminal = currentObject->numberOfInput();
	COMPONENT_DATA *data = &pDoc->engineComponentData[id];
	int width = getComponentWidth(data->type);
	int Height = getComponentHeight(data->type);

	switch (data->direction) {
	case EAST: {
		inputTerminalGap = Height / (numberOfInputTerminal + 1);
		point.x = data->x - 10;
		point.y = data->y + inputTerminalGap * (index + 1);
		break; 
	}
	case SOUTH: {
		inputTerminalGap = width / (numberOfInputTerminal + 1);
		point.x = data->x + inputTerminalGap * (index+1);
		point.y = data->y + -10;
		break;
	}
	case WEST: {
		inputTerminalGap = Height / (numberOfInputTerminal + 1);
		point.x = data->x + Height + 10;
		point.y = data->y + inputTerminalGap * (index+1);
		break;
	}
	case NORTH: {
		inputTerminalGap = width / (numberOfInputTerminal + 1);
		point.x = data->x + inputTerminalGap * (index+1);
		point.y = data->y + width + 10;
		break;
	}
	default: break;	
	}
}

void CMFCLogicSimulatorView::getOutputTerminalPoint(int id, CPoint & point, int index)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int outputTerminalGap;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	point.x += nHorzScroll;
	point.y += nVertScroll;

	currentObject = pDoc->logicSimulatorEngine.getComponentObject(id);
	int numberOfOutputTerminal = currentObject->numberOfOutput();
	COMPONENT_DATA *data = &pDoc->engineComponentData[id];
	int width = getComponentWidth(data->type);
	int Height = getComponentHeight(data->type);

	switch (data->direction) {
	case EAST: {
		outputTerminalGap = Height / (numberOfOutputTerminal + 1);
		point.x  = data->x + width + 10;
		point.y = data->y + outputTerminalGap * (index+1);
		break;
	}
	case SOUTH: {
		outputTerminalGap = width / (numberOfOutputTerminal + 1);
		point.x = data->x + outputTerminalGap *  (index + 1);
		point.y = data->y + Height + 10;
		break;
	}
	case WEST: {
		outputTerminalGap = Height / (numberOfOutputTerminal + 1);
		point.x = data->x - 10;
		point.y = data->y + outputTerminalGap *  (index + 1);
		break;
	}
	case NORTH: {
		outputTerminalGap = width / (numberOfOutputTerminal + 1);
		point.x = data->x + outputTerminalGap *  (index + 1);
		point.y = data->y - 10;
		break;
	}
	default: break;
	}
}




int CMFCLogicSimulatorView::checkMouesPointOnComponent()
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int mouseX, mouseY;
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	//그려줄 좌표를 보정한다
	mouseX = point.x + nHorzScroll;
	mouseY = point.y + nVertScroll;

	int endX, endY;
	int startX, startY;
	COMPONENT_DATA* currentComponent;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		currentComponent = &pDoc->engineComponentData[i];
		//존재하지 않는것은 넘어간다
		if (currentComponent->id <= 0) { continue; }

		startX = currentComponent->x;
		startY = currentComponent->y;
		if (currentComponent->type == COMPONENT_TYPE_LIBRARY_BOX) {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 120;
		}
		else if (currentComponent->type == COMPONENT_TYPE_7SEGMENT) {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 120;
		}
		else {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 75;
		}

		//마우스가 해당 부품위에있는지 검사한다
		if (startX <= mouseX && mouseX <= endX &&
			startY <= mouseY && mouseY <= endY) {
			return i;
		}
	}

	return 0;
}

bool CMFCLogicSimulatorView::checkMouesPointOnTerminalPin(SELECTED_TERMINAL_INFO& selectedTerminalInfo)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int inputTerminalGap;
	int outputTerminalGap;
	CBitmap componentBitmap;
	CBitmap* oldBitmap;
	BITMAP bitmapInfo;
	COMPONENT_DATA* currentData;
	BOOL isInTerminalPin = false;
	CRgn terminalPinRgn;
	CPoint mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(&mousePoint);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	mousePoint.x += nHorzScroll;
	mousePoint.y += nVertScroll;
	CPoint TerminalPoint;

	int a, b;
	for (int ID = 0; ID < pDoc->engineComponentData.size(); ID++) {
		currentData = &pDoc->engineComponentData[ID];
		//존재하지 않는것은 넘어간다
		if (currentData->id <= 0) {continue;}

		currentObject = pDoc->logicSimulatorEngine.getComponentObject(ID);
		int numberOfInputTerminal = currentObject->numberOfInput();
		int numberOfOuputTerminal = currentObject->numberOfOutput();

		//인풋을 검사한다
		for (int  i= 0; i < numberOfInputTerminal ; i++) {
			getInputTerminalPoint(ID, TerminalPoint,i);
			a = TerminalPoint.x;
			b = TerminalPoint.y;
			terminalPinRgn.CreateEllipticRgn(
				a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
			if (terminalPinRgn.PtInRegion(mousePoint)) {
				isInTerminalPin = true;
				SELECTED_TERMINAL_INFO curInfo(ID, TERMINAL_TYPE_INPUT, i);
				copyTerminalInfo(curInfo, selectedTerminalInfo);
				currentSelectedTerminalPoint.x = a;
				currentSelectedTerminalPoint.y = b;
			};
			terminalPinRgn.DeleteObject();
		}
		//아웃풋을 검사한다
		for (int i = 0; i < numberOfOuputTerminal; i++) {
			getOutputTerminalPoint(ID, TerminalPoint, i);
			a = TerminalPoint.x;
			b = TerminalPoint.y;
			terminalPinRgn.CreateEllipticRgn(
				a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
			if (terminalPinRgn.PtInRegion(mousePoint)) {
				isInTerminalPin = true;
				SELECTED_TERMINAL_INFO curInfo(ID, TERMINAL_TYPE_OUTPUT, i);
				copyTerminalInfo(curInfo, selectedTerminalInfo);
				currentSelectedTerminalPoint.x = a;
				currentSelectedTerminalPoint.y = b;
			};
			terminalPinRgn.DeleteObject();
		}	
	}
	if (isInTerminalPin == false){
		currentSelectedTerminalPoint.x = 0;
		currentSelectedTerminalPoint.y = 0;
	}
	return isInTerminalPin;
}

bool CMFCLogicSimulatorView::checkMousePointOnConnectedWire()
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;

	COMPONENT_DATA* pCurrentData;
	CRgn connectedWireRgn;
	CPoint mousePoint;
	CPoint points[4];
	GetCursorPos(&mousePoint);
	ScreenToClient(&mousePoint);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	mousePoint.x += nHorzScroll;
	mousePoint.y += nVertScroll;
	ADJ_LIST* pGraph  = pDoc->logicSimulatorEngine.getConnectionGrahp();;
	int curID,nextID;
	CPoint A, B;
	bool ret = false;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].id <= 0) { continue; }
		pCurrentData = &pDoc->engineComponentData[i];
		curID = pCurrentData->id;
		
		for (int j = 0; j<(*pGraph)[i].size(); j++) {
			nextID = (*pGraph)[i][j].componentID;
			if (nextID <= 0) { continue; }

			//output 단자의 좌표를 가져온다
			getOutputTerminalPoint(curID, A, j);
			//input 단자의 좌표를 가져온다
			getInputTerminalPoint(nextID, B, (*pGraph)[i][j].terminalNumber);

			//좌표를 보정한다
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;

			getConnnectedWirePoints(points, A, B);
			connectedWireRgn.CreatePolygonRgn(points,4,WINDING);

			//영역안에 있는지 검사한다
			if (connectedWireRgn.PtInRegion(mousePoint)) {
				copyPoints(points, selectedConnectedWirePoints,4);
				ret = true;
				break;
			}
			connectedWireRgn.DeleteObject();

		}
		if (ret == true) { break; }
	}

	return ret;
}




void CMFCLogicSimulatorView::copyTerminalInfo(SELECTED_TERMINAL_INFO & source, SELECTED_TERMINAL_INFO & destination)
{
	destination.componentID = source.componentID;
	destination.terminalType = source.terminalType;
	destination.terminalNumber = source.terminalNumber;
}

void CMFCLogicSimulatorView::copyPoints(CPoint * source, CPoint * destination,int size)
{
	for (int i = 0; i < size; i++) {
		destination[i].x = source[i].x;
		destination[i].y = source[i].y;
 	}
}

