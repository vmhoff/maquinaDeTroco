#pragma once
#include <string>
#include <exception>
#include <sstream>

class Hopper
{
public:
	enum class Status { OK, EMPTY, FULL, ERR };

	Hopper(void);
	Hopper(std::string currency, int countMin, int countMax, int value, int count);

	std::string GetCurrency();
	void SetCurrency(std::string currency);

	int GetValue();
	void SetValue(int value);

	Status GetStatus();

	int GetCount();
	void SetCount(int count);
	void AddCount(int count);
	void DecCount(int count);
	void GetChange(int& changeMissing, int& changeCount);
	std::string Serialize();

private:
	std::string currency;
	int value;
	Status status;
	int count;
	int countMin;
	int countMax;

	void updateStatus(void);
};

