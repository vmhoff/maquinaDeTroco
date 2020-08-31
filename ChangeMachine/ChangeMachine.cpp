// ChangeMachine.cpp : Define as funções exportadas para a DLL.
//

#include "framework.h"
#include "ChangeMachine.h"


// Isto é um exemplo de uma variável exportada
CHANGEMACHINE_API int nChangeMachine=0;

// Isto é um exemplo de uma função exportada.
CHANGEMACHINE_API int fnChangeMachine(void)
{
    return 0;
}

// Este é o construtor de uma classe que foi exportada.
ChangeMachine::ChangeMachine()
{
    loadCoinUnit();
    isExchangeActive = false;
}

void ChangeMachine::StartExchange()
{
    isExchangeActive = true;
}

void ChangeMachine::EndExchange(int kind, int* coinValues, int* coinCounts, int coinsLength)
{
    if (!isExchangeActive)
    {
        throw std::exception();
    }

    std::map<int, int> coinExchange;
    for (int i = 0; i < coinsLength; i++)
    {
        coinExchange[coinValues[i]] = coinCounts[i];
    }

    switch ((ExchandeKind)kind)
    {
    case ChangeMachine::ExchandeKind::INITIAL:
        this->coinUnit->SetHoppersCount(coinExchange);
        break;
    case ChangeMachine::ExchandeKind::INCREMENTAL:
        this->coinUnit->IncrementHoppersCount(coinExchange);
        break;
    default:
        throw std::exception();
        break;
    }
    db.saveCoinUnit(this->coinUnit);

    isExchangeActive = false;
}

void ChangeMachine::CashOut(int* coinValues, int* coinCounts, int coinsLength)
{
    if (isExchangeActive)
    {
        throw std::exception();
    }

    std::map<int, int> dispense;
    for (int i = 0; i < coinsLength; i++)
    {
        dispense[coinValues[i]] = coinCounts[i];
    }

    this->coinUnit->DecrementHoppersCount(dispense);
    db.saveCoinUnit(this->coinUnit);
}

void ChangeMachine::PayChange(int cash, int* coinValues, int* coinCounts, int* coinsLength)
{
    if (isExchangeActive)
    {
        throw std::exception();
    }

    auto dispense = this->coinUnit->CalcChange(cash);
    this->coinUnit->DecrementHoppersCount(dispense); 
    db.saveCoinUnit(this->coinUnit);

    int i = 0;
    for (const auto& it : dispense)
    {
        coinValues[i] = it.first;
        coinCounts[i] = it.second;
        i++;
    }
    *coinsLength = dispense.size();
}

void ChangeMachine::GetCountCoinList(int* coinValues, int* coinCounts, int* coinsLength)
{
    std::map<int, int> countCoinList = this->coinUnit->GetHoppersCount();
    int i = 0;
    for (const auto& it : countCoinList)
    {
        coinValues[i] = it.first;
        coinCounts[i] = it.second;
        i++;
    }
    *coinsLength = countCoinList.size();
}

void ChangeMachine::loadCoinUnit(void)
{
    this->coinUnit = db.loadCoinUnit();
}