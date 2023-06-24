#include "global.h"
#include "account.h"
#ifndef BANK_H
#define BANK_H

class BANK{
    private:
        int masterPin;
        
    public:
        int numofAccsOpen;
        unordered_map<int, account*> customers;
        bool isBankOpen;
        unordered_set<int>accNumsInUse;
        queue<int>accNumsNOTinUse;
        const int _STARTNUM = 100000001; //starting of acc numbers
        // int index = _STARTNUM;  //used to assign the next available acc number
        //Default constructor
        BANK();
        //another useful constructor
        BANK(int managerPin);

        void openBank(int managerPin);

        void changeManagerPin(int previousPIN, int newPin);

        void openAccount();

        void getBalance(int accNum, int PIN);
        
        void withdrawAmount(int accNum, int withdraw, int PIN);

        void depositAmount(int accNum, double deposit);

        void printAllAccounts(int sp_pin);
        
        // when the user who didnt opt for ATM service while opening the account and
        // thinks to opt for it at later point of time
        void registerForATMService(int accNUm, int inputAccPIN, int inputATMPIN);

        bool verifyAccount(int accNumber, int PIN_);

        void deleteAnAccount(int accNum, int inputPin);

        void closeBank(int sp_pin);


        // ATM functions:

        //verify if the acc num exists and the pin entered matches with the actual pin 
        bool ATM_verifyAccount(int accNumber, int PIN_);
        
        void displayBalance_ATM(int PIN, int accNum);

        void withDrawBalance_ATM(int accNum, int PIN, int amount);

        void changeATMpin(int prevPIN, int newPIN, int accNum);



};

#endif