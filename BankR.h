#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

struct TransHistory            //sets characteristics for an accounts transaction history
{
	char sign;
	double amountChanged;
	double totalBalance;
};


struct Account         //sets characteristics for a bank account
{
	std::string name;
	int accNum;
	double balance = 0;
	std::vector <TransHistory> transactionHistory;        //incorporates a vector with all the qualities of transacton history in the Account struct
};

class Bank
{
private:
	std::vector <Account> allAccounts;        // creates vector to hold all accounts
	Account* currUser = nullptr;         

public:
	Bank();

	bool saveAccount();
	bool loadAccounts();
	bool withdraw(int accountNum, double amount);
	bool deposit(int accountNum, double amount);
	void checkBalance(int accountNum);
	void checkTransHist(int accountNum);
	Account* createAcc(std::string name, int accountNum);
	Account* findAcc(int accountNum);
	

};

bool endTransaction();
void options();
void clearScreen();
