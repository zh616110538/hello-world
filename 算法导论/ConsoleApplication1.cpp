// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
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
		cout << "key = " << r->k << " \tname = " << r->name << " \tcolor = " << (int)r->color << endl;
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
		if (z->p->p == NULL)break;
		if (z->p == z->p->p->l)
		{
			y = z->p->p->r;
			//情况1，父节点为红色，叔节点也为红色，将父节点和叔节点都置为黑色，祖父节点置为红色，将z的祖父置为新的z
			if (y && y->color == red)
			{
				z->p->color = black;
				y->color = black;
				z->p->p->color = red;
				z = z->p->p;
			}
			else
			{
				//情况2，父节点为红色，叔节点为黑色，z为父节点的右孩子，将父节点置为新的z，左旋z，进而转换为情况3
				if (z == z->p->r)
				{
					z = z->p;
					left_rotation(&r, z);
				}
				//情况3，父节点为红色，叔节点为黑色，将父节点置为黑色，祖父节点置为红色，右旋祖父节点
				z->p->color = black;
				z->p->p->color = red;
				right_rotation(&r, z->p->p);
			}
		}
		else
		{
			y = z->p->p->l;
			if (y && y->color == red)
			{
				z->p->color = black;
				y->color = black;
				z->p->p->color = red;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->l)
				{
					z = z->p;
					right_rotation(&r, z);
				}
				z->p->color = black;
				z->p->p->color = red;
				left_rotation(&r, z->p->p);
			}
		}
	}
	r->color = black;
}

Tree* rb_tree_insert(Tree *r, Tree *z)
{
	if (z == NULL)return r;
	if (r == NULL)
	{
		r = z;
		r->color = black;
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

static void rb_delete_fixup(Tree *r, Tree *x)
{
	Tree *w = NULL;
	while (x != r && x->color == black || x->none)
	{
		if (x == x->p->l)
		{
			w = x->p->r;
			if (w == NULL)break;
			//情况1，z的兄弟节点w是红色的，将w变为黑色，x的父节点置为红色，对x的父节点左旋,将x的兄弟节点置为新的w，由此转换为情况二
			if (w->color == red)
			{
				w->color = black;
				x->p->color = red;
				left_rotation(&r, x->p);
				w = x->p->r;
			}
			//情况2，w的两个子节点都为红色,将x置为红色，x上移一位，进入下一次循环
			if ((w->l == NULL || w->l->color == black) && (w->r == NULL || w->r->color == black))
			{
				w->color = red;
				x = x->p;
			}
			else
			{
				//情况3，w为黑色，w的左孩子为红色，w的右孩子是黑色，将w的左孩子置为黑色，w置为红色，右旋w,将x的新兄弟置为w
				if (w->r == NULL || w->r->color == black)
				{
					w->l->color = black;
					w->color = red;
					right_rotation(&r, w);
					w = x->p->r;
				}
				//情况4，w为黑色，w的右孩子是红色，将w的颜色置为x父节点的颜色，x父节点置为黑，w的右孩子置为黑，对x父节点左旋,终止循环
				w->color = x->p->color;
				x->p->color = black;
				w->r->color = black;
				left_rotation(&r, x->p);
				x = r;
			}
		}
		else
		{
			w = x->p->l;
			if (w == NULL)break;
			if (w->color == red)
			{
				w->color = black;
				x->p->color = red;
				right_rotation(&r, x->p);
				w = x->p->l;
			}
			if ((w->l == NULL || w->l->color == black) && (w->r == NULL || w->r->color == black))
			{
				w->color = red;
				x = x->p;
			}
			else
			{
				if (w->l == NULL || w->l->color == black)
				{
					w->r->color = black;
					w->color = red;
					left_rotation(&r, w);
					w = x->p->l;
				}
				w->color = x->p->color;
				x->p->color = black;
				w->l->color = black;
				right_rotation(&r, x->p);
				x = r;
			}
		}
	}
	x->color = black;
}

Tree* rb_tree_delete(Tree *r, int k)
{
	Tree *z = tree_search(r, k);
	if (z == NULL)return z;
	Tree *y = z;
	Tree *x = NULL;
	char original_color = y->color;
	if (z->l == NULL)
	{
		x = z->r;
		if (x == NULL)
		{
			x = new Tree;
			x->l = x->r = NULL;
			x->none = true;
			x->color = black;
			x->p = z->p;
		}
		transplant(&r, z, z->r);
	}
	else if (z->r == NULL)
	{
		x = z->l;
		if (x == NULL)
		{
			x = new Tree;
			x->l = x->r = NULL;
			x->none = true;
			x->color = black;
			x->p = z->p;
		}
		transplant(&r, z, z->l);
	}
	else
	{
		y = tree_minimium(z->r);
		original_color = y->color;
		x = y->r;
		if (x == NULL)
		{
			x = new Tree;
			x->l = x->r = NULL;
			x->none = true;
			x->color = black;
			x->p = z->p;
		}
		if (y != z->r)
		{
			transplant(&r, y, y->r);
			y->r = z->r;
			z->r->p = y;
		}
		transplant(&r, z, y);
		y->color = z->color;
	}
	delete z;
	if (original_color == black)
		rb_delete_fixup(r, x);
	if (x->none)delete x;
	while (r->p)
		r = r->p;
	return r;
}

void add(Tree **r, int k, char *name)
{
	Tree *p = new Tree;
	p->k = k;
	strcpy_s(p->name, name);
	*r = rb_tree_insert(*r, p);
}

void random_charactor(char *s, int num)
{
	for (int i = 0; i < num - 1; ++i)
		s[i] = rand() % 26 + 'a';
	s[num - 1] = '\0';
}

int main()
{
	srand((unsigned)time(NULL));
	char s[32];
	Tree *r = NULL;
	int x[] = { 26,17,41,14,21,30,47,10,16,19,23,28,38,7,12,15,20,35,39,3 };
	for (int i = 0; i<sizeof(x) / 4; ++i) {
		random_charactor(s, 32);
		add(&r, x[i], s);
	}
	inorder_tree_walk(r);
	cout << "****************************" << endl;
	rb_tree_delete(r, 47);
	inorder_tree_walk(r);
	getchar();
}
