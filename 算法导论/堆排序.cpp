// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <assert.h>
#define maxsize 1024
using namespace std;

void maxheap(int *a,size_t &size,int i)
{
	int large;
	int l = (i << 1);
	int r = (i << 1) + 1;
	if (l<=size && a[l - 1]>a[i - 1])
		large = l;
	else
		large = i;
	if (r<=size && a[r - 1]>a[large - 1])
		large = r;
	if (large != i)
	{
		a[i - 1] = a[i - 1] ^ a[large - 1];
		a[large - 1] = a[large - 1] ^ a[i - 1];
		a[i - 1] = a[i - 1] ^ a[large - 1];
		maxheap(a, size, large);
	}
}

void buildmaxheap(int *a,size_t &size)
{
	for (int i = size / 2 ; i >= 1; --i)
		maxheap(a, size, i);
}

void heapsort(int *a,size_t &size)
{
	size_t s = size;
	buildmaxheap(a, size);
	for (int i = size; i >= 2; --i)
	{
		a[i - 1] = a[i - 1] ^ a[0];
		a[0] = a[0] ^ a[i - 1];
		a[i - 1] = a[i - 1] ^ a[0];
		maxheap(a, --s, 1);
	}
}

int maximum(int *a, size_t &size)
{
	//buildmaxheap(a, size);
	return a[0];
}

int extractmax(int *a, size_t &size)
{
	if (size < 0)
		return -1;
	int max = a[0];
	a[size - 1] = max;
	size--;
	maxheap(a, size, 1);
	return max;
}

void increasekey(int *a, size_t &size, int i, int k)
{
	if (size < 0)
		return ;
	if (a[i - 1] > k)
		return;
	int tmp;
	a[i - 1] = k;
	while (i > 1 && a[i - 1] > a[(i >> 1) - 1])
	{
		tmp = a[i - 1];
		a[i - 1] = a[(i >> 1) - 1];
		a[(i >> 1) - 1] = tmp;
		i = i >> 1;
	}
}

void insert(int *a, size_t &size, int x)
{
	size++;
	size_t tmp = size - 1;
	a[tmp] = -1;
	increasekey(a, size, tmp + 1, x);
}

int main()
{
	int *x = new int[maxsize];
	memset(x, 0, sizeof(int)*maxsize);
	size_t size = 10;
	for (int i = 0; i < size; ++i)
		x[i] = rand()%50;
	buildmaxheap(x, size);

	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	insert(x, size, 100);
	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	getchar();
	delete[] x;
	return 0;
}