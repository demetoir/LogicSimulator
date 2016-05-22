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
	COMPONENT_INFO wire1,wire2;

	andgate.componentType = COMPONENT_TYPE_AND_GATE;
	andgate.direction = DIRECTION_EAST;
	andgate.x = 10;
	andgate.y = 15;
	
	wire1.componentType = COMPONENT_TYPE_WIRE;
	wire1.direction = DIRECTION_NONE;

	wire2.componentType = COMPONENT_TYPE_WIRE;
	wire1.direction = DIRECTION_NONE;
	box.addComponent(andgate);
	box.addComponent(wire1);
	
	box.addComponent(wire2);

	COMPONENT_CONENTION_INFO connect_andgate, connect_wire1, connect_wire2;
	connect_andgate.componentID = andgate.componentID;
	connect_andgate.terminalType = TERMINAL_TYPE_INPUT;
	connect_andgate.terminalNumber = 0;

	connect_wire1.componentID = wire1.componentID;
	connect_wire1.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_wire1.terminalNumber = 0;

	box.connectComponentAndWire(connect_andgate, connect_wire1);

	connect_wire1.componentID = wire1.componentID;
	connect_wire1.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_wire1.terminalNumber = 1;

	connect_wire2.componentID = wire2.componentID;
	connect_wire2.terminalType = TERMINAL_TYPE_INPUT;
	connect_wire2.terminalNumber = 0;
	

	box.connectComponentAndWire(connect_andgate, connect_wire1);
	
	box.connectWireAndWire(connect_wire1, connect_wire2);
	box.deleteComponent(wire1.componentID);
	box.disconnectComponentAndWire(connect_wire1, connect_wire2);


	//box.disconnectComponentAndWire(connect_andgate, connect_wire1);

}