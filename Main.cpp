#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

#include "BankR.h"


// Main function combines all functions to control the entire bank interface and have smooth functionality

int main()
{
	Bank myBank;
	myBank.loadAccounts();

	Account* currAccount = nullptr;

	std::string name;
	int accoNum;
	double balance;
	double amount;
	char choice;
	char finishTrans;
	bool logOut;
	bool endTrans = false;

	do {                                  //Set intital status for loops.  The rest sets up login log out loops.
		endTrans = false;
		logOut = false;
		std::cout << " ------------ \n Refresh Bank \n ------------ \n";
		std::cout << " Please Choose An Option: \n A: Login \n B: Create Account \n C: Quit Application \n";
		std::cin >> choice;
		choice = toupper(choice);

		switch (choice)
		{
		case 'A':

			clearScreen();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Login by entering account number between 8 and 9 digits: ";
			std::cin >> accoNum;
			
			do {
				if (myBank.findAcc(accoNum) == nullptr)
				{
					clearScreen();
					std::cout << "No account found.  Please try again. \n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Login by entering account number between 8 and 9 digits: ";
				
					std::cin >> accoNum;
				}
			} while (myBank.findAcc(accoNum) == nullptr);

			currAccount = myBank.findAcc(accoNum);         //sets current account to a ptr towards the index with the corrosponding account number

			clearScreen();

			std::cout << "Welcome " << currAccount->name << "\n\n\n";

			break;

		case 'B':

			clearScreen();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Enter Name: ";
			std::getline(std::cin, name);
			std::cout << "Enter Account Number between 8 and 9 digits: ";
			std::cin >> accoNum;
			myBank.createAcc(name, accoNum);

			currAccount = myBank.findAcc(accoNum);

			clearScreen();

			std::cout << "Welcome " << currAccount->name << "\n\n\n";

			break;

		case 'C':
			clearScreen();
			std::cout << "Thank you for banking with us.  Have a great Day\n\n";
			endTrans = true;
			return 0;

		default:
			clearScreen();
			std::cout << "Assuming C. \nThank you for banking with us.  Have a great Day\n\n";
			endTrans = true;
			return 0;

			break;

		};

		do {
			clearScreen();

			std::cout << "Welcome " << currAccount->name << "\n\n\n";

			options();
			std::cin >> choice;
			choice = toupper(choice);

			switch (choice)
			{
			case 'A':
				std::cout << "How much would you like to deposit: ";
				std::cin >> amount;
				myBank.deposit(accoNum, amount);
				endTrans = endTransaction();
				break;

			case 'B':
				std::cout << "How much would you like to withdraw: ";
				std::cin >> amount;
				myBank.withdraw(accoNum, amount);
				endTrans = endTransaction();
				break;

			case 'C':
				myBank.checkBalance(accoNum);
				endTrans = endTransaction();
				break;

			case 'D':
				myBank.checkTransHist(accoNum);
				endTrans = endTransaction();
				break;

			case 'E':
				currAccount = nullptr;
				endTrans = true;
				logOut = true;
				std::cout << "\x1b[2J\x1b[1;1H";               //code to clear screen

				break;

			case 'F':
				clearScreen();
				std::cout << "Thank you for banking with us.  Have a great Day\n\n";
				endTrans = true;
				return 0;

				break;

			default:
				clearScreen();
				std::cout << "Assuming F. \nThank you for banking with us.  Have a great Day\n\n";
				endTrans = true;
				return 0;
			}

		} while (endTrans == false);    // these 2 lines continue loop depending on actions taken

	} while (logOut == true);

	clearScreen();
	std::cout << "Thank you for banking with us.  Have a great Day\n\n";
	
	return 0;


}
