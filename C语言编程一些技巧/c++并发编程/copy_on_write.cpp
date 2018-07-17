// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<vector>
#include<assert.h>
using namespace std;
mutex m;
shared_ptr<vector<int>> ptr;
int loop = 100;
void read() {//读者
	while (1) {
		{//放在块内可以使临时对象得到及时析构
			shared_ptr<vector<int>> temp_ptr;
			{
				unique_lock<mutex> lk(m);//这里读者和读者之间，读者和写者之间都互斥，但是临界区很小所以不用担心读者和读者间的互斥
				temp_ptr = ptr;//这里会使对象的引用计数加1
				assert(!temp_ptr.unique());
			}
			for (auto it = temp_ptr->begin(); it != temp_ptr->end(); it++)//如果存在写者，那么读者访问的是旧的vector
				//cout << *it << " ";
				;
		}
	}
}
void write() {//写者
	for (int i = 0;i<loop; i++) {
		{//在一个块内使临时对象及时得到析构
			unique_lock<mutex> lk(m);//写者和写者之间，写者和读者之间都要互斥
			if (!ptr.unique())//如果存在其它写者或读者，则需要拷贝当前的vector
				ptr.reset(new vector<int>(*ptr));
			assert(ptr.unique());
			ptr->push_back(i);
		}
	}
}
int main() {
	ptr.reset(new vector<int>);
	thread one(read);
	thread two(read);
	write();
	one.join();
	two.join();
	getchar();
	return 0;
}
