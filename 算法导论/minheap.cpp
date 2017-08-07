// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <assert.h>
#define index(x) ((x)-1)
#define maxsize 1024
using namespace std;

void exchange(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void minheap(int *a,const size_t &size, int i)
{
	int l = i * 2;
	int r = i * 2 + 1;
	int little;
	if (index(l) < size && a[index(l)] < a[index(i)])
		little = l;
	else
		little = i;
	if (index(r) < size && a[index(r)] < a[index(little)])
		little = r;
	if (little != i)
	{
		exchange(a[index(little)], a[index(i)]);
		minheap(a, size, little);
	}
}

void buildminheap(int *a,const size_t &size)
{
	for (int i = size / 2; i >= 1; --i)
		minheap(a, size, i);
}

void heapsort(int *a,const size_t &size)
{
	int tmp = size;
	buildminheap(a, size);
	for (int i = size; i >= 2; --i)
	{
		exchange(a[index(1)], a[index(i)]);
		minheap(a, --tmp, 1);
	}
}
//以下操作只针对已经进行过buildminheap的数组
int minimum(int *a,const size_t &size)
{
	return a[index(1)];
}

int extractmin(int *a, size_t &size)
{
	int min = a[index(1)];
	a[index(size)] = min;
	size--;
	minheap(a, size, 1);
	return min;
}

void increasekey(int *a, size_t &size, int i, int k)
{
	if (a[index(i)] < k)
		return;
	a[index(i)] = k;
	while (i >= 1 && a[index(i)] < a[index(i / 2)])
	{
		exchange(a[index(i)], a[index(i / 2)]);
		i /= 2;
	}
}

void insert(int *a, size_t &size, int x)
{
	size++;
	a[index(size)] = INT_MAX;
	increasekey(a, size, size, x);
}

int main()
{
	int *x = new int[maxsize];
	memset(x, 0, sizeof(int)*maxsize);
	size_t size = 10;
	for (int i = 0; i < size; ++i)
		x[i] = rand() % 50;
	buildminheap(x, size);

	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	insert(x, size, 5);
	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	getchar();
	delete[] x;
	return 0;
}