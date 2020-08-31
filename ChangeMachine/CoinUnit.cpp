#include "CoinUnit.h"

CoinUnit::CoinUnit()
{
}

void CoinUnit::AddHopper(std::unique_ptr<Hopper> hopper)
{
	this->hoppers.insert(std::pair<int, std::unique_ptr<Hopper>>(hopper->GetValue(), std::move(hopper)));
}

const Hopper &CoinUnit::GetHopper(int value)
{
	return *this->hoppers.at(value);
}

void CoinUnit::SetHoppersCount(std::map<int, int> coinExchange)
{
	for (const auto& it : coinExchange)
	{
		this->hoppers.at(it.first)->SetCount(it.second);
	}
}

void CoinUnit::IncrementHoppersCount(std::map<int, int> coinExchange)
{
	for (const auto& it : coinExchange)
	{
		this->hoppers.at(it.first)->AddCount(it.second);
	}
}

void CoinUnit::DecrementHoppersCount(std::map<int, int> coinExchange)
{
	if (!checkEnoughCoins(coinExchange))
	{
		throw std::exception();
	}

	for (const auto& it : coinExchange)
	{
		this->hoppers.at(it.first)->DecCount(it.second);
	}
}

bool CoinUnit::checkEnoughCoins(std::map<int, int> coinExchange)
{
	for (const auto& it : coinExchange)
	{
		if (this->hoppers.at(it.first)->GetCount() < it.second)
		{
			return false;
		}
	}

	return true;
}

std::map<int, int> CoinUnit::CalcChange(int cash)
{
	std::map<int, int> change;

	int changeMissing = cash;

	for (auto it = this->hoppers.rbegin(); it != this->hoppers.rend(); ++it)
	{
		int changeCount = 0;

		hoppers[it->first]->GetChange(changeMissing, changeCount);

		change[hoppers[it->first]->GetValue()] = changeCount;
	}

	if (changeMissing != 0)
	{
		throw std::exception();
	}

	return change;
}

std::map<int, int> CoinUnit::GetHoppersCount(void)
{
	std::map<int, int> countCoinList;

	for (const auto& it : this->hoppers)
	{
		countCoinList[hoppers[it.first]->GetValue()] = hoppers[it.first]->GetCount();
	}

	return countCoinList;
}

int CoinUnit::GetSize(void)
{
	return this->hoppers.size();
}

std::string CoinUnit::Serialize()
{
	std::stringstream coinUnitString;

	for (const auto& it : this->hoppers)
	{
		coinUnitString << hoppers[it.first]->Serialize() << "\n";
	}

	return coinUnitString.str();
}