#include "parse.h"

using namespace std;

void separate(vector<string> &dst,const string &src,char delimiter)
{
	string s;
	for(string::const_iterator it = src.begin();it!=src.end();++it)
	{
		if(*it == delimiter)
		{
			dst.push_back(s);
			s.clear();
		}
		else
		{
			s += *it;
		}
	}
	if(!s.empty())
		dst.push_back(s);
}

void read_file(std::string &s,const std::string &file)
{
	ifstream in(file.c_str());
	if(in){
		stringstream buffer;
		buffer << in.rdbuf();
		s = buffer.str();
	}
}

inline void skip_space(string &s)
{
	string::iterator it;
	for(it = s.begin();it != s.end();++it)
		if(*it != ' ')
			break;
	s.erase(s.begin(),it);
	for(it = s.end()-1;it != s.begin();--it)
		if(*it != ' ')
			break;
	s.erase(it+1,s.end());
}

Parse::Parse():comment("#"),delim(':')
{

}

Parse::Parse(const string &file):comment("#"),delim(':')
{
	parse_file(file);
}
Parse::~Parse()
{

}
void Parse::parse_file(const string &file)
{
	string s;
	read_file(s,file);
	parse_string(s);
}

void Parse::parse_string(const string &s)
{
	m.clear();
	size_t t;
	vector<string> v_src,v_tmp;
	separate(v_src, s,'\n');
	for(vector<string>::iterator it = v_src.begin();it != v_src.end();++it)
	{
		if( (t = it->find(comment)) != string::npos)
		{
			it->erase(it->begin()+t,it->end());
		}
		separate(v_tmp, *it  ,delim);
		if(v_tmp.size() == 2){
			skip_space(v_tmp[0]);
			skip_space(v_tmp[1]);
			insert(v_tmp[0],v_tmp[1]);
		}
		v_tmp.clear();
	}
}


void Parse::show()
{
	for(map<string,string>::iterator it = m.begin();it != m.end();++it)
		cout<<it->first<<" : "<<it->second<<endl;
}

void Parse::show(const string &index)
{
	string s;
	select(s,index);
	if(s.empty())
		cout<<"error index"<<endl;
	else
		cout<<index<<" : "<<s<<endl;
}

void Parse::select(string &dst,const string &index)
{
	for(map<string,string>::iterator it = m.begin();it != m.end();++it)
	{
		if(it->first == index)
		{
			dst = it->second;
			return;
		}
	}
}

void Parse::dump_string(std::string &s)
{
	stringstream buf;
	for(map<string,string>::iterator it = m.begin();it != m.end();++it)
	{
		buf<<it->first<<" : "<<it->second<<'\n';
	}
	s = buf.str();
}


void Parse::dump_file(const std::string &f)
{
	string s;
	dump_string(s);
	ofstream out(f.c_str());
	if(out)
		out<<s;
}

void Parse::erase(const std::string &index)
{
	map<string,string>::iterator it;
	for(it = m.begin();it != m.end();++it)
	{
		if(it->first == index)
		{
			m.erase(it);
			return;
		}
	}
}

void Parse::update(const std::string &index,const std::string &value)
{
	map<string,string>::iterator it;
	for(it = m.begin();it != m.end();++it)
	{
		if(it->first == index)
		{
			it->second = value;
			return;
		}
	}
}

void Parse::clear()
{
	m.clear();
	comment = "#";
	delim = ':';
}



