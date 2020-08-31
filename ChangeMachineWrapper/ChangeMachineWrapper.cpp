#include "ChangeMachineWrapper.h"
#include "../ChangeMachine/ChangeMachine.h"

void CLI::ChangeMachineWrapper::EndExchange(int kind, array<int>^ coinValues, array<int>^ coinCounts, int coinsLength)
{
	ChangeMachine changeMachine;
	changeMachine.StartExchange();

    pin_ptr<int> coinValuesPtr = &coinValues[0];
    pin_ptr<int> coinCountsPtr = &coinCounts[0];
    changeMachine.EndExchange(kind, coinValuesPtr, coinCountsPtr, coinsLength);
}

void CLI::ChangeMachineWrapper::CashOut(array<int>^ coinValues, array<int>^ coinCounts, int coinsLength)
{
    ChangeMachine changeMachine;
    pin_ptr<int> coinValuesPtr = &coinValues[0];
    pin_ptr<int> coinCountsPtr = &coinCounts[0];
    changeMachine.CashOut(coinValuesPtr, coinCountsPtr, coinsLength);
}

void CLI::ChangeMachineWrapper::PayChange(int cash, array<int>^ coinValues, array<int>^ coinCounts, int% coinsLength)
{
    ChangeMachine changeMachine;
    int coinsLengthPtr = coinsLength;
    pin_ptr<int> coinValuesPtr = &coinValues[0];
    pin_ptr<int> coinCountsPtr = &coinCounts[0];
    changeMachine.PayChange(cash, coinValuesPtr, coinCountsPtr, &coinsLengthPtr);
    stop = 0;
    coinsLength = coinsLengthPtr;
    stop = 1;
}

void CLI::ChangeMachineWrapper::GetCountCoinList(array<int>^ coinValues, array<int>^ coinCounts, int% coinsLength)
{
    ChangeMachine changeMachine;
    int coinsLengthPtr = coinsLength;
    pin_ptr<int> coinValuesPtr = &coinValues[0];
    pin_ptr<int> coinCountsPtr = &coinCounts[0];
    changeMachine.GetCountCoinList(coinValuesPtr, coinCountsPtr, &coinsLengthPtr);
    coinsLength = coinsLengthPtr;
}