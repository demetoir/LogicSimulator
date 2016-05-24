#include "InputPinComponent.h"

CInputPinComponent::CInputPinComponent()
{
	inputTerminalInfo.resize(INPUT_PIN_INPUT_TEMINAL_NUMBER+1);
	outputTerminalInfo.resize(INPUT_PIN_OUTPUT_TEMINAL_NUMBER+1);
	value.resize(INPUT_PIN_OUTPUT_VALUE_SIZE+1);

	value[1] = INPUT_PIN_DEFAULT_INPUT_VALUE;	
}

CInputPinComponent::CInputPinComponent(CInputPinComponent & object)
	:CComponentObject(object)
{
	inputTerminalInfo.resize(INPUT_PIN_INPUT_TEMINAL_NUMBER + 1);
	outputTerminalInfo.resize(INPUT_PIN_OUTPUT_TEMINAL_NUMBER + 1);
	value.resize(INPUT_PIN_OUTPUT_VALUE_SIZE + 1);

	value[1] = object.getValue(1);
}

CInputPinComponent::~CInputPinComponent()
{
}

void CInputPinComponent::setValue(int index, bool newvalue)
{
	value[index] = newvalue;
}

bool CInputPinComponent::getValue(int index)
{
	return value[index];
}

