#include "global.h"
#include "account.h"
#include "BANK.h"
#include "ATM.h"

bool isNum(string s)
{
    for (uint i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}

int getPin(){
    string _pin;
    FORPIN : cin >> _pin;
    if(_pin.size() > 8){
        cerr << "Maximum length of Pin is 8!\n";
        goto FORPIN;
    }
    else if(_pin.size() < 4){
        cerr << "Minimum length of Pin is 4!\n";
        goto FORPIN;
    }
    if(!isNum(_pin)){
        cerr << "Enter numerical Pin!\n";
        goto FORPIN;
    }
    if(stoi(_pin) < 1000){
        cerr << "The pin number lies between 1000 - 99999999. \n";
        goto FORPIN;
    }
    return stoi(_pin);
}

int main(){
    int MASTERPIN;
    char type;
    string _type, AorB;
    cout << "Welcome manager! Enter the masterPin to open the bank\n";
    cout << "[4-8 digits; choose number above 1000 and below 99999999]: ";
    MASTERPIN = getPin();
    
    BANK myBank(MASTERPIN);
    myBank.openBank(MASTERPIN);
    vector <ATM> atms(10);

    for(int i=0; i<10; i++){
        atms[i].refillATM(1000000);
    }

    int inputMasterPin;
    int temp_accNUm, temp_PIN;
    double temp_amount;       
    string Y_OR_N;
    
    while(true){
        cout << "Welcome. Do you wish to go to the bank or ATM?";
        cout << "\n['A' for ATM and 'B' for Bank] : ";
        BANKORATM: cin >> AorB;
        if(AorB[1] != '\0'){
            cerr << "Enter a character!\n";
            goto BANKORATM;
        }
        if(AorB[0] == 'B'){
            cout << "C : [Manager] Change the manager Pin\n";
            cout << "P : [Manager] Print all accounts and their details\n";
            cout << "E : [Manager] Close all the accounts, ATMs and the bank and exit the program\n\n";
            cout << "N : [Customer] Open a new account\n";
            cout << "D : [Customer] Deposit amount in the bank\n";
            cout << "S : [Customer] Show balance of an account\n";
            cout << "W : [Customer] Withdraw amount from an account\n";
            cout << "K : [Customer] Delete an account\n";

            cout << "Enter the transaction type [choose one from the above] : ";
            TRANSACTIONTYPE: cin >> _type;
            if(_type[1] != '\0'){
                cerr << "Enter a character!\n";
                goto TRANSACTIONTYPE;
            }
            type = _type[0];
            cout<<endl;

            switch(type){
                case 'C':
                    cout << "Welcome Manager! Enter your Pin to proceed: ";
                    inputMasterPin = getPin();
                    if(inputMasterPin != MASTERPIN){
                        cerr << "Invalid Manager Pin entered!\n";
                    }
                    else{
                        cout << "Enter your new pin : ";
                        MASTERPIN = getPin();
                        myBank.changeManagerPin(inputMasterPin, MASTERPIN);
                    }
                    break;

                case 'P':
                    cout << "Welcome Manager! Enter your Pin to proceed: ";
                    inputMasterPin = getPin();
                    if(inputMasterPin != MASTERPIN){
                        cerr << "Invalid Manager Pin entered!\n";
                        break;
                    }
                    else{
                        if(myBank.numofAccsOpen == 0){
                            cerr << "No active accounts found!\n";
                            break;
                        }
                        cout << "Ac/No -----> Acc holder name -----> Balance\n";
                        for(auto i:myBank.customers){
                            cout << i.first << " -----> " << i.second->accHolderName;
                            cout << " -----> " << i.second->accBalance << endl;
                        }
                    }
                    break;

                case 'E':
                    cout << "Welcome Manager! Enter your Pin to proceed: ";
                    inputMasterPin = getPin();
                    if(inputMasterPin != MASTERPIN){
                        cerr << "Invalid Manager Pin entered!\n";
                        break;
                    }
                    else{
                        cerr << "Are you sure to close the bank? This will delete all the data! [y/n] : ";

                        FOREXITING : cout << "Do you want ATM service for your account? [y/n] : ";
                        cin >> Y_OR_N;
                        if (Y_OR_N.size() != 1){
                            cerr << "Enter a character!\n";
                            goto FOREXITING;
                        }
                        if(Y_OR_N[0] == 'y'){
                            myBank.closeBank(inputMasterPin);
                            cerr << "The bank is closed succesfully! Thank you. \n\n";
                            exit(0);
                        }
                    }
                    break;

                case 'N':
                    myBank.openAccount();
                    break;

                case 'D':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Enter the amount to be deposited : ";
                    cin >> temp_amount;
                    myBank.depositAmount(temp_accNUm, temp_amount);
                    break;

                case 'S':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the account Pin : ";
                    temp_PIN = getPin();
                    myBank.getBalance(temp_accNUm, temp_PIN);
                    break;

                case 'W':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Enter the amount to be deposited : ";
                    cin >> temp_amount;
                    cout << "Please enter the account Pin : ";
                    temp_PIN = getPin();
                    myBank.withdrawAmount(temp_accNUm, temp_amount, temp_PIN);
                    break;

                case 'K':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the account Pin : ";
                    temp_PIN = getPin();

                    cerr << "Do you really wish to delete your account?\n";

                    FORDELETINGACCOUNT : cout << "Do you want ATM service for your account? [y/n] : ";
                    cin >> Y_OR_N;
                    if (Y_OR_N.size() != 1){
                        cerr << "Enter a character!\n";
                        goto FORDELETINGACCOUNT;
                    }
                    if(Y_OR_N[0] == 'y'){
                        myBank.deleteAnAccount(temp_accNUm, temp_PIN);
                    }
                    break;
                default:
                    cerr << "Invalid Transaction type!\n\n";
                    break;
                
            }

        }

        else if(AorB[0] == 'A'){
            int atmIndex;
            int temp_ATMPIN;
            cout << "Enter which ATM you wish to go [1-10] : ";
            cin >> atmIndex;
            cout << "Welcome to ATM - " << atmIndex << endl;
            cout << "\nS : [Customer] Show balance of an account\n";
            cout << "W : [Customer] Withdraw amount from an account\n";
            cout << "G : [Customer] Register for ATM service if not done previously\n";
            cout << "C : [Customer] Change the ATM pin\n";
            cout << "R : [Manager] Refill the ATM with money\n";
            cout << "Enter the transaction type [choose one from the above] : ";
            ATM_TRANSACTIONTYPE: cin >> _type;
            if(_type[1] != '\0'){
                cerr << "Enter a character!\n";
                goto ATM_TRANSACTIONTYPE;
            }
            type = _type[0];
            cout<<endl;

            switch(type){
                case 'S':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the ATM Pin : ";
                    temp_ATMPIN = getPin();
                    if(myBank.ATM_verifyAccount(temp_accNUm, temp_ATMPIN)){
                        myBank.displayBalance_ATM(temp_ATMPIN, temp_accNUm);
                    }
                    else{
                        cerr << "Entered acc num or ATM PIN are wrong!\n";
                    }
                    break;

                case 'W':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the ATM Pin : ";
                    temp_ATMPIN = getPin();
                    if(myBank.ATM_verifyAccount(temp_accNUm, temp_ATMPIN)){
                        cout << "Enter amount to be withdrawn : ";
                        cin >> temp_amount;
                        if(atms[atmIndex].getAmount() < temp_amount){
                            cerr << "Cannot dispense required amount due to insufficient funds!\n";
                            cerr << "Please try again later.\n";
                            break;
                        }
                        atms[atmIndex].drawAmount(temp_amount);

                        myBank.withDrawBalance_ATM(temp_accNUm, temp_ATMPIN, temp_amount);
                    }

                    else{
                        cerr << "Entered acc num or ATM PIN are wrong!\n";
                    }
                    cout << "Thanks for using the ATM.\n";

                    break;

                case 'G':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the ACCPin : ";
                    temp_PIN = getPin();

                    if(myBank.verifyAccount(temp_accNUm, temp_PIN)){
                        cout << "Enter new ATM pin : ";
                        temp_ATMPIN = getPin();
                        myBank.registerForATMService(temp_accNUm, temp_PIN, temp_ATMPIN);
                    }
                    
                    else{
                        cerr << "Wrong acc no. or Pin entered!\n";
                    }
                    
                    break;

                case 'C':
                    cout << "Please enter the account number : ";
                    cin >> temp_accNUm;
                    cout << "Please enter the ATMPin : ";
                    temp_PIN = getPin();

                    if(myBank.ATM_verifyAccount(temp_accNUm, temp_PIN)){
                        cout << "Enter new ATM pin : ";
                        temp_ATMPIN = getPin();
                        myBank.changeATMpin(temp_PIN, temp_ATMPIN, temp_accNUm);
                    }
                    
                    else{
                        cerr << "Wrong acc no. or Pin entered!\n";
                    }
                    break;
                    
                
                case 'R':
                    cout << "Welcome manager! Please enter the amount to refil the atm : ";
                    cin >> temp_amount;
                    atms[atmIndex].refillATM(temp_amount);
                    break;
            }

        }

        else{
            cerr << "Enter correct character : A or B !\n\n";
        }

    }



    return 0;
}