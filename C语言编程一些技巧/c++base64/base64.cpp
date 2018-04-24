// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

static const string base64_dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
									"abcdefghijklmnopqrstuvwxyz"  
									"0123456789+/";

string base64_encode(const vector<unsigned char> &v)
{
	string ret;
	unsigned char byte[3], base[4];
	int i,size = v.size() / 3;
	int pad = v.size() % 3;
	for (i = 1; i <= size; ++i)
	{
		for (int j = 0; j < 3; ++j)
			byte[j] = v[(i - 1) * 3 + j];
		base[0] = byte[0] >> 2;
		base[1] = ((byte[0] << 4) & 0x30) | ((byte[1] >> 4) & 0x0F);
		base[2] = ((byte[1] << 2) & 0x3C) | ((byte[2] >> 6) & 0x03);
		base[3] = byte[2] & 0x3F;
		for (int j = 0; j < 4; ++j)
			ret += base64_dictionary[base[j]];
		if (i % 19 == 0)
			ret += "\r\n";
	}
	if (pad)
	{
		memset(byte, 0, sizeof(byte));
		for (int j = 0; j < pad; ++j)
			byte[j] = v[(i - 1) * 3 + j];
		base[0] = byte[0] >> 2;
		base[1] = ((byte[0] << 4) & 0x30) | ((byte[1] >> 4) & 0x0F);
		base[2] = ((byte[1] << 2) & 0x3C) | ((byte[2] >> 6) & 0x03);
		base[3] = byte[2] & 0x3F;
		for (int j = 0; j < pad + 1; ++j)
			ret += base64_dictionary[base[j]];
		for (int j = 0; j < 3 - pad; ++j)
			ret += '=';
	}
	return ret;
}

inline unsigned char reversemap(unsigned char b)
{
	return base64_dictionary.find(b);
}

inline void erase_enter(string &v)
{
	int begin = 0;
	begin = v.find("\r\n", begin);  //���ҿո���str�е�һ�γ��ֵ�λ��
	while (begin != -1)  //��ʾ�ַ����д��ڿո�
	{
		v.replace(begin, 2, "");  // �ÿմ��滻str�д�begin��ʼ��1���ַ�
		begin = v.find("\r\n", begin);  //���ҿո����滻���str�е�һ�γ��ֵ�λ��
	}
}

vector<unsigned char> base64_decode(string v)
{
	erase_enter(v);
	vector<unsigned char> ret;
	unsigned char byte[3], base[4];
	int i, c = 0, size = v.size() / 4;
	for (i = 0; i < size - 1 ; ++i)
	{
		for (int j = 0; j < 4; ++j)
			base[j] = v[i * 4 + j];
		byte[0] = reversemap(base[0]) << 2 | reversemap(base[1]) >> 4;
		byte[1] = reversemap(base[1]) << 4 | reversemap(base[2]) >> 2;
		byte[2] = reversemap(base[2]) << 6 | reversemap(base[3]);
		for (int j = 0; j < 3; ++j)
			ret.push_back(byte[j]);
	}
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		if (*it != '=')
			break;
		else
			++c;
	}
	for (int j = 0; j < 4; ++j)
		base[j] = v[i * 4 + j];
	byte[0] = reversemap(base[0]) << 2 | reversemap(base[1]) >> 4;
	byte[1] = reversemap(base[1]) << 4 | reversemap(base[2]) >> 2;
	byte[2] = reversemap(base[2]) << 6 | reversemap(base[3]);
	c = c > 2 ? 2 : c;
	for (int j = 0; j < 3 - c; ++j)
		ret.push_back(byte[j]);
	return ret;
}

int main()
{
	const string s = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	vector<unsigned char> v;
	for (auto &i : s)
		v.push_back(i);
	string encode = base64_encode(v);
	cout << encode << endl;
	v.clear();
	v = base64_decode(encode);
	for (auto &i : v)
		cout << i;
	cout << endl;
	getchar();
    return 0;
}

