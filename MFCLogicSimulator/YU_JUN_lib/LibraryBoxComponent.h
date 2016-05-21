#pragma once
//조상 클래스 추가
#include "ComponentObject.h"
//논리 게이트 헤더 헤더추가
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
#include "NANDGateComponent.h"
#include "NORGateComponent.h"
#include "NOTGateComponent.h"
#include "XORGateComponent.h"
//와이어 헤더 추가
#include "WireComponet.h"
#include <vector>


class CLibraryBox : CComponentObject {

private:
	vector<CComponentObject> componentList;
	vetor<CComponentObject>input
public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	








};