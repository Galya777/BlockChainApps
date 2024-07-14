#pragma once
struct User {
    unsigned id;
    char name[128];
};

struct Transaction {
    unsigned sender;
    unsigned receiver;
    double coins;
    long long time;
};

struct TransactionBlock {
    unsigned id;
    unsigned prevBlockId;
    unsigned prevBlockHash;
    int validTransactions;
    Transaction transactions[16];
};

struct UserExtend
{
	User user;
    double balance;
};

struct BlockExtend {
    TransactionBlock block;
    int sum;
};
