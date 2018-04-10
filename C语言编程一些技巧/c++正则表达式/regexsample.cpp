//test.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include "transform.h"
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

string options[] = { "-m","-h","-k","-d","-r" };

void error()
{
	cout << "error parameters ,see help" << endl;
	exit(0);
}

void help()
{
	cout << "****************************************************************" << endl
		<< "*\tusage: $execute [options] inputfile outputfile         *" << endl
		<< "*\toptions : -d 转换为达野格式                            *" << endl
		<< "*\t          -k 转换为keba格式                            *" << endl
		<< "*\t          -m 生成sps模板                               *" << endl
		<< "*\t          -r A2，A3正负转换                            *" << endl
		<< "*\t          -h 帮助                                      *" << endl
		<< "*\t                                                       *" << endl
		<< "*\tExamples:                                              *" << endl
		<< "*\ttransform.exe -d pionts08_daye.txt newProgram.dat      *" << endl
		<< "*\ttransform.exe -k newProgram.dat pionts08_daye.txt      *" << endl
		<< "*\ttransform.exe -r pionts08_daye1.txt pionts08_daye2.txt *" << endl
		<< "*\ttransform.exe -m                                       *" << endl
		<< "****************************************************************" << endl;
}

bool compare(line a, line b)
{
	return a.l < b.l;
}

void keba_to_daye(string src, string dst)
{
	ifstream in(src);
	if (!in) {
		cout << "bad filename" << endl;
		return ;
	}
	ofstream out(dst, ios::trunc);
	if(!out){
		cout << "bad filename" << endl;
		return;
	}
	string tmp;
	regex e("a(\\d):=([-.\\d]+)");
	regex space("\\s+");
	smatch r;
	int i = 0;
	string axis[6];
	stringstream ss;
	while (getline(in, tmp)) {
		++i;
		for (auto &i : axis)
			i = "0";
		tmp = regex_replace(tmp, space, "");
		while (regex_search(tmp, r, e)) {
			if (r[1] == '1')
				axis[0] = r[2];
			else if (r[1] == '2')
				axis[1] = r[2];
			else if (r[1] == '3')
				axis[2] = r[2];
			else if (r[1] == '4')
				axis[3] = r[2];
			else if (r[1] == '5')
				axis[4] = r[2];
			else if (r[1] == '6')
				axis[5] = r[2];
			tmp = r.suffix().str();
		}

		ss << "p" << i << " = { 2 , 0 , 0 , 0 , 0 , 0 , 0 , " << axis[0] << " , " << axis[1] << " , " << axis[2] << " , " << axis[3] << " , " << axis[4] << " , " << axis[5] << " , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,  0,  0,  0,  0,  0 }\n";
		out << ss.str();
		ss.str("");
	}
	in.close();
	out.close();
}

void daye_to_keba(string src, string dst)
{
	ifstream in(src);
	if (!in) {
		cout << "bad filename" << endl;
		return;
	}
	
	ofstream out(dst, ios::trunc);
	if (!out) {
		cout << "bad filename" << endl;
		return;
	}
	line l;
	vector<line> v1;
	string tmp;
	smatch r;
	//regex e("\\{[-.\\d]+,[-.\\d]+,[-.\\d]+,[-.\\d]+,[-.\\d]+,[-.\\d]+,[-.\\d]+,");
	regex e("\\{([-.\\d]+,){7}");
	regex e_axis("([-.\\d]+)");
	regex space("\\s+");
	regex point("[pP](\\d+)=\\{.+\\}");
	int i = 0;
	string count;
	stringstream ss;
	while (getline(in, tmp)) {
		tmp = regex_replace(tmp, space, "");
		regex_search(tmp, r, point);
		if (r.empty())
			continue;
		count = r[1];
		i = atoi(count.c_str()) - 1;
		
		ss << "ap" << i << " : AXISPOS := (";
		regex_search(tmp, r, e);
		tmp = r.suffix().str();
		for (int i = 0; i < 6; ++i)
		{
			regex_search(tmp, r, e_axis);
			//if (r[1] != '0')
			//{
				ss << "a" << i + 1 << " := " << r[1];
				if (i != 5)
					ss << ", ";
			//}
			if (i == 5) {
				ss << ")\n";
				break;
			}
			tmp = r.suffix().str();
		}
		l.l = i;
		l.s = ss.str();
		v1.push_back(l);
		//out << ss.str();
		ss.str("");
	}
	sort(v1.begin(), v1.end(),compare);
	for (auto it = v1.begin(); it != v1.end();++it) {
		if (it + 1 != v1.end())
			if (it->l == (it + 1)->l)
				continue;
		out << it->s;
	}
	in.close();
	out.close();
}

void keba_reverse(string src,string dst)
{
	ifstream in(src);
	if (!in) {
		cout << "bad filename" << endl;
		return;
	}
	ofstream out(dst, ios::trunc);
	if (!out) {
		cout << "bad filename" << endl;
		return;
	}

	string tmp;
	regex a2("a2");
	regex a3("a3");
	regex e2("a2 := (-)[.\\d]+");
	regex e3("a3 := (-)[.\\d]+");
	regex c2_true("(a2 := )-([.\\d]+)");
	regex c2_false("(a2 := )([.\\d]+)");
	regex c3_true("(a3 := )-([.\\d]+)");
	regex c3_false("(a3 := )([.\\d]+)");
	smatch r;
	string axis[6];
	stringstream ss;
	while (getline(in, tmp)) {
		if (regex_search(tmp, r, a2)) {
			if (regex_search(tmp, r, e2))
				tmp = regex_replace(tmp, c2_true, "$1$2");
			else
				tmp = regex_replace(tmp, c2_false, "$1-$2");
		}
		if (regex_search(tmp, r, a3)) {
			if (regex_search(tmp, r, e3))
				tmp = regex_replace(tmp, c3_true, "$1$2");
			else
				tmp = regex_replace(tmp, c3_false, "$1-$2");
		}
		out << tmp << "\n";
		ss.str("");
	}
	in.close();
	out.close();
}

void sps_generate()
{
	ofstream out(".parallel.prg",ios::trunc);
	if (!out)
		return;
	out << "//This is a parallel program template!\n";
	for (int i = 1; i <= 32; ++i)
	{
		out << "IF FLAG[" << i << "] = TRUE THEN\n"
			<< "//Write your code here\n"
			<< "\n"
			<< "END_IF\n";
	}
}

int main(int argc,char *argv[])
{
	if (argc < 2)
	{
		help();
		return 0;
	}
	if (argc == 2)
	{
		if (argv[1] == options[0])
		{
			sps_generate();
			return 0;
		}
		else if (argv[1] == options[1])
		{
			help();
			return 0;
		}
		else
		{
			error();
		}
	}
	string src, dst;
	if (argc == 4)
	{
		src = argv[2];
		dst = argv[3];
		if (argv[1] == options[2])
		{
			daye_to_keba(src, dst);
			return 0;
		}
		else if (argv[1] == options[3])
		{
			
			keba_to_daye(src, dst);
			return 0;
		}
		else if (argv[1] == options[4])
		{
			keba_reverse(src, dst);
			return 0;
		}
		else
		{
			error();
		}
	}
	error();
	return 0;
}

//int main()
//{
//	string tmp("ap0 : AXISPOS := (a1 := 20.356, a2 := -43.2154, a3 := -41.9908, a4 := 14.2721, a5 := -92.9629, a6 := 226.376)");
//	regex e("a(\\d):=([-.\\d]+)");
//	regex space("\\s+");
//	smatch r;
//	int i = 0;
//	string axis[6];
//	stringstream ss;
//	tmp = regex_replace(tmp, space, "");
//	while (regex_search(tmp, r, e)) {
//		if (r[1] == '1')
//			axis[0] = r[2];
//		else if (r[1] == '2')
//			axis[1] = r[2];
//		else if (r[1] == '3')
//			axis[2] = r[2];
//		else if (r[1] == '4')
//			axis[3] = r[2];
//		else if (r[1] == '5')
//			axis[4] = r[2];
//		else if (r[1] == '6')
//			axis[5] = r[2];
//		tmp = r.suffix().str();
//		
//	}
//	cout << axis[2] << " " << axis[3] << endl;
//	e = "-";
//	cout << regex_search(axis[2], e) << endl;
//	cout << regex_search(axis[3], e) << endl;
//	getchar();
//}
// ^(INFO)\\((.+)\\)$