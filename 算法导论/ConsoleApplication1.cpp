//test.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <assert.h>
#define maxsize 1024
#define red 0
#define black 1

using namespace std;


struct Tree
{
	char name[32];
	int k = 0;
	Tree *p = NULL;
	Tree *l = NULL;
	Tree *r = NULL;
	char color = red;
	bool none = false;
};

void inorder_tree_walk(Tree *r)
{
	if (r != NULL)
	{
		inorder_tree_walk(r->l);
		cout << "key = " << r->k << "\tname = " << r->name << endl;
		inorder_tree_walk(r->r);
	}
}

Tree* tree_maximium(Tree *r)
{
	while (r->r)
		r = r->r;
	return r;
}

Tree* tree_minimium(Tree *r)
{
	while (r->l)
		r = r->l;
	return r;
}

Tree* tree_successor(Tree *r)
{
	if (r->r)
		return tree_minimium(r->r);
	Tree *y = r;
	while (y->p && y == y->p->r)
		y = y->p;
	return y;
}

Tree* tree_search(Tree *r, int k)
{
	while (r)
	{
		if (k == r->k)
			break;
		if (k < r->k)
			r = r->l;
		else
			r = r->r;
	}
	return r;
}

static void left_rotation(Tree **r, Tree *x)
{
	Tree *y = x->r;
	if (y == NULL)return;
	x->r = y->l;
	if (y->l)y->l->p = x;
	y->p = x->p;
	if (x->p == NULL)
		*r = y;
	else if (x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	x->p = y;
	y->l = x;
}

static void right_rotation(Tree **r, Tree *y)
{
	Tree *x = y->l;
	if (x == NULL)return;
	y->l = x->r;
	if (x->r)x->r->p = y;
	x->p = y->p;
	if (y->p == NULL)
		*r = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;
	y->p = x;
	x->r = y;
}

static void rb_insert_fixup(Tree *r, Tree *z)
{
	Tree *y = NULL;
	while (z->p && z->p->color == red)
	{
		if (z->p == z->p->l)
		{

		}
		else
		{

		}
	}
}

Tree* rb_tree_insert(Tree *r, Tree *z)
{
	if (z == NULL)return r;
	if (r == NULL)
	{
		r = z;
		return r;
	}
	Tree *y = r;
	Tree *x = NULL;
	while (y)
	{
		x = y;
		if (z->k < y->k)
			y = y->l;
		else
			y = y->r;
	}
	if (z->k < x->k)
		x->l = z;
	else
		x->r = z;
	z->p = x;
	z->color = red;
	rb_insert_fixup(r, z);
	while (r->p)
		r = r->p;
	return r;
}

//移植z节点到y节点，z的子节点由其本身维护,如果y是根节点则把r置为z
static void transplant(Tree **r, Tree *y, Tree *z)
{
	if (y->p == NULL)
		*r = z;
	else if (y == y->p->r)
		y->p->r = z;
	else
		y->p->l = z;
	if (z != NULL)
		z->p = y->p;
}

void add(Tree **r, int k, char *name)
{
	Tree *p = new Tree;
	p->k = k;
	strcpy(p->name, name);
	*r = rb_tree_insert(*r, p);
}