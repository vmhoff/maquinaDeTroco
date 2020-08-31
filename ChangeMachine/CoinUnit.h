#pragma once
#include <map>
#include <memory>
#include <exception>
#include "Hopper.h"
#include <sstream>

class CoinUnit
{
public:
	CoinUnit(void);

	void AddHopper(std::unique_ptr<Hopper> hopper);
	const Hopper &GetHopper(int value);
	void SetHoppersCount(std::map<int, int> coinExchange);
	void IncrementHoppersCount(std::map<int, int> coinExchange);
	void DecrementHoppersCount(std::map<int, int> coinExchange);
	std::map<int, int> CalcChange(int cash);
	std::map<int, int> GetHoppersCount(void);
	int GetSize(void);
	std::string Serialize(void);

private:
	std::map<int, std::unique_ptr<Hopper>> hoppers;

	bool checkEnoughCoins(std::map<int, int> coinExchange);
};

