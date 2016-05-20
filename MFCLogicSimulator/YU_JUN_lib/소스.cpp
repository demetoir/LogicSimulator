#include <stdio.h>
#include <iostream>
#include "logicGateComponent.h"
#include "WireComponet.h"

using namespace std;

void GateTest(CLogicGateComponent andGate) {
	printf("logic gate type : %d\n", andGate.getLogicGatetype());
	printf("direction: %d\n", andGate.getDirection());
	std::cout <<"label :"<<andGate.getLabel() << std::endl;
	andGate.setLabel(std::string("this is label"));
	std::cout <<"label:"<<andGate.getLabel() << std::endl;

	printf("x,y : %d,%d\n", andGate.getX(),andGate.getY());
	andGate.setX(12);
	andGate.setY(15);
	printf("x,y : %d,%d\n", andGate.getX(), andGate.getY());

	 
	andGate.setInputValue1(false);
	andGate.setInputValue2(false);
	andGate.updateOutputValue();
	printf("inputvalue1:%d inputvalue2 :%d => outputvalue: %d\n",
		andGate.getInputvalue1(),andGate.getInputValue2(), andGate.getOutputValue());


	andGate.setInputValue1(true);
	andGate.setInputValue2(false);
	andGate.updateOutputValue();
	printf("inputvalue1:%d inputvalue2 :%d => outputvalue: %d\n",
		andGate.getInputvalue1(), andGate.getInputValue2(), andGate.getOutputValue());


	andGate.setInputValue1(false);
	andGate.setInputValue2(true);
	andGate.updateOutputValue();
	printf("inputvalue1:%d inputvalue2 :%d => outputvalue: %d\n",
		andGate.getInputvalue1(), andGate.getInputValue2(), andGate.getOutputValue());


	andGate.setInputValue1(true);
	andGate.setInputValue2(true);
	andGate.updateOutputValue();
	printf("inputvalue1:%d inputvalue2 :%d => outputvalue: %d\n",
		andGate.getInputvalue1(), andGate.getInputValue2(), andGate.getOutputValue());


}

void LogicGateTest() {
	CLogicGateComponent andGate(LOGIC_GATE_AND);
	CLogicGateComponent orGate(LOGIC_GATE_OR);
	CLogicGateComponent xorGate(LOGIC_GATE_XOR);
	CLogicGateComponent norGate(LOGIC_GATE_NOR);
	CLogicGateComponent notGate(LOGIC_GATE_NOT);
	std::cout << "##################" << std::endl;
	std::cout << "logicGateTest" << std::endl;
	std::cout << "##################" << std::endl;


	std::cout <<"andgate" <<std::endl;
	GateTest(andGate);
	std::cout << std::endl;

	std::cout <<"orgate"<<std::endl;
	GateTest(orGate);
	std::cout << std::endl;

	std::cout << "xorgate" << std::endl;
	GateTest(xorGate);
	std::cout << std::endl;

	std::cout << "norgate" << std::endl;
	GateTest(norGate);
	std::cout << std::endl;

	std::cout << "notgate" << std::endl;
	GateTest(notGate);
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void wireTest() {
	std::cout << "##################" << std::endl;
	std::cout << "wireTest" << std::endl;
	std::cout << "##################" << std::endl;
	std::cout << std::endl;
	
	CWireComponent wireWithoutJunction;

	cout<< wireWithoutJunction.





}

int main() {
	LogicGateTest();

	wireTest();
}