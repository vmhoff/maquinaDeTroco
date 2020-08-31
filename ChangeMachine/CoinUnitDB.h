#pragma once
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include "CoinUnit.h"
#include "Hopper.h"

class CoinUnitDB
{
public:
	CoinUnitDB(std::string filePath);

	void saveCoinUnit(std::unique_ptr<CoinUnit> &coinUnit);
	std::unique_ptr<CoinUnit> loadCoinUnit(void);
	void loadCoinUnitDefault(std::unique_ptr<CoinUnit>& coinUnit);

private:
	std::string filePath;

	int getDataFromLine(std::stringstream &line);
};

