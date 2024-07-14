#include <iostream>
#include <fstream>
#include "UserFuncs.h"
#include "TrBlock.h"
#include "MakeTransactions.h"
int main()
{
    UserFuncs usersl;
    TrBlock bl;
    std::fstream UserFile("users.dat", std::ios::binary | std::ios::in | std::ios::out);
    std::fstream BlockFile("blocks.dat", std::ios::binary | std::ios::in | std::ios::out);
     if (UserFile.is_open() && BlockFile.is_open()) {
         usersl.readFromFile(UserFile);
         bl.readFromFile(BlockFile);

         std::cout << "File successfully opened!" << std::endl;
     }
     else {
         UserFile.open("users.dat", std::ios::app);
         BlockFile.open("blocks.dat", std::ios::app);
         std::cout << "Files not excisting or empty!\n";
     }
   
    char* command = new char[128];
    if (!command) {
        std::cout << "Not enough memory!\n";
        return -1;
    }
    
    MakeTransactions makeTr(usersl);
    do {
        std::cout << "Enter comand: ";

   std::cin.getline(command, 20);
   if (strcmp(command, "create-user")==0) {
       char* name = new char[128];
       if (!name) {
           std::cout << "Not enough memory!\n";
           return -1;
       }
       int sum;
       std::cout << "Enter name: ";
       std::cin.getline(name, 20);
       std::cout << "Enter sum: ";
       std::cin >> sum;
       usersl.create_user(name, sum);
       std::cout << "User successfully created!" << std::endl;
       makeTr.setTrans(usersl.getTransaction());
       bl.addTransaction(makeTr.getTrans());
       delete[] name;
   }
   else if (strcmp(command, "remove-user")==0) {
       char* name = new char[128];
       if (!name) {
           std::cout << "Not enough memory!\n";
           return -1;
       }
       int sum;
       std::cout << "Enter name: ";
       std::cin.getline(name, 20);
       usersl.remove_user(name);
       std::cout << "User successfully removed!" << std::endl;
       delete[] name;
   }else if (strcmp(command, "send-coins")==0) {
       int s, r;
       std::cout << "Enter sender id: ";
       std::cin >> s;
       std::cout << "Enter receiver id: ";
       std::cin >> r;
       double balance;
       std::cout << "Enter balance: ";
       std::cin >> balance;
       makeTr.send_coins(r, s, balance);
       bl.addTransaction(makeTr.getTrans());
   }
   else if (strcmp(command, "verify-transactions")==0) {
      std::cout<<bl.verify_transactions()?"valid":"invalid";
   }
   else if (strcmp(command, "wealthiest-users")==0) {
       int num;
       std::cout << "Enter number smaller than: " << usersl.getSize();
       std::cin >> num;
       while (num > usersl.getSize()) {
           std::cout << "Enter number smaller than: " << usersl.getSize();
           std::cin >> num;
       }
       usersl.quickSort(usersl.getUsers(), usersl.getSize(), false);
       usersl.printUsers(num);
   }
   else if (strcmp(command, "biggest-blocks")==0) {
       int num;
       std::cout << "Enter number smaller than: "<<bl.getSize();
       std::cin >> num;
       while (num > usersl.getSize()) {
           std::cout << "Enter number smaller than: " << bl.getSize();
           std::cin >> num;
       }
      bl.quickSort(bl.getBlocks(), bl.getSize(), false);
      bl.printBlocks(num);
   }
    } while (strcmp(command, "exit") != 0);
    delete[] command;
   usersl.writeToFile(UserFile);
   UserFile.close();
   bl.writeToFile(BlockFile);
   BlockFile.close();
    
    return 0;
}


/* както и на най - скъпите 
блокове(biggest - blocks).За всеки блок трябва да се изведе общото количество монети и поредният номер на блока.
И двете команди трябва да приемат аргумент число, което представлява броя записи(хора или блокове), които трябва да се изведат.
В резултат от изпълнението на командите трябва да се генерират текстови файлове, чието име се образува от името на командата и текущото 
вiреме в секунди.Те съдържат данните за съответните потребители или блокове, по един на ред.*/
