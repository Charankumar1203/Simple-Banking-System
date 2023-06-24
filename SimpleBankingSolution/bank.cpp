#include "global.h"
#include "account.h"
#include "BANK.h"

bool isNumber(string s)
{
    for (uint i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}

int getAccPin(){
    string _pin;
    FORPIN_ : cin >> _pin;
    if(_pin.size() > 8){
        cerr << "Maximum length of Pin is 8!\n";
        goto FORPIN_;
    }
    else if(_pin.size() < 4){
        cerr << "Minimum length of Pin is 4!\n";
        goto FORPIN_;
    }
    if(!isNumber(_pin)){
        cerr << "Enter numerical Pin!\n";
        goto FORPIN_;
    }
    if(stoi(_pin) < 1000){
        cerr << "The pin number lies between 1000 - 99999999. \n";
        goto FORPIN_;
    }
    return stoi(_pin);
}

BANK::BANK(int managerPin){
    masterPin = managerPin;
    numofAccsOpen = 0;
    isBankOpen = false;
    while (accNumsNOTinUse.empty()){
        accNumsNOTinUse.pop();
    }
}

BANK::BANK(){
    numofAccsOpen = 0;
    isBankOpen = false;
    while (accNumsNOTinUse.empty()){
        accNumsNOTinUse.pop();
    }
}

void BANK::openBank(int managerPin){
    masterPin = managerPin;
    numofAccsOpen = 0;
    customers.clear();
    isBankOpen = true;
    accNumsInUse.clear();
    for (int i =100000001; i < 101000001; i++){
        accNumsNOTinUse.push(i);
    }
}

void BANK::changeManagerPin(int previousPIN, int newPin){
    if (previousPIN != masterPin){
        cerr << "Invalid manager pin!\n";
        return;
    }
    else{
        masterPin = newPin;
        cerr << "The manager pin is updated successfully!\n";
    }
    return;
}
// void openBank(int managerPin);

void BANK::openAccount(){
    if (accNumsNOTinUse.empty()){
        // max num of accounts in this bank = 1 MILLION
        cerr << "NUMBER OF USERS EXCEEDED! PLEASE TRY AFTER ANYONE CLOSES THEIR ACCOUNT\n";
        return;
    }
    int newAccNum = accNumsNOTinUse.front();
    accNumsNOTinUse.pop();
    accNumsInUse.insert(newAccNum);

    int FRESHPIN;
    int ATM_FRESH_PIN;
    double AMOUNT_;
    string ACC_HOLDER_NAME;
    string YES_OR_NO;
    bool needATMService;
    account *NEW_ACCOUNT = NULL;
    cout << "Your account is being created with A/c No : " << newAccNum << endl;
    cout << "Please enter your name : ";
    cin >> ACC_HOLDER_NAME;

    GETAMOUNT_:
    string amt;
    cout << "Enter the amount which you wish to deposit for the first time : ";
    cin >> amt;
    if(!isNumber(amt)) goto GETAMOUNT_;
    else AMOUNT_ = stod(amt);

    cout << "Enter your new pin for the bank transactions : ";
    FRESHPIN = getAccPin();

FOR_ATM_SERVICE:
    cout << "Do you want ATM service for your account? [y/n] : ";
    cin >> YES_OR_NO;
    if (YES_OR_NO.size() != 1){
        goto FOR_ATM_SERVICE;
    }
    else{
        if (YES_OR_NO[0] == 'y'){
            needATMService = true;
            cout << "Please enter the new ATM Pin : ";
            cin >> ATM_FRESH_PIN;
        }
        else{
            needATMService = false;
        }
    }

    //now create the account accordingly
    if (needATMService){
        NEW_ACCOUNT = new account(newAccNum, ACC_HOLDER_NAME, FRESHPIN, AMOUNT_, ATM_FRESH_PIN);
    }
    else{
        NEW_ACCOUNT = new account(newAccNum, ACC_HOLDER_NAME, FRESHPIN, AMOUNT_);
    }

    customers[newAccNum] = NEW_ACCOUNT;
    // index++;
    numofAccsOpen++;
};


void BANK::getBalance(int accNum, int PIN){
    if(accNumsInUse.find(accNum) == accNumsInUse.end()){
        cerr << "Acc number doesnt exists!\n";
        return;
    }
    if (PIN == customers[accNum]->ACCPIN){
        cout << "Hey " << customers[accNum]->accHolderName;
        cout << " Your current account balance is : " << customers[accNum]->accBalance << endl;
        return;
    }
    else{
        cerr << "INVALID PIN ENTERED!\n";
    }
    return;
};

void BANK::withdrawAmount(int accNum, int withdraw, int PIN){
    if(accNumsInUse.find(accNum) == accNumsInUse.end()){
        cerr << "Acc number doesnt exists!\n";
        return;
    }
    if (PIN == customers[accNum]->ACCPIN){
        if (customers[accNum]->accBalance >= withdraw){
            customers[accNum]->accBalance -= withdraw;
        }
        else{
            cerr << "Insufficient Funds.\n";
            return;
        }

        cout << "Hey " << customers[accNum]->accHolderName;
        cout << "Amount withdrawn. Your new account balance is : " << customers[accNum]->accBalance << endl;
        return;
    }
    else{
        cerr << "INVALID PIN ENTERED!\n";
    }
    return;
};

void BANK::depositAmount(int accNum, double deposit){
    if(accNumsInUse.find(accNum) == accNumsInUse.end()){
        cerr << "Acc number doesnt exists!\n";
        return;
    }
    //anyone can deposit amount in anyone's account without any pin
    customers[accNum]->accBalance += deposit;
    return;
};

void BANK::printAllAccounts(int sp_pin){
    if (sp_pin != masterPin){
        cerr << "Invalid manager pin.\n";
        return;
    }
    cout << "Acc No.  -----> Acc Holder Name -----> ";
    cout << "Acc Balance\n";
    for (auto i : customers){
        cout << i.first << " -----> " << i.second->accHolderName;
        cout << " -----> " << i.second->accBalance << endl;
    }
    cout << endl;
};

bool BANK::verifyAccount(int accNumber, int PIN_){
    if (accNumsInUse.find(accNumber) != accNumsInUse.end()){
        if (customers[accNumber]->ACCPIN == PIN_){
            return true;
        }
    }
    return false;
};

void BANK::deleteAnAccount(int accNum, int inputPin){
    if (verifyAccount(accNum, inputPin)){
        numofAccsOpen--;
        accNumsInUse.erase(accNum);
        accNumsNOTinUse.push(accNum);
        free(customers[accNum]);
        customers.erase(accNum);
        cerr << "The account has been deleted succesfully!\n";
    }
    else{
        cerr << "Entered acc number or pin is invalid!\n";
    }
    return;
};

void BANK::closeBank(int sp_pin){
    if (isBankOpen){   
        if(sp_pin != masterPin){
            cerr << "Invalid Pin entered!\n";
            return;
        }
        isBankOpen = false;
        for (auto i : customers){
            free(i.second);
        }
        customers.clear();
        numofAccsOpen = 0;
        accNumsInUse.clear();
        while (accNumsNOTinUse.empty()){
            accNumsNOTinUse.pop();
        }
    }
};

// when the user who didnt opt for ATM service while opening the account and
// thinks to opt for it at later point of time
void BANK::registerForATMService(int accNUm, int inputAccPIN, int inputATMPIN)
{
    if(verifyAccount(accNUm, inputAccPIN)){
        if(customers[accNUm]->ATMService){
            cerr << "You have an active ATM service. No need to do again.\n";
        }
        else{
            customers[accNUm]->ATMService = true;
            customers[accNUm]->ATMPIN = inputATMPIN;
        }
    }
}
