//test.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <assert.h>
#define maxsize 1024
using namespace std;

struct Tree
{
	int x;
	Tree *l;
	Tree *r;
	Tree *p;
};

void inorder_tree_walk(Tree *x)
{
	if (x != NULL)
	{
		
		inorder_tree_walk(x->l);
		cout << x->x << " ";
		inorder_tree_walk(x->r);
	}
}

Tree* tree_search(Tree *x, int k)
{
	while (x != NULL && k != x->x)
	{
		if (k < x->x)
			x = x->l;
		else
			x = x->r;
	}
	return x;
}

Tree* tree_minimum(Tree *x)
{
	while (x->l != NULL)
	{
		x = x->l;
	}
	return x;
}

Tree* tree_maximum(Tree *x)
{
	while (x->r != NULL)
	{
		x = x->r;
	}
	return x;
}

Tree* tree_successor(Tree *x)
{
	if (x->r != NULL)
		return tree_minimum(x->r);
	Tree* y = x->p;
	while (y != NULL || x == y->r)
	{
		x = y;
		y = x->p;
	}
	return y;
}

void tree_insert(Tree *r, int k)
{
	Tree *z = new Tree;
	z->x = k;
	z->p = NULL;
	z->l = NULL;
	z->r = NULL;
	Tree *y = NULL;
	Tree *x = r;
	while (x != NULL)
	{
		y = x;
		if (z->x < x->x)
			x = x->l;
		else
			x = x->r;
	}
	z->p = y;
	if (y == NULL)
		r = z;
	else if (z->x < y->x)
		y->l = z;
	else
		y->r = z;
}

void transplant(Tree *r, Tree *u, Tree *v)
{
	if (u->p == NULL)
		r = u;
	else if (u == u->p->l)
		u->p->l = v;
	else
		u->p->r = v;
	if (v != NULL)
		v->p = u->p;
}

void tree_delete(Tree *r, int k)
{
	Tree *z = tree_search(r, k);
	if (z->l == NULL)
		transplant(r, z, z->r);
	else if (z->r == NULL)
		transplant(r, z, z->l);
	else
	{
		Tree *y = tree_minimum(z->r);
		if (y->p != z)
		{
			transplant(r, y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		transplant(r, z, y);
		y->l = z->l;
		y->l->p = y;
	}
	delete z;
}

int main()
{
	Tree *root = new Tree;
	root->p = NULL;
	root->l = NULL;
	root->r = NULL;
	root->x = 7;
	int a[9] = {1,4,3,9,2,11,32,5,10};
	for (int i = 0; i < 9; ++i)
		tree_insert(root, a[i]);
	inorder_tree_walk(root);
	cout << endl;
	tree_delete(root, 4);
	inorder_tree_walk(root);
	cout << endl;
	Tree *tmp = tree_successor(root);
	cout << tmp->x << endl;
	getchar();
	return 0;
}