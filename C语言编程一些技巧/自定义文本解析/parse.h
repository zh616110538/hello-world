#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

void separate(std::vector<std::string> &dst, const std::string &src,
		char delimiter);
void read_file(std::string &dst, const std::string &file);

class Parse {
	public:
		Parse();
		Parse(const std::string &);
		~Parse();

		void parse_file(const std::string &);
		void parse_string(const std::string &);
		void dump_string(std::string &);
		void dump_file(const std::string &);
		void show();
		void show(const std::string &);
		void select(std::string &,const std::string &);
		void erase(const std::string &);
		void update(const std::string &,const std::string &);
		inline void insert(const std::string &s1,const std::string &s2){m.insert(m.begin(),std::pair<std::string,std::string>(s1,s2));}


	private:
		std::map<std::string, std::string> m;
		std::string comment;
		char delim;
};

#endif /* PARSE_H_ */


