#include "stdafx.h"
#include "LogicIOGraph.h"
//http://unikys.tistory.com/43
//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=1069
LogicIOGraph::LogicIOGraph()
{
}


LogicIOGraph::~LogicIOGraph()
{
}

void LogicIOGraph::drawPoint()
{


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
