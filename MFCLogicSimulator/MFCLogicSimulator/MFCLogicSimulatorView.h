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

// MFCLogicSimulatorView.h : CMFCLogicSimulatorView 클래스의 인터페이스
//

//gdi+ 사용법
///http://redstory2010.tistory.com/157



#pragma once
#include "ViewTree.h"
#include "FileView.h" // tree item 관련하여 추가
#include "PropertiesWnd.h" // 속성창 옵션 수정 관련하여 추가
#include "MFCLogicSimulatorDoc.h"

// 스크롤 생성
// http://moguwai.tistory.com/entry/CView-CScrollView%EB%A1%9C-%EC%A0%84%ED%99%98

#define HIGHLIGHT_EDGE_GAP 5
#define	SELECTED_TERMINAL_INFO COMPONENT_CONENTION_INFO
#define CONNECTING_WIRE_ELLIPSE_HALF_SIZE 3
#define TERMINAL_PIN_HALF_SIZE 8
#define HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE  13
#define SIZE_OF_COMPONENT_BITMAP 20
#define SIZE_OF_VIEW_X 4000
#define SIZE_OF_VIEW_Y 2000
#define PI 	3.14159265358979323846
#define HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH 10
#define SEVEN_SEGMENT_INPUT_BAR_WIDTH 30
#define SEVEN_SEGMENT_INPUT_BAR_HIGHT 160
#define updateTimerID 999

#define updateTimer_TIME 100
#define SEVEN_SEGMENT_INPUT_BAR_WIDTH 30
#define SEVEN_SEGMENT_INPUT_BAR_HIGHT 160

enum MouseButtonFlag {
	NBUTTON = NULL,							// 마우스 버튼이 눌리지 않은 상태
	LBUTTON = MK_LBUTTON,					// 좌클릭 상태
	RBUTTON = MK_RBUTTON,					// 우클릭 상태
	MBUTTON = MK_MBUTTON					// 가운데 클릭 상태
};
enum ModeFlag {
	NONE = NULL,	// 모드 버튼이 눌리지 않은 상태
					//EDIT = ID_INSERT_LINE		// 편집 모드 버튼
};

class CMFCLogicSimulatorView : public CScrollView
{
public:
	MouseButtonFlag m_MouseButtonFlag;			// 마우스 버튼이 클릭되어있는 상태 플래그
	ModeFlag m_ModeFlag;

	CRect rlClientRect;
	CFileView* p_toolbox; // tool box 포인터

	CBitmap componentBitmap[SIZE_OF_COMPONENT_BITMAP];
	bool isHighlightComponentMode;
	int highlightedComponentIndex;
	bool isHighlightTerminalPin;
	int HighlightedTerminalPinType;
	int HighlightedTerminalPinNumber;
	bool ishighlightConnectedWire;
	SELECTED_TERMINAL_INFO firstSelectedTerminalPin;
	SELECTED_TERMINAL_INFO secondSelectedTerminalPin;
	SELECTED_TERMINAL_INFO dummy_SELECTED_TERMINAL_INFO;
	SELECTED_TERMINAL_INFO highlightedTerminalPinInfo;
	CPoint currentSelectedTerminalPoint;
	CPoint oldSelectedTerminalPoint;
	CPoint currentConnectedWirePoints[4];
	bool clockEdge[1000];
	


protected: // serialization에서만 만들어집니다.
	CMFCLogicSimulatorView();
	DECLARE_DYNCREATE(CMFCLogicSimulatorView)
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFilePrintPreview();
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMFCLogicSimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 특성입니다.
public:
	CMFCLogicSimulatorDoc* GetDocument() const;

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	//모드 그리는 함수들
	//모든 컴포넌트 를 그림
	void drawComponent(CDC &DC);
	//와이어들을 그림
	void drawConnectedWire(CDC &DC);	
	//부품 추가 모드일떄 움직이면서 보여주는거
	void drawAddingComponent(CDC &DC);
	//화면에 있는 선택 한부품을 강조하는거
	void drawMassage(CDC &DC);
	//부품의 단자를 그린다
	void drawComponentTermialPin(CDC& DC, int ID);
	//부품의 몸체를 그린다
	void drawComponentBody(CDC & DC, int ID);
	//연결하는중일때의 선을 그린다
	void drawConnectingWire(CDC& DC);
	//부품 몸체를 강조하는 부분을 그린다
	void drawHighlightComponentBody(CDC& DC, int x, int y, int bitmapWidth, int bitmapHeight);
	//부품의  단자를 강조하는 부분을 그린다
	void drawHighlightComponentTerminalPin(CDC& DC);
	//화면에 있는 선택 한부품을 강조하는거
	void drawHighlightSelectedComponent(CDC &DC);
	//연결된선을 강조하는 부분을 그린다
	void drawHighlightSelectedconnectedWire(CDC &DC);
	void draw7SegmentInputBar(CDC &DC,CPoint point , COMPONENT_DIRECTION direction);
	void drawInputTerminalPinLine(CDC &DC, int x, int y, COMPONENT_DIRECTION direction);
	void drawOutputTerminalPinLine(CDC &DC, int x, int y, COMPONENT_DIRECTION direction);
	//미니맵을 그린다
	void drawMiniMap(CDC &DC);
	//타입으로 부품의 높이를 구한다
	int getComponentHeight(COMPONENT_TYPE type, LIBRARYBOX_TYPE libraryBoxType);
	int getComponentWidth(COMPONENT_TYPE type, LIBRARYBOX_TYPE libraryBoxType);
	//들어온 부품의 인풋 터미널 핀좌표을 반환한다 
	void getInputTerminalPoint(int id, CPoint &point,int index);
	//들어온 부품의 인풋 터미널 핀을 반환한다 
	void getOutputTerminalPoint(int id, CPoint &point,int index);
	//부품의 타입에 해당하는 부품의 비트맵 아이디를 가져온다
	int getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction, LIBRARYBOX_TYPE libraryBoxType);
	//연결할 줄의 좌표를 구한다
	void getConnnectedWirePoints(CPoint* points,CPoint A ,CPoint B);
	//세그먼트의 인풋핀 좌표를 구한다
	void get7SegmentInputTerminalPinPoint(CPoint &point, int id ,int index);
		
	COMPONENT_DIRECTION adjustDirection(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction);
	int adjustBitmapID(COMPONENT_TYPE type, int& bitmapID, CComponentObject* pCurrentObject);
	
	//현재 마우스가 부품위에 있는지 검사한다
	int checkMouesPointOnComponent();
	bool checkMouesPointOnTerminalPin(SELECTED_TERMINAL_INFO& selectedTerminalInfo);
	bool checkMousePointOnConnectedWire(COMPONENT_CONENTION_INFO &A, COMPONENT_CONENTION_INFO &B);

	void copyTerminalInfo(SELECTED_TERMINAL_INFO& source, SELECTED_TERMINAL_INFO& destination);
	void copyPoints(CPoint* source, CPoint* destination,int size);	
	void copyConnectionInfo(COMPONENT_CONENTION_INFO &source, COMPONENT_CONENTION_INFO &destination);
	
	void changeComponentValue(int id);

	bool checkIsPossibleDirectConnect(COMPONENT_CONENTION_INFO &A, COMPONENT_CONENTION_INFO &B);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void startUpdating();
	void stopUpdating();
};

#ifndef _DEBUG  // MFCLogicSimulatorView.cpp의 디버그 버전
inline CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const
   { return reinterpret_cast<CMFCLogicSimulatorDoc*>(m_pDocument); }
#endif

