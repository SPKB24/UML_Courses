//**                                 **//
//                                     //
// PROGRAM NAME: Account.cc            //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
//  ##  #  # # ### ###     ##   #  #   //
// #   # # # #  #   #      # # # # #   //
//  #  # # ###  #   #      ##  ### #   //
//   # # # # #  #   #      #   # # #   //
// ##   #  # # ###  #      #   # # ### //
//                                     //
// DATE: March 2, 2014                 //
//                                     //
//**                                 **//

#include <iostream>
#include "Account.h"
using namespace std;

Account::Account()
{
	accountBalance = 0; //Initialize Account Balance to 0
}

Account::Account(double balance)
{
	if (balance >= 0.0) //Balance should be positive
		accountBalance = balance;
	else
	{
		accountBalance = 0;
		cout << "ERROR: The value you entered was too low." << endl
			<< "Account Balance has been set to $0.00" << endl;
	}
}

bool Account::credit(double addAmount)
{
	if (addAmount >= 0) //Amount should be positive
		accountBalance += addAmount;
	else
	{
		cout << "ERROR: The value you entered was too low" << endl;
		return false;
	}

	return true;
}

bool Account::debit(double withdrawAmount)
{
	//Amount should be positive and should be less than account balance
	if (withdrawAmount >= 0 && (accountBalance - withdrawAmount >= 0)) 
		accountBalance -= withdrawAmount;
	else
	{
		if (withdrawAmount < 0)
			cout << "ERROR: The value you entered was too low." << endl;
		else
			cout << "ERROR: You have insufficient funds in your account" << endl;
		return false;
	}

	return true;
}

double Account::addAccountBalance(Account b)
{
	return accountBalance + b.getBalance();
}

double Account::getBalance(void)
{
	return accountBalance;
}

void Account::setBalance(double balance)
{
	accountBalance = balance;
}

