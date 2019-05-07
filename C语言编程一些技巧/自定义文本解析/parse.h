#ifndef PARSE_H_
#define PARSE_H_


#include <string>
#include <map>



class Parse {
	public:
		Parse(std::string commentsign = "#",char delimitersign = ':'):comment(commentsign),delim(delimitersign){}
		Parse(const std::string &filename,std::string commentsign = "#",char delimitersign = ':'):
			comment(commentsign),delim(delimitersign){parse_file(filename);}
		~Parse(){}

		void parse_file(const std::string &);
		void parse_string(const std::string &);
		void dump2string(std::string &);
		void dump2file(const std::string &);
		void show();
		std::string select(const std::string &index);
		void select(std::string &dst,const std::string &index);
		void erase(const std::string &);
		void update(const std::string &,const std::string &);
		void clear();
		void insert(const std::string &s1,const std::string &s2){m.insert(m.begin(),std::pair<std::string,std::string>(s1,s2));}

	private:
		std::map<std::string, std::string> m;
		std::string comment;
		char delim;
};

#endif /* PARSE_H_ */


