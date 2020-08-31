// O bloco ifdef a seguir é a forma padrão de criar macros que tornam a exportação
// de uma DLL mais simples. Todos os arquivos nessa DLL são compilados com CHANGEMACHINE_EXPORTS
// símbolo definido na linha de comando. Esse símbolo não deve ser definido em nenhum projeto
// que usa esta DLL. Desse modo, qualquer projeto cujos arquivos de origem incluem este arquivo veem
// Funções CHANGEMACHINE_API como importadas de uma DLL, enquanto esta DLL vê símbolos
// definidos com esta macro conforme são exportados.
#ifdef CHANGEMACHINE_EXPORTS
#define CHANGEMACHINE_API __declspec(dllexport)
#else
#define CHANGEMACHINE_API __declspec(dllimport)
#endif

#include <memory>
#include <exception>
#include "CoinUnit.h"
#include "Hopper.h"
#include "CoinUnitDB.h"

// Esta classe é exportada da DLL
class CHANGEMACHINE_API ChangeMachine {
public:
	enum class ExchandeKind { INITIAL, INCREMENTAL};

	ChangeMachine(void);

	void StartExchange(void);
	void EndExchange(int kind, int *coinValues, int *coinCounts, int coinsLength);
	void CashOut(int* coinValues, int* coinCounts, int coinsLength);
	void PayChange(int cash, int* coinValues, int* coinCounts, int *coinsLength);
	void GetCountCoinList(int* coinValues, int* coinCounts, int* coinsLength);

private:
	void loadCoinUnit(void);

	CoinUnitDB db = CoinUnitDB("cashunit.config");
	std::unique_ptr<CoinUnit> coinUnit;
	bool isExchangeActive;
};

extern CHANGEMACHINE_API int nChangeMachine;

CHANGEMACHINE_API int fnChangeMachine(void);
