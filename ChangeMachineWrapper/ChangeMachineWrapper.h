#pragma once
using namespace System;
namespace CLI {
	public ref class ChangeMachineWrapper
	{
	public:

		void EndExchange(int kind, array<int>^ coinValues, array<int>^ coinCounts, int coinsLength);
		void CashOut(array<int>^ coinValues, array<int>^ coinCounts, int coinsLength);
		void PayChange(int cash, array<int>^ coinValues, array<int>^ coinCounts, int% coinsLength);
		void GetCountCoinList(array<int>^ coinValues, array<int>^ coinCounts, int% coinsLength);
		int stop;
	};
}
