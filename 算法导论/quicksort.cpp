//test.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <assert.h>
#define maxsize 1024
using namespace std;

void exchange(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(int *a, int p, int r)
{
	int x = a[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j)
	{
		if (a[j] <= x)
		{
			exchange(a[++i], a[j]);
		}
	}
	exchange(a[i + 1], a[r]);
	return i + 1;
}

void quicksort(int *a, int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}

int main()
{
	int *x = new int[maxsize];
	memset(x, 0, sizeof(int)*maxsize);
	size_t size = 10;
	for (int i = 0; i < size; ++i) {
		x[i] = rand() % 50;
	}

	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	quicksort(x, 0, 9);
	for (int i = 0; i < size; ++i)
		cout << x[i] << " ";
	cout << endl;
	getchar();
	delete[] x;
	return 0;
}