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
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCLogicSimulatorView 생성/소멸



CMFCLogicSimulatorView::CMFCLogicSimulatorView()
{
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
	return CScrollView::PreCreateWindow(cs);
}



void CMFCLogicSimulatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
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
	COMPONENT_CONENTION_INFO A, B;
	CPropertiesWnd* pPropWnd = pFrame->getCPropertiesWnd();

	//지금 부품 추가 모드이면
	switch (pDoc->operationMode) {
	case OPERATION_MODE_ADDING_COMPONENT: {
		//선택한 부품을 도큐에 추가한다
		pDoc->addComponentToEngine(point.x + nHorzScroll, point.y + nVertScroll,pDoc->currentSelectedItemIndex );
		pDoc->operationMode = OPERATION_MODE_NONE;
		//tree view 부품 선택모드를 해제하는 메세지를 날린다		
		((pFrame->getCFileView())->getCFileViewTree())->SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW);
		Invalidate();
		break;
	}
	case OPERATION_MODE_SELECT_COMPONENT: {
		int newIndex = checkMouesPointOnComponent();
		// 속성창 지움
		pPropWnd->removePropertiesList();
		//선택이 취소됨
		if (newIndex <=0) {
			highlightedComponentIndex = 0;
			pDoc->operationMode = OPERATION_MODE_NONE;
		}
		// 다른 부품을 선택함
		else if (newIndex != highlightedComponentIndex) {
			highlightedComponentIndex = newIndex;
			pDoc->selectedComponentID = newIndex;
			pPropWnd->addPropertiesList();
		}
		Invalidate();
		break;
	}	
	case OPERATION_MODE_CONNECTING_COMPONENT: {
		bool isInTerminalPin = checkMouesPointOnTerminalPin(selectedTerminalInfo);
		//다른곳을 클릭하였다 해제한다
		if (isInTerminalPin == true) {

			bool isConnected = false;
			checkMouesPointOnTerminalPin(selectedTerminalInfo);			
			//연결해본다
			isConnected = pDoc->connectComponent(selectedTerminalInfo,
				firstSelectedTerminalPin);
			
			//안되면 부품간 직접 연결인지 확인하고 연결해본다
			if (isConnected == false) {
				int aID = selectedTerminalInfo.componentID;
				int bID = firstSelectedTerminalPin.componentID;
				int aX = pDoc->engineComponentData[aID].x;
				int aY = pDoc->engineComponentData[aID].y;
				int bX = pDoc->engineComponentData[bID].x;
				int bY = pDoc->engineComponentData[bID].y;
				int newX = bX + (aX - bX) / 2;
				int newY = bY + (aY - bY) / 2;
				bool isdirectConnected = 0;
				int id;
				bool wireInputSide;
				bool wireOuputSide;
				COMPONENT_CONENTION_INFO WireInput(0, TERMINAL_TYPE_INPUT, 0);
				COMPONENT_CONENTION_INFO WireOutput(0, TERMINAL_TYPE_OUTPUT, 0);

				//wire 부품을 만들어본다
				id = pDoc->addComponentToEngine(newX, newY, ITEM_WIRE);
				WireInput.componentID = id;
				WireOutput.componentID = id;
				//다이렉트 A->B 방향으로해본다
				wireInputSide = pDoc->connectComponent(selectedTerminalInfo, WireInput);
				wireOuputSide = pDoc->connectComponent(firstSelectedTerminalPin, WireOutput);
				if (wireInputSide == false || wireOuputSide == false) {
					isdirectConnected = false;
					pDoc->deleteComponentToEngine(id);
				}
				//wire 부품을 만들어본다
				id = pDoc->addComponentToEngine(newX, newY, ITEM_WIRE);
				WireInput.componentID = id;
				WireOutput.componentID = id;
				//다이렉트 B->A 방향으로해본다
				wireInputSide = pDoc->connectComponent(firstSelectedTerminalPin, WireInput);
				wireOuputSide = pDoc->connectComponent(selectedTerminalInfo, WireOutput);
				if (wireInputSide == false || wireOuputSide == false) {
					isdirectConnected = false;
					pDoc->deleteComponentToEngine(id);
				}
			}			
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
		break;
	}
	case OPERATION_MODE_NONE: {
		highlightedComponentIndex = checkMouesPointOnComponent();
		pDoc->selectedComponentID = highlightedComponentIndex;
		if (highlightedComponentIndex > 0) {
			pDoc->operationMode = OPERATION_MODE_SELECT_COMPONENT;
			// 하이라이트 시 속성창 띄워줌
			pPropWnd->addPropertiesList();
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
		//연결선을 눌럿을때
		ishighlightConnectedWire = checkMousePointOnConnectedWire(A,B);
		if (ishighlightConnectedWire == true) {
			pDoc->operationMode = OPERATION_MODE_SELECT_WIRE;
			copyConnectionInfo(A, pDoc->selectedconnectionInfoA);
			copyConnectionInfo(B, pDoc->selectedconnectionInfoB);
			Invalidate();
		}	
		break;
	}	
	case OPERATION_MODE_VAlUE_CHANGE: {
		//선택한 부품이 
		int selectedComponentID = checkMouesPointOnComponent();
		if (selectedComponentID >0) {
			changeComponentValue(selectedComponentID);
			Invalidate();
		}
		break;
	}
	case OPERATION_MODE_SELECT_WIRE: {
		ishighlightConnectedWire= checkMousePointOnConnectedWire(A,B);
		if (ishighlightConnectedWire == false) {
			pDoc->operationMode = OPERATION_MODE_NONE;
			COMPONENT_CONENTION_INFO dummy;
			copyConnectionInfo(dummy, pDoc->selectedconnectionInfoA);
			copyConnectionInfo(dummy, pDoc->selectedconnectionInfoB);			
		}
		else {
			copyConnectionInfo(A, pDoc->selectedconnectionInfoA);
			copyConnectionInfo(B, pDoc->selectedconnectionInfoB);
		}
		Invalidate();
		break;
	}
	default: {


		break;}
	}
	Invalidate();
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMFCLogicSimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
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

	memDC.CreateCompatibleDC(&dc);
	newBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&newBitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	//메모리에다가 그리기시작
	{
		//좌표 출력
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		int nVertScroll = GetScrollPos(SB_VERT);
		int nHorzScroll = GetScrollPos(SB_HORZ);
		CString str;
 		str.Format( _T("%d, %d"), point.x + nHorzScroll, point.y + nVertScroll);
		memDC.TextOutW(100+nHorzScroll, 100+ nVertScroll, str);

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
			
			if (pDoc->operationMode == OPERATION_MODE_SELECT_WIRE) {
				drawHighlightSelectedconnectedWire(memDC);
			}
			
			if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
				drawConnectingWire(memDC);
			}
			//화면에 메세지를 띄어주는것
			drawMassage(memDC);
		}
		//미니맵을 그린다
		//drawMiniMap(memDC);
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
	CScrollView::OnMouseMove(nFlags, point);	
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
			highlightComponent = &pDoc->engineComponentData[highlightedComponentIndex];
			highlightComponent->x = point.x+ nHorzScroll;
			highlightComponent->y = point.y+ nVertScroll;
			Invalidate();
		}
	}	
	isHighlightTerminalPin = checkMouesPointOnTerminalPin(highlightedTerminalPinInfo);	
	Invalidate();
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
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	for (int ID = 0; ID < pDoc->engineComponentData.size(); ID++) {
		//존재하지 않는것은 넘어간다
		if (pDoc->engineComponentData[ID].id <= 0) {
			continue;
		}		
		// 터미널 핀을 그린다
		drawComponentTermialPin(DC, ID);

		//부품의 몸체를 그린다
		drawComponentBody(DC, ID);		
	}
}

void CMFCLogicSimulatorView::drawConnectedWire(CDC & DC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	ADJ_LIST* OutputGrahp;
	ADJ_LIST* inputGrahp;
	OutputGrahp = pDoc->logicSimulatorEngine.getOutputGrahp();
	inputGrahp = pDoc->logicSimulatorEngine.getInputGrahp();
	COMPONENT_DATA* pCurrentComponent;

	CPen penOff, penOn;
	penOff.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	penOn.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	CPen* oldPen = NULL;

	int curID;
	int nextID;
	CPoint A, B;
	CComponentObject* pCurrentObject;
	
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].id <= 0) { continue; }
		pCurrentComponent = &pDoc->engineComponentData[i];
		curID = pCurrentComponent->id;

		//wire 가 아니면 스킵한다
		if (pCurrentComponent->type != COMPONENT_TYPE_WIRE) { continue; }

		pCurrentObject = pDoc->logicSimulatorEngine.getComponentObject(curID);
		//연결할 선을 그린다		
		if (pCurrentObject->getOutputValue(0) == true) {
			oldPen = DC.SelectObject(&penOn);
		}
		else {
			oldPen = DC.SelectObject(&penOff);
		}
		for (int j = 0; j<(*OutputGrahp)[i].size(); j++) {
			nextID = (*OutputGrahp)[i][j].componentID;
			if (nextID <= 0) { continue; }
			//output 단자의 좌표를 가져온다
			getOutputTerminalPoint(curID,A, j);
			//input 단자의 좌표를 가져온다
			getInputTerminalPoint(nextID, B, (*OutputGrahp)[i][j].terminalNumber);
			//좌표를 보정한다
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;
			DC.MoveTo(A);
			DC.LineTo(B);		
		}
		for (int j = 0; j<(*inputGrahp)[i].size(); j++) {
			nextID = (*inputGrahp)[i][j].componentID;
			if (nextID <= 0) { continue; }
			//output 단자의 좌표를 가져온다
			getInputTerminalPoint(curID, A, j);
			//input 단자의 좌표를 가져온다
			getOutputTerminalPoint(nextID, B, (*inputGrahp)[i][j].terminalNumber);
			//좌표를 보정한다
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;
			DC.MoveTo(A);
			DC.LineTo(B);
		}
	}
	if (oldPen != NULL) {
		DC.SelectObject(oldPen);
	}

}

void CMFCLogicSimulatorView::drawAddingComponent(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	COMPONENT_TYPE type = pDoc->getCurrentSelectedComponentType();
	LIBRARYBOX_TYPE libType = pDoc->getCurrentSelectedComponentlibraryBoxType();
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;

	if (type == COMPONENT_TYPE_NONE)
		return;

	//타입에 맞는 부품의 비트맵 아이디를 가져오고 로드한다
	componentBitmap.LoadBitmapW(getBitmapIDByComponentType(type,EAST, libType));
	componentBitmap.GetBitmap(&bitmapInfo);

	//부품을 그린다
	oldBitmap = memDC.SelectObject(&componentBitmap);
	DC.BitBlt(point.x, point.y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

	//가져온 비트맵을 제거한다
	componentBitmap.DeleteObject();
}

void CMFCLogicSimulatorView::draw7SegmentInputBar(CDC &DC, CPoint point, COMPONENT_DIRECTION direction)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x = point.x;
	int y = point.y;
	
	CPen pen;
	pen.CreatePen(PS_DOT, 5, RGB(0, 0, 0));
	CPen* oldPen = DC.SelectObject(&pen);

	switch (direction) {
	case EAST: {
		x += 45;
		y -= 35;
		DC.Rectangle(x, y, 
			x + SEVEN_SEGMENT_INPUT_BAR_WIDTH, 
			y + SEVEN_SEGMENT_INPUT_BAR_HIGHT);
		break; 
	}
	case SOUTH: {
		x -= 55;
		y += 75;
		DC.Rectangle(x, y, 
			x + SEVEN_SEGMENT_INPUT_BAR_HIGHT, 
			y + SEVEN_SEGMENT_INPUT_BAR_WIDTH);
		break;
	}
	case WEST: {
		x -= 30;
		y -= 35;
		DC.Rectangle(x, y, 
			x + SEVEN_SEGMENT_INPUT_BAR_WIDTH, 
			y + SEVEN_SEGMENT_INPUT_BAR_HIGHT);
		break;
	}
	case NORTH: {
		x -= 55;
		y -= 30;
		DC.Rectangle(x, y, 
			x + SEVEN_SEGMENT_INPUT_BAR_HIGHT, 
			y + SEVEN_SEGMENT_INPUT_BAR_WIDTH);
		break;
	}
	}
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawInputTerminalPinLine(CDC & DC, int x, int y, COMPONENT_DIRECTION direction)
{
	switch (direction) {
	case EAST: {
		DC.MoveTo(x, y);
		DC.LineTo(x + 30, y);
		break;
	}
	case SOUTH: {
		DC.MoveTo(x, y);
		DC.LineTo(x , y+30);
		break;
	}
	case WEST: {
		DC.MoveTo(x, y);
		DC.LineTo(x -30, y);
		break;
	}
	case NORTH: {
		DC.MoveTo(x, y);
		DC.LineTo(x , y-30);
		break;
	}
	}
}

void CMFCLogicSimulatorView::drawOutputTerminalPinLine(CDC & DC, int x, int y, COMPONENT_DIRECTION direction)
{
	switch (direction) {
	case EAST: {
		DC.MoveTo(x, y);
		DC.LineTo(x - 30, y);
		break;
	}
	case SOUTH: {
		DC.MoveTo(x, y);
		DC.LineTo(x, y - 30);
		break;
	}
	case WEST: {
		DC.MoveTo(x, y);
		DC.LineTo(x + 30, y);
		break;
	}
	case NORTH: {
		DC.MoveTo(x, y);
		DC.LineTo(x, y + 30);
		break;
	}
	}
}

void CMFCLogicSimulatorView::drawMiniMap(CDC &DC)
{
	CRect rect;
	GetClientRect(rect);
	// 테두리 그린다음 전체 복사해와서 생기는 문제 발생
	//DC.Rectangle(9, 9, rect.Width() / 4 + 9, rect.Height() / 4 + 9);
	// 미니맵
	DC.StretchBlt(10, 10, rect.Width() / 4, rect.Height() / 4, &DC,
		10, 10, rect.Width(), rect.Height(), SRCCOPY);
	// 미니맵 테두리
	DC.MoveTo(9, 9);
	DC.LineTo(9, rect.Height() / 4 + 9);
	DC.MoveTo(9, 9);
	DC.LineTo(rect.Width() / 4 + 9, 9);
	DC.MoveTo(9, rect.Height() / 4 + 9);
	DC.LineTo(rect.Width() / 4 + 9, rect.Height() / 4 + 9);
	DC.MoveTo(rect.Width() / 4 + 9, 9);
	DC.LineTo(rect.Width() / 4 + 9, rect.Height() / 4 + 9);
}

void CMFCLogicSimulatorView::drawMassage(CDC & DC)
{
	//CMFCLogicSimulatorDoc* pDoc = GetDocument();
	//int nHorzScroll = GetScrollPos(SB_HORZ);
	//int nVertScroll = GetScrollPos(SB_VERT);
	//CString str;
	//int x = 200 - nHorzScroll;
	//int y = 300 - nVertScroll;
	//if (pDoc->isCurcuitOcillate == true) {
	//	str = "curcuit is ocillate\n";
	//	DC.TextOutW(x,y,str);	
	//}
}

void CMFCLogicSimulatorView::drawComponentTermialPin(CDC & DC, int ID)
{	
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	COMPONENT_DATA* currentData = &pDoc->engineComponentData[ID];
	CPoint TerminalPoint;	
	CPen pen;
	CPen* oldPen;
	int a, b;
	currentObject = pDoc->logicSimulatorEngine.getComponentObject(ID);
	CPoint point;
	int numberOfInputTerminal = currentObject->numberOfInput();
	int numberOfOutputTerminal = currentObject->numberOfOutput();

	//인풋핀을 그린다
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // 빨간색 펜 생성
	oldPen = DC.SelectObject(&pen);
	for (int i = 0; i < numberOfInputTerminal; i++) {
		getInputTerminalPoint(ID, point, i);
		a = point.x- nHorzScroll;
		b = point.y- nVertScroll;

		drawInputTerminalPinLine(DC, a, b, adjustDirection(currentData->type, currentData->direction));
		DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
			a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
	}
	DC.SelectObject(oldPen);
	pen.DeleteObject();

	//아웃풋 단자를 그린다
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // 빨간색 펜 생성
	oldPen = DC.SelectObject(&pen);
	for (int i = 0; i < numberOfOutputTerminal ; i++) {
		getOutputTerminalPoint(ID, point, i);
		a = point.x - nHorzScroll;
		b = point.y - nVertScroll;

		drawOutputTerminalPinLine(DC, a, b, adjustDirection(currentData->type, currentData->direction));
		DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
			a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
	}
	DC.SelectObject(oldPen);
	pen.DeleteObject();	
}

void CMFCLogicSimulatorView::drawComponentBody(CDC & DC, int ID)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x = pDoc->engineComponentData[ID].x - nHorzScroll;
	int y = pDoc->engineComponentData[ID].y - nVertScroll;
	COMPONENT_TYPE type = pDoc->engineComponentData[ID].type;
	COMPONENT_DIRECTION direction = pDoc->engineComponentData[ID].direction;
	LIBRARYBOX_TYPE libType = pDoc->engineComponentData[ID].libraryBoxType;
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;
	CComponentObject* pCurrentObject = pDoc->logicSimulatorEngine.getComponentObject(ID);
	int bitmapID = getBitmapIDByComponentType(type, direction, libType);
	adjustBitmapID( type , bitmapID , pCurrentObject);

	//타입에 맞는 부품의 비트맵 아이디를 가져오고 로드한다		
	componentBitmap.LoadBitmapW(bitmapID);
	componentBitmap.GetBitmap(&bitmapInfo);

	//부품을 그린다
	oldBitmap = memDC.SelectObject(&componentBitmap);
	DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

	if (type == COMPONENT_TYPE_7SEGMENT) {
		draw7SegmentInputBar(DC, CPoint(x, y), direction);
	}	
	
	//가져온 비트맵을 제거한다
	componentBitmap.DeleteObject();

	if (type == COMPONENT_TYPE_7SEGMENT) {
		DC.TextOutW(x + 15, y + 75, pDoc->engineComponentData[ID].label);
	}
	else {
		DC.TextOutW(x + 15, y + 15, pDoc->engineComponentData[ID].label);
	}
}

void CMFCLogicSimulatorView::drawConnectingWire(CDC & DC)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

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
	pen.CreatePen(PS_SOLID, 2, RGB(153, 0, 255));    // 펜 생성

	CPen* oldPen= DC.SelectObject(&pen);
	
	DC.Ellipse(x - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE,
		x + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE);
	DC.SelectObject(oldPen);
	pen.DeleteObject();
	CString str;
	if (HighlightedTerminalPinType == TERMINAL_TYPE_INPUT) {
		str.Format(_T("input %d"), HighlightedTerminalPinNumber);
	}
	else {
		str.Format(_T("output %d"), HighlightedTerminalPinNumber);
	}	
	DC.TextOutW(x+15, y+15, str);
}

void CMFCLogicSimulatorView::drawHighlightSelectedComponent(CDC & DC)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	COMPONENT_DATA* currentComponent = &pDoc->engineComponentData[highlightedComponentIndex];
	int x = currentComponent->x - nHorzScroll;
	int y = currentComponent->y - nVertScroll;

	if (currentComponent->type == COMPONENT_TYPE_LIBRARY_BOX) {
		drawHighlightComponentBody(DC, x, y, 120, 120);
	}
	else if (currentComponent->type == COMPONENT_TYPE_7SEGMENT) {
		drawHighlightComponentBody(DC, x, y, 45, 75);
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
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int nVertScroll = GetScrollPos(SB_VERT);

	int x = currentConnectedWirePoints[0].x - nHorzScroll;
	int y = currentConnectedWirePoints[0].y - nVertScroll;
	DC.MoveTo(x,y);
	for (int i = 1; i < 5; i++) {
		x = currentConnectedWirePoints[i % 4].x - nHorzScroll;
		y = currentConnectedWirePoints[i % 4].y - nVertScroll;
		DC.LineTo(x,y);
	}
	DC.SelectObject(oldPen);
}






int CMFCLogicSimulatorView::getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction, LIBRARYBOX_TYPE libraryBoxType)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
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
	int i = IDB_7SEGMENT_0000000;
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
		 
	case COMPONENT_TYPE_7SEGMENT:
		return IDB_7SEGMENT_0000000;
		break;




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
		return IDB_PIN_OFF_E;
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		return IDB_PROBE_OFF_E ;
		break;

	case COMPONENT_TYPE_WIRE:
		return IDB_COPPER_WIRE;
		break;
		

	case COMPONENT_TYPE_LIBRARY_BOX:
		if (libraryBoxType == LIBRARYBOX_TYPE_NOR) {
			return IDB_GATE_NOR_E + direction;
		}
		if (libraryBoxType == LIBRARYBOX_TYPE_NAND) {
			return IDB_GATE_NAND_E + direction;
		}
		if (libraryBoxType == LIBRARYBOX_TYPE_DFF) {
			return IDB_FF_DFF_E + direction;
		}
		if (libraryBoxType == LIBRARYBOX_TYPE_JKFF) {
			return IDB_FF_JKFF_E + direction;
		}
		if (libraryBoxType == LIBRARYBOX_TYPE_TFF) {
			return IDB_FF_TFF_E + direction;
		}
		else {
			return IDB_LIBBOX_E + direction;
		}
		break;
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

void CMFCLogicSimulatorView::get7SegmentInputTerminalPinPoint(CPoint &point, int id, int index)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument(); 
	COMPONENT_DATA *data = &pDoc->engineComponentData[id];

	int gap = SEVEN_SEGMENT_INPUT_BAR_HIGHT / 8;
	switch (data->direction) {
	case EAST:
		point.x = data->x +30 +35 +30;
		point.y = data->y - 35 + gap*(index +1);
		break;
	case SOUTH:
		point.x = data->x - 55 + gap*(index + 1);;
		point.y = data->y  +75 +30+15;

		break;
	case WEST:
		point.x = data->x -30 - 15;
		point.y = data->y - 35 + gap*(index + 1);
		break;
	case NORTH:
		point.x = data->x - 55 + gap*(index + 1);;
		point.y = data->y -30 -15;
		break;
	}
}

COMPONENT_DIRECTION CMFCLogicSimulatorView::adjustDirection(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction)
{
	int dir = direction;
	if (_type == COMPONENT_TYPE_7SEGMENT ||
		_type == COMPONENT_TYPE_CLOCK ||
		_type == COMPONENT_TYPE_ONE_BIT_LAMP ||
		_type == COMPONENT_TYPE_ONE_BIT_SWITCH) {
		dir = (dir + 2) % 4;
	}
	return (COMPONENT_DIRECTION)dir;
}

int CMFCLogicSimulatorView::adjustBitmapID(COMPONENT_TYPE type, int& bitmapID, CComponentObject* pCurrentObject)
{
	
	if (type == COMPONENT_TYPE_INPUT_PIN ||
		type == COMPONENT_TYPE_ONE_BIT_LAMP ||
		type == COMPONENT_TYPE_ONE_BIT_SWITCH ||
		type == COMPONENT_TYPE_OUTPUT_PIN) {
		bitmapID += pCurrentObject->getOutputValue(0);
	}
	else if (type == COMPONENT_TYPE_7SEGMENT) {
		int segmentValue = 0;
		for (int i = 0; i < 7; i++) {
			segmentValue = segmentValue *2;
			segmentValue += pCurrentObject->getOutputValue(i);

 		}
		bitmapID += segmentValue;

	}

	return bitmapID;
}

int CMFCLogicSimulatorView::getComponentHeight(COMPONENT_TYPE type, LIBRARYBOX_TYPE libraryBoxType)
{
	//세그먼트일때
	if (type == COMPONENT_TYPE_7SEGMENT) {
		return 120;
	}
	else if (type == COMPONENT_TYPE_LIBRARY_BOX) { 

			return 75;
		
	}
	else {
		return 75;
	}
}

int CMFCLogicSimulatorView::getComponentWidth(COMPONENT_TYPE type, LIBRARYBOX_TYPE libraryBoxType)
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
	int width = getComponentWidth(data->type,data->libraryBoxType);
	int Height = getComponentHeight(data->type, data->libraryBoxType);


	if (pDoc->engineComponentData[id].type == COMPONENT_TYPE_7SEGMENT) {
		get7SegmentInputTerminalPinPoint(point, id, index);
		return;
	}
	switch (adjustDirection(data->type, data->direction)) {
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
	int width = getComponentWidth(data->type, data->libraryBoxType);
	int Height = getComponentHeight(data->type, data->libraryBoxType);

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

	CBitmap componentBitmap;

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
				HighlightedTerminalPinType = TERMINAL_TYPE_INPUT;
				HighlightedTerminalPinNumber = i;
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
				HighlightedTerminalPinType = TERMINAL_TYPE_OUTPUT;
				HighlightedTerminalPinNumber = i;
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

bool CMFCLogicSimulatorView::checkMousePointOnConnectedWire(COMPONENT_CONENTION_INFO &AInfo, COMPONENT_CONENTION_INFO &BInfo)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	COMPONENT_DATA* pCurrentData;
	CRgn connectedWireRgn;
	CPoint mousePoint;
	CPoint points[4];
	GetCursorPos(&mousePoint);
	ScreenToClient(&mousePoint);
	mousePoint.x += GetScrollPos(SB_HORZ);
	mousePoint.y += GetScrollPos(SB_VERT);
	ADJ_LIST* pGraph  = pDoc->logicSimulatorEngine.getOutputGrahp();;
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

			getConnnectedWirePoints(points, A, B);
			connectedWireRgn.CreatePolygonRgn(points,4,WINDING);

			//영역안에 있는지 검사한다
			if (connectedWireRgn.PtInRegion(mousePoint)) {
				copyPoints(points, currentConnectedWirePoints,4);
				AInfo.componentID = curID;
				AInfo.terminalType = TERMINAL_TYPE_OUTPUT;
				AInfo.terminalNumber = j;
				BInfo.componentID = nextID;
				BInfo.terminalType = TERMINAL_TYPE_INPUT;
				BInfo.terminalNumber = (*pGraph)[i][j].terminalNumber;
				ishighlightConnectedWire = true;
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

void CMFCLogicSimulatorView::copyConnectionInfo(COMPONENT_CONENTION_INFO & source, COMPONENT_CONENTION_INFO & destination)
{
	destination.componentID = source.componentID;
	destination.terminalType = source.terminalType;
	destination.terminalNumber = source.terminalNumber;
}

void CMFCLogicSimulatorView::changeComponentValue(int id)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	COMPONENT_DATA* data = &pDoc->engineComponentData[id];
	CComponentObject * object= pDoc->logicSimulatorEngine.getComponentObject(id);
	
	if (data->type == COMPONENT_TYPE_INPUT_PIN||
		data->type == COMPONENT_TYPE_ONE_BIT_SWITCH) {

	//값을 변경한다
	bool val = object->getInputValue(0);
 	object->setInputValue(0, !val);
	}
}

bool CMFCLogicSimulatorView::checkIsPossibleDirectConnect(COMPONENT_CONENTION_INFO &A, COMPONENT_CONENTION_INFO &B)
{
	//둘중 하나가 논타입일뗴
	if (A.terminalType == TERMINAL_TYPE_NONE || B.terminalType == TERMINAL_TYPE_NONE) {
		return false;
	}
	if (A.terminalType == TERMINAL_TYPE_INPUT) {
		return false;
	}
		
	return false;
}

void CMFCLogicSimulatorView::startUpdating()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	str.Format(_T("in mfc logicsimulator view : start updating\n"));
	pOutput->addBuildWindowString(str);
	SetTimer(updateTimerID, updateTimer_TIME, NULL);
	CMFCLogicSimulatorDoc *pDoc = GetDocument();

	for (int i = 0; i < pDoc->engineComponentData.size();i++) {
		if (pDoc->engineComponentData[i].type == COMPONENT_TYPE_CLOCK) {
			clockEdge[i] = pDoc->engineComponentData[i].clockEdge;
			SetTimer(updateTimerID + i+1, 1000/pDoc->engineComponentData[i].hz, NULL);
		}
	}
}

void CMFCLogicSimulatorView::stopUpdating()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	str.Format(_T("in mfc logicsimulator view : end updating\n"));
	pOutput->addBuildWindowString(str);
	KillTimer(updateTimerID);
	
	//CChildFrame *pChildFrame = pFrame->get
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].type == COMPONENT_TYPE_CLOCK) {
			clockEdge[i] = (bool)pDoc->engineComponentData[i].clockEdge;
			KillTimer(updateTimerID + i+1 );
		}
	}

	Invalidate();
}



void CMFCLogicSimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CScrollView::OnTimer(nIDEvent);
	switch (nIDEvent) {
	case updateTimerID:
		//회로가 진동한다
		pDoc->logicSimulatorEngine.update();
		if (pDoc->logicSimulatorEngine.checkOscillation() == true) {
			KillTimer(updateTimerID);
			pDoc->isCurcuitOcillate = true;
			pDoc->logicSimulatorEngine.setOffOscillation();
			AfxMessageBox(_T("진동 발생이 확실합니다"));
			SendMessage(ID_BUTTONCONTINUE, 0, 0);
			SendMessage(ID_BUTTONSTOP, 0, 0);
			for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
				if (pDoc->engineComponentData[i].type == COMPONENT_TYPE_CLOCK) {
					KillTimer(updateTimerID+i+1);
				}
			}
		}
		Invalidate();
	}
	int clockNumber = 0;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
 
		if (nIDEvent == updateTimerID+i+1) {
			if (clockEdge[i]==true) {
				pDoc->logicSimulatorEngine.setClockValue(clockNumber, false);
				clockEdge[i] = false;
			}
			else {
				pDoc->logicSimulatorEngine.setClockValue(clockNumber,true);
				clockEdge[i] = true;
			}
			pDoc->logicSimulatorEngine.update();
			Invalidate();
			
		}
		if (pDoc->engineComponentData[i].type == COMPONENT_TYPE_CLOCK) {
			clockNumber++;
		}
	}

}



//  부품삭제 연결해제 라이브러리박스 로드 세이브하기  라벨 붙이기  단자 라벨 붙이기  그래프 그리기