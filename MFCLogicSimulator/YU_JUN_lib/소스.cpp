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
	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE),wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	printf("library box test\n");
	printf("\n");

	box.printstatus();

	// 라이브러리 박스에 집어넣음
	printf("add component andgate\n");
	box.addComponent(andgate);
	box.printstatus();

	printf("add component wire1\n");
	box.addComponent(wire1);	

	box.printstatus();

	printf("add component wire2\n");
	box.addComponent(wire2);
	box.printstatus();
	printf("add component wire3\n");
	box.addComponent(wire3);
	box.printstatus();
	printf("add component input pin1\n");
	box.addComponent(inputpin1);
	box.printstatus();
	printf("add component input pin2\n");
	box.addComponent(inputpin2);
	box.printstatus();
	printf("add component output pin1\n");
	box.addComponent(outputpin1);
	box.printstatus();
	
	/* pin 1 -> wire1 
		pin2 ->wire2

		wire1->andgate
		wire2->andgate

		andgate->ouputpin1
	
	*/


	COMPONENT_CONENTION_INFO connect_gate, connect_wire, connect_pin;


	// pin 1 -> wire1 
	connect_wire.componentID = wire1.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_INPUT;
	connect_wire.terminalNumber = 0;
	connect_pin.componentID = inputpin1.componentID;
	connect_pin.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_pin.terminalNumber = 0;


	printf("connect input pin1 to wire1\n");
	box.connectComponentAndWire(connect_pin, connect_wire);


	//pin2 ->wire2
	connect_wire.componentID = wire2.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_INPUT;
	connect_wire.terminalNumber = 0;
	connect_pin.componentID = inputpin2.componentID;
	connect_pin.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_pin.terminalNumber = 0;

	printf("connect input pin2 to wire2\n");
	box.connectComponentAndWire(connect_pin, connect_wire);

	//wire1->andgate
	connect_wire.componentID = wire1.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_wire.terminalNumber = 0;
	connect_gate.componentID = andgate.componentID;
	connect_gate.terminalType = TERMINAL_TYPE_INPUT;
	connect_gate.terminalNumber = 0;

	printf("connect input wire1 to andgate1\n");
	box.connectComponentAndWire(connect_gate, connect_wire);

	//wire2->andgate
	connect_wire.componentID = wire2.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_wire.terminalNumber = 0;
	connect_gate.componentID = andgate.componentID;
	connect_gate.terminalType = TERMINAL_TYPE_INPUT;
	connect_gate.terminalNumber = 1;
	printf("connect wire2 to andgate\n");
	box.connectComponentAndWire(connect_gate, connect_wire);

	//andgate-> wire3
	connect_wire.componentID = wire3.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_INPUT;
	connect_wire.terminalNumber = 0;
	connect_gate.componentID = andgate.componentID;
	connect_gate.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_gate.terminalNumber = 0;
	printf("connect andgate to wire3\n");
	box.connectComponentAndWire(connect_gate, connect_wire);

	//wire3->ouputpin1
	connect_wire.componentID = wire3.componentID;
	connect_wire.terminalType = TERMINAL_TYPE_OUTPUT;
	connect_wire.terminalNumber = 0;
	connect_pin.componentID = outputpin1.componentID;
	connect_pin.terminalType = TERMINAL_TYPE_INPUT;
	connect_pin.terminalNumber = 0;
	printf("connect wire3 to output pin1\n");
	box.connectComponentAndWire(connect_pin, connect_wire);

	
	box.printstatus();

}
