#include <stdio.h>
#include <iostream>
#include "WireComponet.h"
#include "OneBitSwitch.h"
#include "ANDGateComponet.h"

#include "LibraryBoxComponent.h"


using namespace std;


int main() {
	//LogicGateTest();
	//wireTest();
	CLibraryBox box;
	COMPONENT_INFO andgate;
	COMPONENT_INFO wire;

	andgate.componentType = COMPONENT_TYPE_AND_GATE;
	andgate.direction = DIRECTION_EAST;
	andgate.x = 10;
	andgate.y = 15;
	
	wire.componentType = COMPONENT_TYPE_WIRE;
	wire.direction = DIRECTION_EAST;
	
	COMPONENT_CONENTION_INFO connect_andgate, connect_wire;
	connect_andgate.componentID = andgate.componentID;
	connect_andgate.terminalType = TERMINAL_TYPE_INPUT;

	box.addComponent(andgate);
	box.addComponent(wire);
	box.connectComponentAndWire();
}