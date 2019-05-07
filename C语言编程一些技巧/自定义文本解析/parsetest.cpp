#include "parse.h"
#include <iostream>

using namespace std;

int main()
{
	string s = "sign:I am the bone of my sword. Steel is my body, Fire is my blood. I have created over a thousand blades. Unknown to life, nor known to death. Have withstood pain to create many weapons. Yet those hands will never hold anything. So as I pray, Unlimited Blade Works!\nsign_kill_all:Judgement Knight of thunder\nlo_addr:127.0.0.1\nlua_launch_port:8888\nserver_port:5000";
	Parse p;
	p.parse_string(s);
	p.show();
	return 0;
}
