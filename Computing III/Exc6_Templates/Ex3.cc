//**                                 **//
//                                     //
// PROGRAM NAME: Ex3.cc                //
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

template<typename T>
class MyObject2
{
public:
	MyObject2(T _data = 0) : data(_data) 
	{}

	T get()
	{ return data; }

private:
	T data;
};

int main(int argc, char * argv[])
{
	MyObject2<double> a(15.5);

	cout << incr(a.get()) << endl;

	return 0;
}
