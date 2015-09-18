//**                                 **//
//                                     //
// PROGRAM NAME: Account.h             //
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

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{

public:
	//CONSTRUCTORS
	Account(void);
	Account(double balance);
	
	//INTERFACE
	bool credit(double addAmount);
	bool debit(double withdrawAmount);
	double addAccountBalance(Account b);

	//GETTER
	double getBalance();

	//SETTER/CHANGER
	void setBalance(double balance);

private:
	double accountBalance; //Hold current account balance

};

#endif
