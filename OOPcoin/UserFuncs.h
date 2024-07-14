#pragma once
#include <cstring>
#include "UserExtend.h"
#include <fstream>
#pragma warning(disable:4996)

class UserFuncs
{
   static int THIS_ID;
public:
    UserFuncs();
    UserFuncs(const UserFuncs& other);
    UserFuncs& operator=(const UserFuncs& other);
    ~UserFuncs();

    UserExtend* getUsers();
    int  getSize() const;
    int findByID(int id) const;

    bool compare(UserExtend one, UserExtend two);
    void quickSort(UserExtend* arr, int length, bool reverse);
    void printUsers(int num);

    Transaction getTransaction() const;

    //read from file
    void readFromFile(std::fstream& file);
    //write to file
    void writeToFile(std::fstream& file);
    
    void create_user(const char* name, int sum);
    void remove_user(const char* name);
private:
    void copy(const UserFuncs& other);
    void del();
   
    void createSystemUser();
    int findTheUser(const char* name);
    UserExtend* users;
    size_t userSize=0;
    Transaction transaction;
};
int UserFuncs::THIS_ID = 1;
