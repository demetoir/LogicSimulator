#pragma once
#include "ComponentObject.h"

#define ONE_BIT_LAMP_ON true
#define ONE_BIT_LAMP_OFF false
enum ONE_BIT_LAMP_STATE{LAMP_ON,LAMP_OFF};
class COneBitLampComponent :CComponentObject {
private:
	ONE_BIT_LAMP_STATE lampState;
public:
	COneBitLampComponent();
	COneBitLampComponent(COneBitLampComponent& object);
	~COneBitLampComponent();

	void setLampState(bool _lampState);
	void setLampON();
	void setLampOFF();
	ONE_BIT_LAMP_STATE getLampState();



};