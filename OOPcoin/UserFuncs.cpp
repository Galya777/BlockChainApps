#include "UserFuncs.h"
#include <iostream>
#define MAX 1000
UserFuncs::UserFuncs()
{
	createSystemUser();
}

UserFuncs::UserFuncs(const UserFuncs& other)
{
	copy(other);
}

UserFuncs& UserFuncs::operator=(const UserFuncs& other)
{
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
	// TODO: insert return statement here
}

UserFuncs::~UserFuncs()
{
	del();
}

UserExtend* UserFuncs::getUsers() 
{
	return users;
}

int UserFuncs::getSize() const
{
	return userSize;
}

int UserFuncs::findByID(int id) const
{
	for (size_t i = 0; i < userSize; ++i) {
		if (users[i].user.id==id) {
			return i;
		}
	}
	return -1;
}

bool UserFuncs::compare(UserExtend one, UserExtend two)
{
	return one.balance < two.balance;
}

void UserFuncs::quickSort(UserExtend* arr, int length, bool reverse)
{
	if (length <= 1) {
		return;
	}
	const int pivot_count = arr[length / 2].balance;
	int smaller_length = 0;
	int bigger_length = 0;
	int equal_length = 0;

	for (int i = 0; i < length; i++) {
		if (!reverse) {
			if (arr[i].balance < pivot_count) smaller_length++;
			if (arr[i].balance > pivot_count) bigger_length++;
		}
		else {
			if (arr[i].balance > pivot_count) smaller_length++;
			if (arr[i].balance < pivot_count) bigger_length++;
		}
		if (arr[i].balance == pivot_count) equal_length++;
	}

	UserExtend* smaller = new UserExtend[smaller_length];
	UserExtend* bigger = new UserExtend[bigger_length];
	UserExtend* equal = new UserExtend[equal_length];

	int smaller_i = 0;
	int bigger_i = 0;
	int equal_i = 0;

	// comparisons, this part should be pluggable to make this generic
	for (int i = 0; i < length; i++) {
		if (!reverse) {
			if (arr[i].balance < pivot_count) smaller[smaller_i++] = arr[i];
			if (arr[i].balance > pivot_count) bigger[bigger_i++] = arr[i];
		}
		else {
			if (arr[i].balance > pivot_count) smaller[smaller_i++] = arr[i];
			if (arr[i].balance < pivot_count) bigger[bigger_i++] = arr[i];
		}
		if (arr[i].balance == pivot_count) equal[equal_i++] = arr[i];
	}

	quickSort(smaller, smaller_length, reverse);
	quickSort(bigger, bigger_length, reverse);

	int j = 0;
	// now overwrite the original array with:
	// smaller + equal + bigger

	for (int i = 0; i < smaller_length; i++) arr[j++] = smaller[i];
	for (int i = 0; i < equal_length; i++) arr[j++] = equal[i];
	for (int i = 0; i < bigger_length; i++) arr[j++] = bigger[i];
}

void UserFuncs::printUsers(int num)
{
	if (num > userSize) return;
	for (size_t i = 0; i < num; i++)
	{
	std::cout << "name: " << users[i].user.name << " balance: " << users[i].balance;
	}
	std::cout << "\n";
}

Transaction UserFuncs::getTransaction() const
{
	return transaction;
}

void UserFuncs::readFromFile(std::fstream& file)
{
	for (size_t i = 0; i < userSize; i++)
	{
		file >> users[i].user.id;
		file.read((char*)users[i].user.name, sizeof(users[i].user.name));
		file>> users[i].balance;
	}
}

void UserFuncs::writeToFile(std::fstream& file)
{
	for (size_t i = 0; i < userSize; i++)
	{
		file << users[i].user.id << " " << "name: " << users[i].user.name << " balance: " << users[i].balance;
	}
	file <<"\n";
}

void UserFuncs::createSystemUser()
{	
	User admin;
	admin.id = 0;
	users = new UserExtend[100];
	strcpy(admin.name, "admin");
	users[userSize].user = admin;
	users[userSize].balance = 1000;
	userSize++;
}

int UserFuncs::findTheUser(const char* name)
{
	for (size_t i = 0; i < userSize; ++i) {
		if (strcmp(users[i].user.name, name) == 0) {
			return i;
		}
	}
	return -1;
}

void UserFuncs::create_user(const char* name, int sum)
{
	User newUser;
	newUser.id= THIS_ID;
	++THIS_ID;
	strcpy(newUser.name, name);
	transaction.sender= users[0].user.id;
	transaction.coins = 450 * sum;
	transaction.receiver = newUser.id;
	users[userSize].user = newUser;
	users[userSize].balance = sum;
	++userSize;

}

void UserFuncs::remove_user(const char* name)
{
	if (findTheUser(name) != -1) {
		for (size_t i = 0; i < userSize; i++)
		{
			if (strcmp(users[i].user.name, name) == 0)
			{
				for (size_t j = i; j < (userSize - 1); j++)
					users[j] = users[j + 1];
				i--;
				userSize--;
			}
		}
	}
	else {
		std::cout << "This user is not in the database!\n";
	}
}

void UserFuncs::copy(const UserFuncs& other)
{
	this->users = other.users;
	this->userSize = other.userSize;
}

void UserFuncs::del()
{
	delete[] users;
}
