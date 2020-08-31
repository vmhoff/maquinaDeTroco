#include "CoinUnitDB.h"

CoinUnitDB::CoinUnitDB(std::string filePath) : 
	filePath(filePath)
{
	std::ofstream fs(filePath, std::ofstream::app);

	if (!fs.is_open())
	{
		throw std::exception();
	}

	fs.close();
}

void CoinUnitDB::saveCoinUnit(std::unique_ptr<CoinUnit> &coinUnit)
{
	std::ofstream ofs;
	ofs.open(filePath);
	if (!ofs.is_open())
	{
		throw std::exception();
	}

	ofs << coinUnit->Serialize();

	ofs.close();

}

std::unique_ptr<CoinUnit> CoinUnitDB::loadCoinUnit(void)
{
	std::ifstream ifs(filePath);
	ifs.open(filePath);
	if (!ifs.is_open())
	{
		throw std::exception();
	}

	std::string line;
	std::unique_ptr<CoinUnit> coinUnit = std::make_unique<CoinUnit>();
	ifs.clear();
	while (std::getline(ifs, line)) {
		std::stringstream hopperLine;
		hopperLine << line; 
		std::string currency;
		std::getline(hopperLine, currency, ',');
		int value = getDataFromLine(hopperLine);
		int count = getDataFromLine(hopperLine);
		int countMin = getDataFromLine(hopperLine);
		int countMax = getDataFromLine(hopperLine);

		std::unique_ptr<Hopper> hopper;
		hopper = std::make_unique<Hopper>(currency, countMin, countMax, value, count);
		coinUnit->AddHopper(std::move(hopper));
	}
	ifs.close();

	if (coinUnit->GetSize() == 0)
	{
		loadCoinUnitDefault(coinUnit);
		saveCoinUnit(coinUnit);
	}

	return std::move(coinUnit);
}

void CoinUnitDB::loadCoinUnitDefault(std::unique_ptr<CoinUnit>& coinUnit)
{
	std::unique_ptr<Hopper> hopper;

	hopper = std::make_unique<Hopper>("BRL", 0 , 100, 100, 0);
	coinUnit->AddHopper(std::move(hopper));

	hopper = std::make_unique<Hopper>("BRL", 0, 100, 50, 0);
	coinUnit->AddHopper(std::move(hopper));

	hopper = std::make_unique<Hopper>("BRL", 0, 100, 25, 0);
	coinUnit->AddHopper(std::move(hopper));

	hopper = std::make_unique<Hopper>("BRL", 0, 100, 10, 0);
	coinUnit->AddHopper(std::move(hopper));

	hopper = std::make_unique<Hopper>("BRL", 0, 100, 5, 0);
	coinUnit->AddHopper(std::move(hopper));
	
}

int CoinUnitDB::getDataFromLine(std::stringstream &line)
{
	std::string data;
	int value;
	std::getline(line, data, ',');
	std::stringstream sData(data);
	sData >> value;

	return value;
}
