#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

#include "BankR.h"


Bank::Bank()    // initializes bank
{

}


bool Bank::saveAccount()          //function to save account info including nested vector information
{
	std::ofstream outFile("account_info.txt");
	if (!outFile)
	{
		return false;
	}

	for (const auto& acc : allAccounts)
	{
		outFile << acc.name << "\n" << acc.accNum << "\n" << acc.balance << "\n";
	
		outFile << acc.transactionHistory.size() << "\n";

		for (const auto& accHist : acc.transactionHistory)
		{
			outFile << accHist.sign << " " << accHist.amountChanged << " " << accHist.totalBalance << "\n";
		}
	}
	outFile.close();
	return true;
}

bool Bank::loadAccounts()                // loads all information for accounts
{
	std::ifstream inFile("account_info.txt");
	if (!inFile)
	{
		std::cout << "Failed to load accounts.  Terminating Program.";
		return false;
		
	}

	allAccounts.clear();
	std::string name;
	while (std::getline(inFile, name))
	{
		Account tempAcc;
		tempAcc.name = name;
		size_t historySize;
		if (!(inFile >> tempAcc.accNum >> tempAcc.balance >> historySize)) break;

		for (size_t i = 0; i < historySize; i++)
		{
			TransHistory hpush;
			inFile >> hpush.sign >> hpush.amountChanged >> hpush.totalBalance;
			tempAcc.transactionHistory.push_back(hpush);
		}
	inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	allAccounts.push_back(tempAcc);
    }
	inFile.close();
	return true;
}

void options()           //The basic user interface screen
{
	std::cout << "Please choose an option:\n\n";
	std::cout << "A. Deposit \nB. Withdraw \nC. Check Balance \nD. Check Transaction History \nE. Logout \nF. End Transaction \n\n";
}

bool Bank::withdraw(int accNum, double amount)        //function to withdraw money from account while making sure to stop overdafting
{
	Account* currAccount = (findAcc(accNum));
		if (currAccount->balance >= amount)
		{
			currAccount->balance -= amount;
			clearScreen();
			std::cout << "Your current balance is " << currAccount->balance << "\n\n";
			currAccount->transactionHistory.push_back({ '-', amount, currAccount->balance });
			saveAccount();
			return true;
			
		}
		else
		{
			std::cout << "Not Enough Money In Accout. Please Try Again. \n";
			return false;
		}
	
}

bool Bank::deposit(int accNum, double amount)              //function to add money to account while making sure no negative values are added
{

	Account* currAccount = (findAcc(accNum));
	
	if (amount > 0)
	{
		currAccount->balance += amount;
		clearScreen();
		std::cout << "Your current balance is " << currAccount->balance << "\n\n";
		currAccount->transactionHistory.push_back({ '+', amount, currAccount->balance });
		saveAccount();
		return true;
	}
	else
	{
		std::cout << "Deposit cannot be less than $0.01. Please Try Again. \n";
		return false;
	}

}

void Bank::checkBalance(int accNum)             //function to see account balance
{
	Account* currAcct = findAcc(accNum);
	clearScreen();
	std::cout << "Your Current Balance is " << currAcct->balance;
}

void Bank::checkTransHist(int accNum)                // function to read collected transaction information from nested vector
{
	Account* currAcct = findAcc(accNum);
	clearScreen();
	std::cout << "All Previous Transactions:\n";
	for (size_t i = 0; i < currAcct->transactionHistory.size(); i++)
	{
		std::cout << currAcct->transactionHistory[i].sign << "$" << currAcct->transactionHistory[i].amountChanged << "| Total Balance: " << currAcct->transactionHistory[i].totalBalance << "\n\n";
	}
}

Account* Bank::createAcc(std::string name, int accNum)        //function to create and save an account
{
	if (findAcc(accNum) != nullptr)
	{
		std::cout << "There is already an account associated with this account number. \n";
		return nullptr;
	}

	Account newAcc;
	newAcc.name = name;
	newAcc.accNum = accNum;
	newAcc.balance = 0;

	allAccounts.push_back(newAcc);
	saveAccount();

	Account* currAccount = findAcc(accNum);
	return currAccount;
}

Account* Bank::findAcc(int accNum)             //function to find a pointer to specific accounts
{
	for (size_t i = 0; i < allAccounts.size(); i++)
	{
		if (allAccounts[i].accNum == accNum)
		{
			return &allAccounts[i];
		}

	}
		return nullptr;
		
	
}

bool endTransaction()        //function required to terminate program
{
	char choice;

	std::cout << "\n\nWould you like to end the transaction? \nA. Yes \nB. No\n";
	std::cin >> choice;
	choice = toupper(choice);
	std::cout << "\x1b[2J\x1b[1;1H";
	if (choice == 'A')
	{
		return true;
	}
	return false;

}

void clearScreen()                  // uses codes to clear the screen and show basic bank name
{
	std::cout << "\x1b[2J\x1b[1;1H";
	std::cout << " ------------ \n Refresh Bank \n ------------ \n";
}
