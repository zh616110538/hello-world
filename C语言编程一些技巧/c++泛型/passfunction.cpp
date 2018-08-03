// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <exception>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <stack>

using namespace std;

template<typename Fn,typename ... Args>
void mycall(Fn && f,Args&& ... args)
{
	//f(std::forward<Args>(args)...);
	bind(forward<Fn>(f), std::forward<Args>(args)...)();
}

class X
{
private:
	void init()
	{
		cout << "In init" << endl;
	}
public:
	void f1()
	{
		mycall(&X::init,this);
	}
};

void test(int i)
{
	cout << i<< endl;
}

int main()
{
	mycall(test, 1);
	X x;
	x.f1();
	getchar();
	return 0;
}