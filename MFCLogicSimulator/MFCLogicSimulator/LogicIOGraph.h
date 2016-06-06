#pragma once
#include "afxwin.h"

#define MIN_Y 0
#define MAX_Y 1
#define DEFAULT_RATIO 10

class LogicIOGraph :
	public CWnd
{
public:
	LogicIOGraph();
	~LogicIOGraph();

	int m_minY;
	int m_maxY;

	int m_x;
	int m_xRatio;

	int m_nShiftPoint;

	int m_clockCount;
	int m_clockIn;

	CString XUnits; // time
	CString YUnits; // in/out value
	CRect m_clientRect;
	CRect m_graphRect;
	CFont m_font;

	void drawPoint();
	void ResetGraph();
	void setRangeXY(int _minY = MIN_Y, int _maxY = MAX_Y, int X_ratio = DEFAULT_RATIO);
	void setGraphLabel(CString _XUnits = _T("Time"), CString _YUnits = _T("Value"));

	typedef struct PlotDataStruct
	{
		int dCurrentPositionY;    // current position
		int dPreviousPositionY;   // previous position
		int	nPrevX;
		int		iRatio;
		CString graphLabel;
	} PlotData_t;

	PlotData_t* m_PlotData;
};

