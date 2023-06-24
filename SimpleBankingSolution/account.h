#ifndef ACCOUNT_H
#define ACCOUNT_H
// account class for holding account details of a customer. 
class account{
    private:
        int ACCPIN;
        int ATMPIN;
    public:
        bool ATMService;    // says if the person is registered for ATMM services or not
        int accNumber;
        string accHolderName;
        double accBalance;
        
        // if a person opts not to use ATM service
        account(int ACCNUM, string ACCHOLDER, int inputPIN, double BALANCE);

        // if a person opts to use ATM service
        account(int ACCNUM, string ACCHOLDER, int inputPIN, double BALANCE, int ATM_FRESH_PIN);


        friend class BANK;
        friend class ATM;
};

#endif