#include <stdio.h>
#include <iostream>
#include "WireComponet.h"
#include "OneBitSwitch.h"
#include "ANDGateComponet.h"

#include "LibraryBoxComponent.h"


#define ENDL printf("\n");
#define print(str) printf(str);
#define printE(str) printf(str);ENDL;
using namespace std;



void printBoxInOutvalue(CLibraryBox& box) {
	for (int i = 0; i < box.numberOfClock(); i++) {
		printf("       %d ", box.getClockValue(i));
	}
	for (int i = 0; i < box.numberOfInput(); i++) {
		printf("    %d ", box.getInputValue(i));
	}
	printf("   ->   ");
	for (int i = 0; i < box.numberOfOutput(); i++) {
		printf("    %d ", box.getOutputValue(i));
	}
	printf("\n");
}

void clockDownUpDown(CLibraryBox& box) {
	printE("clock down");
	box.setClockValue(0, false);
	box.update();
	printBoxInOutvalue(box);

	printE("clock up");
	box.setClockValue(0, true);
	box.update();
	printBoxInOutvalue(box);

	printE("clock down");
	box.setClockValue(0, false);
	box.update();
	printBoxInOutvalue(box);
}

void printStateTable(CLibraryBox& box) {

	printf("number of input value  : %d\n", box.numberOfInput());
	printf("number of output value : %d\n", box.numberOfOutput());
	printf("number of clock  : %d\n", box.numberOfClock());
	printE("-------------------------------------------------------");
	for (int i = 0; i < box.numberOfClock(); i++) {
		printf("clock %2.d ", i + 1);
	}
	for (int i = 0; i < box.numberOfInput(); i++) {
		printf("in %2.d ", i+1);
	}
	printf("       ");
	for (int i = 0; i < box.numberOfOutput(); i++) {
		printf("out %2.d ", i+1);
	}
	printf("\n");
	printE("-------------------------------------------------------");




	//모든 인풋을 다해본다
	int numberOfinput = box.numberOfInput();
	int max = 1 << numberOfinput;


	//클럭이 없을떄
	if (box.numberOfClock()  == 0) {
		for (int curState = 0; curState < max; curState++) {
			printE("current state");
			//이전 상태를 셋팅한다
			for (int b = numberOfinput - 1; b >= 0; b--) {
				box.setInputValue(b, (curState & (1 << b)));
			}
			box.update();
			printBoxInOutvalue(box);
			printE("-------------------------------------------------------");			
		}
		return;
	}
	//이전의 상태를 고려한다
	for (int curState = 0; curState < max; curState++) {
		for (int nextState = 0; nextState<max; nextState++) {
			printE("current state");
			//이전 상태를 셋팅한다
			for (int b = numberOfinput - 1; b >= 0; b--) {
				box.setInputValue(b, (curState & (1 << b)));
			}	
			clockDownUpDown(box);
			ENDL;
			printE("next state");
			//이후 상태를 셋팅한다
			for (int b = numberOfinput - 1; b >= 0; b--) {
				box.setInputValue(b, (nextState & (1 << b)));
			}
			clockDownUpDown(box);
			printE("-------------------------------------------------------");
		}		
	}
	printf("\n");
}

void make_NANDGATE(CLibraryBox& box) {

	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	//1
	box.addComponent(outputpin1);
	//2
	box.addComponent(wire2);
	
	//3
	box.addComponent(andgate);
	//4
	box.addComponent(wire3);
	//5
	box.addComponent(wire1);
	//6
	box.addComponent(notgate);
	//7
	box.addComponent(inputpin1);
	//8
	box.addComponent(inputpin2);
	//9
	box.addComponent(wire4);



	COMPONENT_CONENTION_INFO B, A;
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

	}
}

void make_NORGATE(CLibraryBox& box) {


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
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}

}

void Make_ANDGATE(CLibraryBox& box) {

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
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> output pin1
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}
}

void make_ORGATE(CLibraryBox& box) {

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
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> output pin1
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}

}

void make_XORGATE(CLibraryBox& box) {
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
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> output pin1
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

	}
}


void Oscillation_test(CLibraryBox& box) {

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
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);



		//wire1 -> andgate in 0
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire3 -> andgate in 1
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 2
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2  . 0 -> output pin1
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2  . 1 -> not gate
		A.componentID = wire2.componentID;
		A.terminalNumber = 1;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//not gate -> wire3 
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}

	box.update();

	box.setInputValue(0, false);
	box.update();
	printf("oscillation : %d\n", box.checkOscillation());
	printBoxInOutvalue(box);

	box.setInputValue(0, true);
	box.update();
	printf("oscillation : %d\n", box.checkOscillation());
	printBoxInOutvalue(box);
}

void libbox_Save_Load_test(CLibraryBox& box, CLibraryBox& box2){



	printf("save box data\n");
	LIBRARY_BOX_DATA boxData;
	box.saveLibraryBoxData(boxData);

	printf("load box data\n");
	box2.loadLibraryBoxData(boxData);

	printf("box1 info\n");
	printStateTable(box);
	printf("box2 info\n");
	printStateTable(box2);

}

void make_D_flipflop(CLibraryBox& box) {



	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);

	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire5(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire6(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire7(COMPONENT_TYPE_WIRE);

	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputClock(COMPONENT_TYPE_CLOCK);

	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);
	COMPONENT_INFO outputpin2(COMPONENT_TYPE_OUTPUT_PIN);

	COMPONENT_INFO nandgate1(COMPONENT_TYPE_LIBRARY_BOX);
	COMPONENT_INFO nandgate2(COMPONENT_TYPE_LIBRARY_BOX);
	COMPONENT_INFO nandgate3(COMPONENT_TYPE_LIBRARY_BOX);
	COMPONENT_INFO nandgate4(COMPONENT_TYPE_LIBRARY_BOX);

	CLibraryBox nandgate;
	make_NANDGATE(nandgate);
	LIBRARY_BOX_DATA data;
	nandgate.saveLibraryBoxData(data);

	box.addComponent(notgate);

	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(wire3);
	box.addComponent(wire4);
	box.addComponent(wire5);
	box.addComponent(wire6);
	box.addComponent(wire7);

	box.addComponent(inputpin1);
	box.addComponent(inputClock);
	box.addComponent(outputpin1);
	box.addComponent(outputpin2);
	box.addComponent(nandgate1,data);
	box.addComponent(nandgate2,data);
	box.addComponent(nandgate3, data);
	box.addComponent(nandgate4, data);
	
	
	COMPONENT_CONENTION_INFO B, A;



	{
		//A->B
		//input pin 1 -> wire 1
		A.componentID = inputpin1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//input pin 2 -> wire 2
		A.componentID = inputClock.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire2.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);


		/////////////////////////////////////
		//A->B
		//wire1 -> nand1 .0
		A.componentID = wire1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);


		//A->B
		//wire 1 . 1 -> not 1.0
		A.componentID = wire1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 1;
		B.componentID = notgate.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//wire 2 . 0 -> nand1 .1
		A.componentID = wire2.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 1;
		box.connnectComponent(A, B);

		//A->B
		//wire2.1 -> nand 2.0
		A.componentID = wire2.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 1;
		B.componentID = nandgate2.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//not 1.0 -> wire3.0
		A.componentID = notgate.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire3.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//wire3.0 -> nand 2.1
		A.componentID = wire3.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate2.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 1;
		box.connnectComponent(A, B);

		//A->B
		//nand 1. 0  -> wire 4.0
		A.componentID = nandgate1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire4.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//nand 2. 0 -> wire5.0
		A.componentID = nandgate2.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire5.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);



		//A->B
		//wire 4.0 -> nand 3.0
		A.componentID = wire4.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate3.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//wire5.0 -> nand 4.1
		A.componentID = wire5.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate4.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 1;
		box.connnectComponent(A, B);


		//A->B
		//nand3.0 -> wire6.0
		A.componentID = nandgate3.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire6.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);


		//A->B
		//nand4.0 -> wire 7.0
		A.componentID = nandgate4.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire7.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);


		//A->B
		//wire 6 . 0 -> nand4.0
		A.componentID = wire6.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate4.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//wire 6. 1 -> output1.0
		A.componentID = wire6.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 1;
		B.componentID = outputpin1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

		//A->B
		//wire7.0 -> nand3.1
		A.componentID = wire7.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = nandgate3.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 1;
		box.connnectComponent(A, B);

		//A->B
		//wire7.1 -> output2.0
		A.componentID = wire7.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 1;
		B.componentID = outputpin2.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		box.connnectComponent(A, B);

	}

}



void libboxIn_libbox_test(CLibraryBox& outbox, CLibraryBox& inbox) {


	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);

	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);

	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);

	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	COMPONENT_INFO libbox(COMPONENT_TYPE_LIBRARY_BOX);

	LIBRARY_BOX_DATA data;
	inbox.saveLibraryBoxData(data);

	outbox.addComponent(inputpin1);
	outbox.addComponent(inputpin2);
	outbox.addComponent(wire1);
	outbox.addComponent(wire2);
	outbox.addComponent(libbox, data);
	outbox.addComponent(wire3);
	outbox.addComponent(notgate);
	outbox.addComponent(wire4);
	outbox.addComponent(outputpin1);


	{
		COMPONENT_CONENTION_INFO A, B;
		//A->B
		//input pin 1 -> wire 1
		A.componentID = inputpin1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);

		//A->B
		//input pin 2 -> wire 2
		A.componentID = inputpin2.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire2.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);


		//A->B
		//wire1 -> nand1 .0 
		A.componentID = wire1.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = libbox.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);

		//A->B
		// wire 2 - > nang gate 1 .1
		A.componentID = wire2.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = libbox.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 1;
		outbox.connnectComponent(A, B);

		//A->B
		//nandgate -> wire 3   
		A.componentID = libbox.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire3.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);

		//A->B
		//wire 3 -> notgate
		A.componentID = wire3.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = notgate.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);

		//A->B
		//not gate -> wire 4 
		A.componentID = notgate.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = wire4.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);


		//A->B
		//wire4 -> output pin
		A.componentID = wire4.componentID;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		A.terminalNumber = 0;
		B.componentID = outputpin1.componentID;
		B.terminalType = TERMINAL_TYPE_INPUT;
		B.terminalNumber = 0;
		outbox.connnectComponent(A, B);

	}

}

int main() {
	printE("this is test");
	//머지 하고 작업 브랜치 만듦


	CLibraryBox box1, box2;
	CLibraryBox andgate, orgate, xorgate, norgate, nandgate;


	printf("and gate_test\n");
	Make_ANDGATE(andgate);
	printStateTable(andgate);

	printf("orgate test\n");
	make_ORGATE(orgate);
	printStateTable(orgate);

	printf("xorgate test\n");
	make_XORGATE(xorgate);
	printStateTable(xorgate);

	printf("norgate test"); ENDL;
	make_NORGATE(norgate);
	printStateTable(norgate);

	printf("nand gate test"); ENDL;
	make_NANDGATE(nandgate);
	printStateTable(nandgate);

	libbox_Save_Load_test(nandgate,box2);

	CLibraryBox dfilpflop;

	printE("D flip flop test");
	make_D_flipflop(dfilpflop);
	printStateTable(dfilpflop);


	printE("lib box  in lib box nand not ");
	CLibraryBox outbox;
	libboxIn_libbox_test(outbox, nandgate);
	printStateTable(outbox);

	printE("lib box  in lib box nor not ");
	CLibraryBox outbox2;
	libboxIn_libbox_test(outbox2, norgate);
	printStateTable(outbox2);





}
