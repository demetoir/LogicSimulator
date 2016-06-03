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
#define TERMINAL_PIN_HALF_SIZE  8
#define HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE  15
#define SIZE_OF_COMPONENT_BITMAP 20


class CMFCLogicSimulatorView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMFCLogicSimulatorView();
	DECLARE_DYNCREATE(CMFCLogicSimulatorView)

// 특성입니다.
public:
	CMFCLogicSimulatorDoc* GetDocument() const;

	enum MouseButtonFlag {
		NBUTTON = NULL,							// 마우스 버튼이 눌리지 않은 상태
		LBUTTON = MK_LBUTTON,					// 좌클릭 상태
		RBUTTON = MK_RBUTTON,					// 우클릭 상태
		MBUTTON = MK_MBUTTON					// 가운데 클릭 상태
	};
	MouseButtonFlag m_MouseButtonFlag;			// 마우스 버튼이 클릭되어있는 상태 플래그
	
	enum ModeFlag {
		NONE = NULL,	// 모드 버튼이 눌리지 않은 상태
		//EDIT = ID_INSERT_LINE		// 편집 모드 버튼
	};
	ModeFlag m_ModeFlag;

// 작업입니다.
public:
	CRect rlClientRect;
	CFileView* p_toolbox; // tool box 포인터
						  
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCLogicSimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:

	//모드 그리는 함수들
	//모든 컴포넌트 를 그림
	void drawComponent(CDC &DC);


	//와이어들을 그림
	void drawComponentWire(CDC &DC);
	
	//부품 추가 모드일떄 움직이면서 보여주는거
	void drawAddingComponent(CDC &DC);

	//화면에 있는 선택 한부품을 강조하는거
	void drawHighlightSelectedComponent(CDC &DC);

	//화면에 있는 선택 한부품을 강조하는거
	void drawMassage( CDC &DC);

	//부품의 타입에 해당하는 부품의 비트맵 아이디를 가져온다
	int getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction);

	//현재 마우스가 부품위에 있는지 검사한다
	int checkMouesPointOnComponent();
	CPoint currentSelectedTerminalPoint;
	CPoint oldSelectedTerminalPoint;
	bool checkMouesPointOnTerminalPin(SELECTED_TERMINAL_INFO& selectedTerminalInfo);

	//부품 몸체를 강조하는 부분을 그린다
	void drawHighlightComponentBody(CDC& DC, int x, int y, int bitmapWidth, int bitmapHeight);

	//부품의  단자를 강조하는 부분을 그린다
	void drawHighlightComponentTerminalPin(CDC& DC);
	
	
	//단자를 그린다
	void drawComponentTermialPin(CDC& DC, int x, int y, COMPONENT_DIRECTION direction, 
		int componentWidth, int componentHeight, int numberOfInputTerminal, int numberOfOutputTerminal);
	//부품의 몸체를 그린다
	void drawComponentBody(CDC& DC, int x, int y, COMPONENT_DIRECTION direction, 
		int componentWidth, int componentHeight);


	CBitmap componentBitmap[SIZE_OF_COMPONENT_BITMAP];


	bool isHighlightComponentMode;
	int highlightComponentIndex;
	bool isHighlightTerminalPin;

	SELECTED_TERMINAL_INFO firstSelectedTerminalPin;
	SELECTED_TERMINAL_INFO secondSelectedTerminalPin;
	SELECTED_TERMINAL_INFO dummy_SELECTED_TERMINAL_INFO;
	
	void copyTerminalInfo(SELECTED_TERMINAL_INFO& source, SELECTED_TERMINAL_INFO& destination);

	void drawConnectingWire(CDC& DC);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFCLogicSimulatorView.cpp의 디버그 버전
inline CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const
   { return reinterpret_cast<CMFCLogicSimulatorDoc*>(m_pDocument); }
#endif

