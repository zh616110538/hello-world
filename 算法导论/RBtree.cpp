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
	Tree *l = NULL;
	Tree *r = NULL;
	Tree *p = NULL;
	bool black;
	bool isnone = false;
};

void inorder_tree_walk(Tree *x)
{
	if (x != NULL)
	{
		
		inorder_tree_walk(x->l);
		cout << x->x << " " << x->black << endl;
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

void left_rotation(Tree **r, Tree *x)
{
	
	Tree *y = x->r;
	if (y == NULL)
		return;
	x->r = y->l;
	if (y->l != NULL) 
		y->l->p = x;
	y->p = x->p;
	if (x->p == NULL)
		*r = y;
	else if (x->p->l == x)
		x->p->l = y;
	else
		x->p->r = y;
	y->l = x;
	x->p = y;
	while ((*r)->p)
		(*r) = (*r)->p;
}

void right_rotation(Tree **r, Tree *y)
{

	Tree *x = y->l;
	if (x == NULL)
		return;
	y->l = x->r;
	if (x->r != NULL)
		x->r->p = y;
	x->p = y->p;
	if (y->p == NULL)
		*r = y;
	else if (y->p->l == y)
		y->p->l = x;
	else
		y->p->r = x;
	x->r = y;
	y->p = x;
	while ((*r)->p)
		(*r) = (*r)->p;
}

void rb_insert_fix(Tree *r, Tree *z)
{
	Tree *y;
	while (z->p && z->p->p && z->p->black == false)
	{
		if (z->p == z->p->p->l) 
		{
			y = z->p->p->r;
			if (y && y->black == false)
			{
				z->p->black = true;
				y->black = true;
				z->p->p->black = false;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->r)
				{
					z = z->p;
					left_rotation(&r, z);
				}
				z->p->black = true;
				z->p->p->black = false;
				right_rotation(&r, z->p->p);
			}
		}
		else
		{
			y = z->p->p->l;
			if (y && y->black == false)
			{
				z->p->black = true;
				y->black = true;
				z->p->p->black = false;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->l)
				{
					z = z->p;
					right_rotation(&r, z);
				}
				z->p->black = true;
				z->p->p->black = false;
				left_rotation(&r, z->p->p);
			}
		}
	}
	//while (r->p)
	//	r = r->p;
	r->black = true;
}

Tree* tree_insert(Tree *r, int k)
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
	z->black = false;
	rb_insert_fix(r, z);
	while (r->p)
		r = r->p;
	return r;
}



void transplant(Tree **r, Tree *u, Tree *v)
{
	if (u->p == NULL)
		*r = v;
	else if (u == u->p->l)
		u->p->l = v;
	else
		u->p->r = v;
	if (v != NULL)
		v->p = u->p;
}

void rb_delete_fix(Tree *r, Tree *x)
{
	Tree *w = NULL;
	while (x && x != r && (x->black == true || x->isnone == true))
	{
		if (x == x->p->l)
		{
			w = x->p->r;
			if (w && w->black == false)
			{
				w->black = true;
				x->p->black = false;
				left_rotation(&r, x->p);
				w = x->p->r;
			}
			if (w == NULL)return;
			if ((w->l == NULL || w->l->black == true) && (w->r == NULL || w->r->black == true))
			{
				w->black = false;
				x = x->p;
			}
			else
			{
				if (w->r == NULL || w->r->black == true)
				{
					w->l->black = false;
					w->black = true;
					right_rotation(&r, w);
					w = x->p->r;
				}
				w->black = x->p->black;
				x->p->black = true;
				w->r->black = true;
				left_rotation(&r, x->p);
				x = r;
			}
		}
		else 
		{
			w = x->p->l;
			if (w && w->black == false)
			{
				w->black = true;
				x->p->black = false;
				right_rotation(&r, x->p);
				w = x->p->l;
			}
			if (w == NULL)return;
			if ((w->l == NULL || w->l->black == true) && (w->r == NULL || w->r->black == true))
			{
				w->black = false;
				x = x->p;
			}
			else
			{
				if (w->l == NULL || w->l->black == true)
				{
					w->r->black = false;
					w->black = true;
					left_rotation(&r, w);
					w = x->p->l;
				}
				w->black = x->p->black;
				x->p->black = true;
				w->l->black = true;
				right_rotation(&r, x->p);
				x = r;
			}
		}
	}
	x->black = true;
}

Tree * tree_delete(Tree *r, int k)
{
	Tree *z = tree_search(r, k);
	Tree *y = z;
	Tree *x = NULL;
	bool black = y->black;
	if (z->l == NULL) {
		x = z->r;
		if (x == NULL)
		{
			x = new Tree;
			x->p = z->p;
			x->l = x->r = NULL;
			x->isnone = true;
		}
		transplant(&r, z, z->r);
	}
	else if (z->r == NULL) {
		x = z->l;
		if (x == NULL)
		{
			x = new Tree;
			x->p = z->p;
			x->l = x->r = NULL;
			x->isnone = true;
		}
		transplant(&r, z, z->l);
	}
	else
	{
		Tree *y = tree_minimum(z->r);
		black = y->black;
		x = y->r;
		if (x == NULL)
		{
			x = new Tree;
			x->l = x->r = NULL;
			x->p = y;
			x->isnone = true;
		}
		if (y->p != z)
		{
			transplant(&r, y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		transplant(&r, z, y);
		y->l = z->l;
		y->l->p = y;
		y->black = z->black;
	}
	delete z;
	if (black)
		rb_delete_fix(r, x);
	if (x->isnone == true)delete x;
	return r;
	
}

int main()
{
	Tree *root = new Tree;
	root->p = NULL;
	root->l = NULL;
	root->r = NULL;
	root->x = 26;
	root->black = true;
	int a[] = {17,41,14,21,30,47,10,16,19,23,28,38,7,12,15,20,35,39,3};
	for (int i = 0; i < sizeof(a)/4; ++i) {
		root = tree_insert(root, a[i]);
	}
	while (root->p)
		root = root->p;
	inorder_tree_walk(root);
	cout << endl;
	root = tree_delete(root, 47);
	while (root->p)
		root = root->p;
	inorder_tree_walk(root);
	cout << endl;
	getchar();
	return 0;
}
