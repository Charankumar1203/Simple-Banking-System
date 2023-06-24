#include "global.h"
#include "BANK.h"
#include "ATM.h"
//ATM functions.

bool BANK::ATM_verifyAccount(int accNumber, int PIN_){
    if (accNumsInUse.find(accNumber) != accNumsInUse.end()){
        if (customers[accNumber]->ATMPIN == PIN_){
            return true;
        }
    }
    return false;
}

void BANK::displayBalance_ATM(int PIN, int accNum)
{
    if (PIN == customers[accNum]->ATMPIN)
    {
        cout << "Hey " << customers[accNum]->accHolderName;
        cout << " Your current account balance is : " << customers[accNum]->accBalance << endl;
        return;
    }
    else
    {
        cerr << "INVALID PIN ENTERED!\n";
    }
    return;
}

void BANK::withDrawBalance_ATM(int accNum, int PIN, int _amount)
{
    if (PIN == customers[accNum]->ATMPIN)
    {
        withdrawAmount(accNum, _amount, customers[accNum]->ACCPIN);
    }
    else
    {
        cerr << "Invalid Pin entered.\n";
    }
    return;
}

void BANK::changeATMpin(int prevPIN, int newPIN, int accNum)
{
    if (prevPIN == customers[accNum]->ATMPIN)
    {
        customers[accNum]->ATMPIN = newPIN;
    }
    else
    {
        cerr << "Invalid Pin entered.\n";
    }
    return;
}
