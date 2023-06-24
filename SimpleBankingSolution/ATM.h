#include "BANK.h"
#ifndef ATM_H
#define ATM_H

class ATM : public BANK{
    private:
        double amount;
    public:
        ATM(int avl){
            amount = avl;
        }
        ATM(){
            amount = 0;
        }
        void refillATM(double money){
            amount += money;
        }

        double getAmount(){
            return amount;
        }

        void drawAmount(double _amount){
            amount -= _amount;
        }
        
};

#endif