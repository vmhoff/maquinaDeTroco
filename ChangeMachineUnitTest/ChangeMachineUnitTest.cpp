
#include <map>
#include <memory>
#include <exception>
#include "pch.h"
#include "CppUnitTest.h"
#include "ChangeMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChangeMachineUnitTest
{
	TEST_CLASS(ChangeMachineUnitTest)
	{
	public:
		
		TEST_METHOD(exchange1)
		{
			ChangeMachine changeMachine;
			changeMachine.StartExchange();
		}

		TEST_METHOD(exchange2)
		{
			try
			{
				ChangeMachine changeMachine;
				std::map<int, int> coinExchange;
				int* coinValues = {};
				int* coinCounts = {};
				int coinsLength = 0;
				changeMachine.EndExchange(0, coinValues, coinCounts, coinsLength);

				Assert::Fail(L"No exception", LINE_INFO());
			}
			catch (std::exception)
			{

			}
		}

		TEST_METHOD(exchange3)
		{
			ChangeMachine changeMachine;
			changeMachine.StartExchange();
			int coinValues[5] = {5, 10, 25, 50, 100};
			int coinCounts[5] = {0, 0, 0, 0, 0};
			int coinsLength = 5;
			changeMachine.EndExchange(0, coinValues, coinCounts, coinsLength);

			int coinValuesResult[5];
			int coinCountsResult[5];
			int coinsLengthResult;
			changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
			Assert::AreEqual(coinsLength, coinsLengthResult);
			for (int i = 0; i < coinsLengthResult; i++)
			{
				Assert::AreEqual(coinValues[i], coinValuesResult[i]);
				Assert::AreEqual(coinCounts[i], coinCountsResult[i]);
			}
		}

		TEST_METHOD(exchange4)
		{
			ChangeMachine changeMachine;
			changeMachine.StartExchange();
			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);
			int coinValues[5] = { 5, 10, 25, 50, 100 };
			int coinCounts[5] = { 100, 100, 100, 100, 100 };
			int coinsLength = 5;
			changeMachine.EndExchange(1, coinValues, coinCounts, coinsLength);

			int coinValuesResult[5];
			int coinCountsResult[5];
			int coinsLengthResult;
			changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
			Assert::AreEqual(coinsLength, coinsLengthResult);
			for (int i = 0; i < coinsLengthResult; i++)
			{
				int count = coinCountsOrig[i] + coinCounts[i];
				Assert::AreEqual(coinValues[i], coinValuesResult[i]);
				Assert::AreEqual(coinCounts[i], count);
			}
		}

		TEST_METHOD(cashOut1)
		{
			ChangeMachine changeMachine;

			changeMachine.StartExchange();
			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);
			int coinValues[5] = { 5, 10, 25, 50, 100 };
			int coinCounts[5] = { 50, 50, 50, 50, 50 };
			int coinsLength = 5;
			changeMachine.EndExchange(1, coinValues, coinCounts, coinsLength);

			int coinValuesOut[5] = { 5, 10, 25, 50, 100 };
			int coinCountsOut[5] = { 50, 20, 10, 5, 1 };
			int coinsLengthOut = 5;
			changeMachine.CashOut(coinValues, coinCounts, coinsLength);

			int coinValuesResult[5];
			int coinCountsResult[5];
			int coinsLengthResult;
			changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
			Assert::AreEqual(coinsLengthOut, coinsLengthResult);
			for (int i = 0; i < coinsLengthResult; i++)
			{
				int count = coinCountsOrig[i] - coinCountsOut[i];
				Assert::AreEqual(coinValues[i], coinValuesResult[i]);
				Assert::AreEqual(coinCountsOut[i], count);
			}
		}

		TEST_METHOD(cashOut2)
		{
			ChangeMachine changeMachine;
			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);
			try
			{
				int coinValues[5] = { 5, 10, 25, 50, 100 };
				int coinCounts[5] = { 50, 20, 100, 5, 1 };
				int coinsLength = 5;
				changeMachine.CashOut(coinValues, coinCounts, coinsLength);

				int coinValuesResult[5];
				int coinCountsResult[5];
				int coinsLengthResult;
				changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
				Assert::AreEqual(5, coinsLengthResult);
				for (int i = 0; i < coinsLengthResult; i++)
				{
					Assert::AreEqual(coinValuesOrig[i], coinValuesResult[i]);
					Assert::AreEqual(coinCountsOrig[i], coinCountsResult[i]);
				}
			}
			catch (std::exception)
			{
				int coinValuesResult[5];
				int coinCountsResult[5];
				int coinsLengthResult;
				changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
				Assert::AreEqual(5, coinsLengthResult);
				for (int i = 0; i < coinsLengthResult; i++)
				{
					Assert::AreEqual(coinValuesOrig[i], coinValuesResult[i]);
					Assert::AreEqual(coinCountsOrig[i], coinCountsResult[i]);
				}
			}
		}

		TEST_METHOD(cashOut3)
		{
			ChangeMachine changeMachine;
			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);
			try
			{
				int coinValues[5] = { 5, 10, 25, 50, 100 };
				int coinCounts[5] = { 50, 20, 100, 50, 1 };
				int coinsLength = 5;
				changeMachine.CashOut(coinValues, coinCounts, coinsLength);

				int coinValuesResult[5];
				int coinCountsResult[5];
				int coinsLengthResult;
				changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
				Assert::AreEqual(5, coinsLengthResult);
				for (int i = 0; i < coinsLengthResult; i++)
				{
					Assert::AreEqual(coinValuesOrig[i], coinValuesResult[i]);
					Assert::AreEqual(coinCountsOrig[i], coinCountsResult[i]);
				}
			}
			catch (std::exception)
			{
				int coinValuesResult[5];
				int coinCountsResult[5];
				int coinsLengthResult;
				changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
				Assert::AreEqual(5, coinsLengthResult);
				for (int i = 0; i < coinsLengthResult; i++)
				{
					Assert::AreEqual(coinValuesOrig[i], coinValuesResult[i]);
					Assert::AreEqual(coinCountsOrig[i], coinCountsResult[i]);
				}
			}
		}

		TEST_METHOD(payChange1)
		{
			ChangeMachine changeMachine;

			changeMachine.StartExchange();
			int coinValues[5] = { 5, 10, 25, 50, 100 };
			int coinCounts[5] = { 5, 5, 5, 5, 5 };
			int coinsLength = 5;
			changeMachine.EndExchange(1, coinValues, coinCounts, coinsLength);

			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);

			changeMachine.PayChange(280, coinValues, coinCounts, &coinsLength);
			Assert::AreEqual(coinCounts[4], 2);
			Assert::AreEqual(coinCounts[3], 1);
			Assert::AreEqual(coinCounts[2], 1);
			Assert::AreEqual(coinCounts[1], 0);
			Assert::AreEqual(coinCounts[0], 1);

			int coinValuesResult[5];
			int coinCountsResult[5];
			int coinsLengthResult;
			changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
			Assert::AreEqual(coinsLength, coinsLengthResult);
			for (int i = 0; i < coinsLengthResult; i++)
			{
				int count = coinCountsOrig[i] - coinCounts[i];
				Assert::AreEqual(coinValues[i], coinValuesResult[i]);
				Assert::AreEqual(count, coinCountsResult[i]);
			}
		}

		TEST_METHOD(payChange2)
		{
			ChangeMachine changeMachine;
			int coinValuesOrig[5];
			int coinCountsOrig[5];
			int coinsLengthOrig;
			changeMachine.GetCountCoinList(coinValuesOrig, coinCountsOrig, &coinsLengthOrig);
			try
			{
				int coinValues[5];
				int coinCounts[5];
				int coinsLength;
				changeMachine.PayChange(10000, coinValues, coinCounts, &coinsLength);
				Assert::Fail(L"No exception", LINE_INFO());
			}
			catch (std::exception)
			{
				int coinValuesResult[5];
				int coinCountsResult[5];
				int coinsLengthResult;
				changeMachine.GetCountCoinList(coinValuesResult, coinCountsResult, &coinsLengthResult);
				Assert::AreEqual(5, coinsLengthResult);
				for (int i = 0; i < coinsLengthResult; i++)
				{
					Assert::AreEqual(coinValuesOrig[i], coinValuesResult[i]);
					Assert::AreEqual(coinCountsOrig[i], coinCountsResult[i]);
				}
			}
		}
	};
}
