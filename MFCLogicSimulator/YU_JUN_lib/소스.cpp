#include <stdio.h>
#include <iostream>
#include "WireComponet.h"
#include "OneBitSwitch.h"
#include "ANDGateComponet.h"

#include "LibraryBoxComponent.h"


using namespace std;



void printBoxInOutvalue(CLibraryBox& box) {

	printf("input value : \n");
	for (int i = 0; i < box.numberOfInput(); i++) {
		printf("%d : %d \n", i, box.getSingleInputPinValue(i));
	}
	printf("output value : \n");
	for (int i = 0; i < box.numberOfOutput(); i++) {
		printf("%d : %d \n", i, box.getSingleOutputPinValue(i));
	}
	printf("\n");

}

void printStateTable(CLibraryBox& box) {

	box.setInputValue(0, false);
	box.setInputValue(1, false);
	box.updateCircuit();
	printBoxInOutvalue(box);

	box.setInputValue(0, true);
	box.setInputValue(1, false);
	box.updateCircuit();
	printBoxInOutvalue(box);

	box.setInputValue(0, false);
	box.setInputValue(1, true);
	box.updateCircuit();
	printBoxInOutvalue(box);

	box.setInputValue(0, true);
	box.setInputValue(1, true);
	box.updateCircuit();
	printBoxInOutvalue(box);
}


void NANDGATE_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);


	box.addComponent(outputpin1);
	box.addComponent(wire2);
	box.addComponent(andgate);
	box.addComponent(wire3);
	box.addComponent(wire1);

	box.addComponent(notgate);


	box.addComponent(inputpin1);
	box.addComponent(inputpin2);

	box.addComponent(wire4);



	COMPONENT_CONENTION_INFO B, A;

	//A->B
	//input pin 1-> wire1
	A.componentID = inputpin1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 3 -> notgate 
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = notgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//notgate -> wire 4
	A.componentID = notgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire4.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 4 -> output pin 
	A.componentID = wire4.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);



	printStateTable(box);


}



void NORGATE_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_OR_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(andgate);
	box.addComponent(wire3);
	box.addComponent(notgate);
	box.addComponent(wire4);
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
	box.connnectComponent(&A, &B);

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 3 -> notgate 
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = notgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//notgate -> wire 4
	A.componentID = notgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire4.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 4 -> output pin 
	A.componentID = wire4.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);


	printStateTable(box);


}

void ANDGATE_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(andgate);
	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
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
	box.connnectComponent(&A, &B);

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 3 -> output pin1
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	printStateTable(box);

}


void ORGATE_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_OR_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(andgate);
	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
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
	box.connnectComponent(&A, &B);

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 3 -> output pin1
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	printStateTable(box);

}

void XORGATE_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_XOR_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(andgate);
	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
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
	box.connnectComponent(&A, &B);

	//input pin 2 -> wire2 
	A.componentID = inputpin2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire1 -> andgate in 1
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2 -> andgate in 2
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 3
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire 3 -> output pin1
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	printStateTable(box);

}


void Oscillation_test() {

	CLibraryBox box;

	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(andgate);
	box.addComponent(inputpin1);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
	box.addComponent(outputpin1);
	box.addComponent(notgate);

	COMPONENT_CONENTION_INFO B, A;

	//A->B
	//input pin 1-> wire1
	A.componentID = inputpin1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);



	//wire1 -> andgate in 0
	A.componentID = wire1.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire3 -> andgate in 1
	A.componentID = wire3.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = andgate.componentID;
	B.terminalNumber = 1;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//andgate out 1 -> wire 2
	A.componentID = andgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire2.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2  . 0 -> output pin1
	A.componentID = wire2.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = outputpin1.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//wire2  . 1 -> not gate
	A.componentID = wire2.componentID;
	A.terminalNumber = 1;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = notgate.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	//not gate -> wire3 
	A.componentID = notgate.componentID;
	A.terminalNumber = 0;
	A.terminalType = TERMINAL_TYPE_OUTPUT;
	B.componentID = wire3.componentID;
	B.terminalNumber = 0;
	B.terminalType = TERMINAL_TYPE_INPUT;
	box.connnectComponent(&A, &B);

	box.updateCircuit();

	box.setInputValue(0,false);
	box.updateCircuit();
	printf("oscillation : %d\n", box.checkOscillation());
	printBoxInOutvalue(box);

	box.setInputValue(0, true);
	box.updateCircuit();
	printf("oscillation : %d\n", box.checkOscillation());
	printBoxInOutvalue(box);
}

int main() {




	printf("#### nand test\n");
	NANDGATE_test();

	printf("#### nor test \n");
	NORGATE_test();

	printf("#### and  test \n");
	ANDGATE_test();

	printf("#### or test\n");
	ORGATE_test();

	printf("#### xor test\n");
	XORGATE_test();

	printf("#### oscillation test\n");
	Oscillation_test();


}
