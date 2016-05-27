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
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(andgate);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(outputpin1);


	COMPONENT_CONENTION_INFO B, A;

	//A->B
	//input pin 1-> wire1
	A.componentID = inputpin1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	printf("%d\n", box.connnectComponent(&A, &B));

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	printf("%d\n", box.connnectComponent(&A, &B));

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	printf("%d\n", box.connnectComponent(&A, &B));



	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	printf("%d\n", box.connnectComponent(&A, &B));

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	printf("%d\n", box.connnectComponent(&A, &B));


	//wire 3 -> outputpin 
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;

	printf("%d\n", box.connnectComponent(&A, &B));

	printf("input value : \n");
	for (int i = 0; i < box.numberOfInput(); i++) {
		printf("%d : %d \n", i, box.getSingleInputPinValue(i));
	}

	printf("\n");
	printf("output value : \n");
	for (int i = 0; i < box.numberOfOutput(); i++) {
		printf("%d : %d \n", i, box.getSingleOutputPinValue(i));
	}

 

}
