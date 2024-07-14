#pragma once
#include "UserFuncs.h"
#include <time.h>
#include <iostream>


class MakeTransactions
{
public:
    MakeTransactions(UserFuncs& us);
    Transaction getTrans() const;
    void send_coins(int sender, int receiver, double balance);
    void setTrans(Transaction trans);

private:
    UserFuncs us;
	Transaction trans;
};

