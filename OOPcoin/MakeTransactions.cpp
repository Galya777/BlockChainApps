#include "MakeTransactions.h"

MakeTransactions::MakeTransactions(UserFuncs& us)
{
	this->us = us;
	trans.coins = 0;
	trans.receiver = 0;
	trans.sender = 0;
	trans.time = 0;
}

Transaction MakeTransactions::getTrans() const
{
	return trans;
}

void MakeTransactions::send_coins(int sender, int receiver, double balance)
{
	time_t seconds;
	seconds = time(NULL);
	if (us.findByID(sender) == -1 || us.findByID(receiver) == -1)
		std::cout << "No such users!\n";
	int indS = us.findByID(sender);
	int indR = us.findByID(receiver);
	if(us.getUsers()[indS].balance<balance)
		std::cout << "Not enough money!\n";

	us.getUsers()[indS].balance -= balance;
	us.getUsers()[indR].balance += balance;
	trans.receiver = receiver;
	trans.sender = sender;
	trans.coins = balance;
	trans.time = seconds;
}

void MakeTransactions::setTrans(Transaction trans)
{
	this->trans.coins = trans.coins;
	this->trans.sender = trans.sender;
	this->trans.receiver = trans.receiver;
	this->trans.time = trans.time;
}
