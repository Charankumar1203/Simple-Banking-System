#include "global.h"
#include "account.h"

// if a person opts not to use ATM service
account::account(int ACCNUM, string ACCHOLDER, int inputPIN, double BALANCE)
{
    accNumber = ACCNUM;
    accHolderName = ACCHOLDER;
    accBalance = BALANCE;
    ACCPIN = inputPIN;
    ATMService = false;
}

// if a person opts to use ATM service
account::account(int ACCNUM, string ACCHOLDER, int inputPIN, double BALANCE, int ATM_FRESH_PIN)
{
    accNumber = ACCNUM;
    accHolderName = ACCHOLDER;
    accBalance = BALANCE;
    ACCPIN = inputPIN;
    ATMPIN = ATM_FRESH_PIN;
    ATMService = false;
}
