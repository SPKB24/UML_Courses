//**                                 **//
//                                     //
// PROGRAM NAME: account_client.cc     //
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

int main(int argc, char * argv[])
{
	Account a;	//account initialized via default constructor
	Account b(100);	//account initialized via custom constructor
	double a_withdraw, b_withdraw;
	double a_deposit, b_deposit;

	//WITHDRAW	
	cout << "How much would you like to withdraw from Account a?: $";
	cin >> a_withdraw;

	cout << "How much would you like to withdraw from Account b?: $";
	cin >> b_withdraw;

	a.debit(a_withdraw);
	b.debit(b_withdraw);

	cout << "Account a has $" << a.getBalance() << endl;
	cout << "Account b has $" << b.getBalance() << endl;
	cout << endl;

	//DEPOSIT
	cout << "How much would you like to deposit to Account a?: $";
	cin >> a_deposit;

	cout << "How much would you like to deposit to Account b?: $";
	cin >> b_deposit;

	a.credit(a_deposit);
	b.credit(b_deposit);

	cout << "Account a has $" << a.getBalance() << endl;
	cout << "Account b has $" << b.getBalance() << endl;
	cout << endl;

	//TOTAL VALUE (ADD BOTH ACCOUNTS)
	cout << "Account a + Account b = $" << a.addAccountBalance(b) << endl;

	a.setBalance(10000);

	cout << "Account a + Account b = $" << a.addAccountBalance(b) << endl;

	return 0;
}
