#include <iostream>
#include "stack.hpp"

int NUM = 0;

class with_throw
{
public:
	with_throw operator=(with_throw tmp)
	{
		if (NUM == 6)
		{
			++NUM;
			throw "no copy";
		}
		++NUM;
		return tmp;
	}
	~with_throw(){};

};

int main(void)
{
	std::cout << "Stack<int> with 10 number\n";
	Stack<int> T(10);
	for (int i = 0; i < 10; ++i)
	{	T.push(i);}
	for (int i = 0; i < 11; ++i)
	{
		try
		{	int k = T.pop();
			std::cout << k << " ";}
		catch(std::exception& ex)
		{	std::cout << "\n" << ex.what() << std::endl;}
	}

	std::cout << "\nStack<with_throw>\n";
	Stack<with_throw> tw;
	Stack<with_throw> nw;
	with_throw B;
	tw.push(B);
	tw.push(B);
	tw.push(B);
	nw.push(B);
	nw.push(B);
	std::cout << "first stack: " << tw.count() << "\nsecond stack: " << nw.count() << "\n";
	std::cout << "\noperator= from class with_throw will be call on 6 time and throw exception\n";
	try
	{	nw = tw;}
	catch(...)
	{
		std::cout << "!!It worked!!\n";
	}
	std::cout << "first: " << tw.count() << "\nsecond: " << nw.count() << "\n";
	std::cout << "\nNext case must copy all from 2 stack to 1!\n";
	try
	{	tw = nw;}
	catch(...)
	{
		std::cout << "Don`t call!" << std::endl;//
	}
	std::cout << "first: " << tw.count() << "\nsecond: " << nw.count() << "\n";
	return 0;
}