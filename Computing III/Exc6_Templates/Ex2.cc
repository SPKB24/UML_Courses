//**                                 **//
//                                     //
// PROGRAM NAME: Ex2.cc                //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: April 15, 2015                //
//                                     //
//**                                 **//

#include <iostream>
using namespace std;

template<typename T>
T incr(T one)
{
	return ++one;
}

class MyObject
{
public:
	MyObject(int _data) : data(_data)
	{}

	int get()
	{ return data; }

private:
	int data;
};

int main(int argc, char * argv[])
{
	MyObject a(15);

	cout << incr(a.get()) << endl;

	return 0;
}
