#include "Hopper.h"

Hopper::Hopper() :
	currency("None"), value(0), count(0), countMin(0), countMax(0)
{
	this->status = Status::ERR;
}

Hopper::Hopper(std::string currency, int countMin, int countMax, int value, int count) :
	currency(currency), value(value), count(count), countMin(countMin), countMax(countMax)
{
	if (this->countMin < 0 ||
		this->countMax < 0 ||
		this->value <= 0 ||
		this->count < 0 ||
		this->countMin > this->countMax)
	{
		throw std::exception();
	}
	updateStatus();
}

std::string Hopper::GetCurrency()
{
	return this->currency;
}

void Hopper::SetCurrency(std::string currency)
{
	this->currency = currency;
}

int Hopper::GetValue()
{
	return this->value;
}

void Hopper::SetValue(int value)
{
	if (value <= 0)
	{
		throw std::exception();
	}
	this->value = value;
}

Hopper::Status Hopper::GetStatus()
{
	return this->status;
}

int Hopper::GetCount()
{
	return this->count;
}

void Hopper::SetCount(int count)
{
	if (count < 0)
	{
		throw std::exception();
	}
	this->count = count;
	updateStatus();
}

void Hopper::AddCount(int count)
{
	if (count < 0)
	{
		throw std::exception();
	}
	this->count += count;
	updateStatus();
}

void Hopper::DecCount(int count)
{
	if (count < 0 ||
		(this->count - count < 0))
	{
		throw std::exception();
	}
	this->count -= count;
	updateStatus();
}

void Hopper::GetChange(int& changeMissing, int& changeCount)
{
	changeCount = changeMissing / this->value;
	if (changeCount > this->count)
	{
		changeCount = this->count;
	}
	changeMissing -= (changeCount * this->value);
}

void Hopper::updateStatus(void)
{
	if (this->count >= this->countMax)
	{
		this->status = Status::FULL;
	}
	else if(this->count <= this->countMin)
	{
		this->status = Status::EMPTY;
	}
	else
	{
		this->status = Status::OK;
	}
}

std::string Hopper::Serialize()
{
	std::stringstream hopperString;

	hopperString.flush();
	hopperString << currency << ",";
	hopperString << value << ",";
	hopperString << count << ",";
	hopperString << countMin << ",";
	hopperString << countMax;

	return hopperString.str();
}