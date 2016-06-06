#include "stdafx.h"
#include "LogicIOGraph.h"

//http://unikys.tistory.com/43
//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=1069

LogicIOGraph::LogicIOGraph()
{
	m_xPos = 10;
	m_yPos = 15;
	m_xRatio = 10;

	m_nShiftPoint = 10;

	m_clockCount = 20;
	m_clockIn = 0;
}


LogicIOGraph::~LogicIOGraph()
{
}

void LogicIOGraph::drawPoint(CDC* pDC, CPoint point)
{
	CPaintDC dc(this);

	dc.FillSolidRect(m_clientRect, RGB(255, 255, 255));

	// 그래프가 그려질 그래프 영역을 검정색으로 채운다.
	dc.FillSolidRect(m_graphRect, RGB(0, 0, 0));

	// 그래프 영역의 사각형 속성을 지정한다.
	dc.Draw3dRect(m_graphRect, RGB(192, 192, 192), RGB(255, 255, 255));

	int i = 0;
	CRect r;
	CString str;
	// 폰트를 설정한다.
	CFont *p_oldFont = dc.SelectObject(&m_font);

	// 그래프를 그릴 때 사용할 브로쉬와 펜을 생성한다.
	CBrush dataBrush(RGB(255, 255, 0)), *p_oldBrush = NULL;
	CPen scalePen(PS_SOLID, 1, RGB(0, 128, 255)), /* 그래프 눈금 그릴 펜(축) */ *p_oldPen = NULL;
	CPen gridPen(PS_SOLID, 1, RGB(64, 64, 64)); /* 그래프 눈금 그릴 펜(값) */
	CPen dataPen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen pointPen(PS_SOLID, 1, RGB(255, 255, 0));

	// 글자색을 지정한다.
	dc.SetTextColor(RGB(0, 128, 255));
	// 글자의 배경색을 지정한다.
	dc.SetBkColor(RGB(232, 232, 208));

	m_clockIn = m_graphRect.Width() / (m_clockCount + 1);
	// x축 눈금 그린다.
	for (i = 0; i < m_clockCount; i++) {
		// 눈금과 수치선을 그릴 x좌표를 설정한다.
		m_xPos = m_graphRect.left + m_clockIn*(i + 1);

		// 눈금을 그릴 펜을 설정한다.
		p_oldPen = dc.SelectObject(&scalePen);

		// x축의 눈금을 그린다.
		dc.MoveTo(int(m_xPos), m_graphRect.left + 1);
		dc.LineTo(int(m_xPos), m_graphRect.left + 5);

		// 가로선을 그릴 펜을 설정한다.
		dc.SelectObject(&gridPen);
		// 그래프 영역의 수치를 나타내는 가로선을 그린다.
		dc.MoveTo(int(m_xPos), m_graphRect.right + 2);
		dc.LineTo(int(m_xPos), m_graphRect.left - 2);

		// 기존의 펜으로 대체한다.
		dc.SelectObject(p_oldPen);
		// 눈금의 수치(횟수)를 문자로 출력한다.
		str.Format(_T("%d초"), i + 1);
		r.SetRect(int(m_xPos - 40), m_graphRect.left + 10, int(m_xPos + 40), m_graphRect.left + 30);
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	m_clockIn = m_graphRect.Height() / (m_clockCount + 1);
	// y축 눈금 그린다.
	for (i = 0; i <= 1 /* 출력은 0, 1값을 가진다.*/; i++) {
		// 눈금과 수치선을 그릴 y좌표를 설정한다.
		m_yPos = m_graphRect.bottom + m_clockIn*(i + 1);

		// 눈금을 그릴 펜을 설정한다.
		p_oldPen = dc.SelectObject(&scalePen);

		// y축의 눈금을 그린다.
		dc.MoveTo(int(m_yPos), m_graphRect.bottom + 1);
		dc.LineTo(int(m_yPos), m_graphRect.bottom + 5);

		// 세로선을 그릴 펜을 설정한다.
		dc.SelectObject(&gridPen);
		// 그래프 영역의 수치를 나타내는 세로선을 그린다.
		dc.MoveTo(int(m_yPos), m_graphRect.top + 2);
		dc.LineTo(int(m_yPos), m_graphRect.bottom - 2);

		// 기존의 펜으로 대체한다.
		dc.SelectObject(p_oldPen);
		// 눈금의 수치(횟수)를 문자로 출력한다.
		str.Format(_T("%d val"), i);
		r.SetRect(int(m_yPos - 40), m_graphRect.bottom + 10, int(m_yPos + 40), m_graphRect.bottom + 30);
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	// 데이터 받아서 그래프 그린다.


	// 기존의 펜과 브러쉬로 대체한다.
	dc.SelectObject(p_oldPen);
	dc.SelectObject(p_oldBrush);

	// 기존의 폰트로 대체한다.
	dc.SelectObject(p_oldFont);

	// 생성한 펜과 브러쉬를 제거한다.
	scalePen.DeleteObject();
	gridPen.DeleteObject();
	dataPen.DeleteObject();
	dataBrush.DeleteObject();
	pointPen.DeleteObject();


}

void LogicIOGraph::ResetGraph()
{

}

void LogicIOGraph::setRangeXY(int _minY, int _maxY, int X_ratio)
{
	m_minY = _minY;
	m_maxY = _maxY;
	m_xRatio = X_ratio;
}

void LogicIOGraph::setGraphLabel(CString _XUnits, CString _YUnits)
{
	XUnits = _XUnits;
	YUnits = _YUnits;
}
