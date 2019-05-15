#include <stdexcept>
#include <memory>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

void CreateFolder(const std::string &name)
{
	shared_ptr<char> tmp(new char[name.size()+1]);
	char *p = NULL;
	size_t len;

	snprintf(tmp.get(), name.size() + 1, "%s", name.c_str());
	len = strlen(tmp.get());
	if (tmp.get()[len - 1] == '/')
		tmp.get()[len - 1] = 0;
	for (p = tmp.get() + 1; *p; p++)
		if (*p == '/') {
			*p = 0;
			if (mkdir(tmp.get(), S_IRWXU | S_IRGRP | S_IROTH))
			{
				if(errno != EEXIST)
					throw runtime_error(string("mkdir fail:") + strerror(errno));
			}
			*p = '/';
		}
	if (mkdir(tmp.get(), S_IRWXU | S_IRGRP | S_IROTH))
	{
		if (errno != EEXIST)
			throw runtime_error(string("mkdir fail:") + strerror(errno));
	}
}

int main()
{
	CreateFolder("test/test");
	return 0;
}