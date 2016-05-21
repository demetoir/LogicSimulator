#pragma once
#include "ComponentObject.h"

#define ONE_BIT_LAMP_ON true
#define ONE_BIT_LAMP_OFF false
#define ONE_BIT_INPUT_TERMINAL_NUMBER 1
#define ONE_BIT_OUTPUT_TERMINAL_NUMBER 0

enum ONE_BIT_LAMP_STATE{LAMP_ON,LAMP_OFF};
class COneBitLampComponent :public CComponentObject {
private:
	ONE_BIT_LAMP_STATE lampState;
public:
	COneBitLampComponent();
	COneBitLampComponent(COneBitLampComponent& object);
	~COneBitLampComponent();

	void setLampState(ONE_BIT_LAMP_STATE _lampState);
	void setLampState(bool _lampstate);
	void setLampON();
	void setLampOFF();
	ONE_BIT_LAMP_STATE getLampState();
};