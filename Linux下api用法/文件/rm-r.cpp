#include <stdexcept>
#include <string>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <functional>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void DeleteFolder(const std::string &name)
{
	static function<void(const string&)> rmr = [&](const string &name) {
		DIR* dir = opendir(name.c_str());
		if (dir == NULL)
			throw runtime_error(string("opendir fail:") + strerror(errno));
		struct dirent* ent;
		string buf;
		while ((ent = readdir(dir)))
		{
			if (ent->d_type == DT_DIR)
			{
				if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
					continue;
				buf = name + "/" + ent->d_name;
				rmr(buf);
			}
			if (ent->d_type == DT_REG)
			{
				buf = name + "/" + ent->d_name;
				if (remove(buf.c_str()) != 0)
					throw runtime_error(string("remove fail:") + strerror(errno));
			}
		}
		if (rmdir(name.c_str()) != 0)
			throw runtime_error(string("rmdir fail:") + strerror(errno));
	};
	struct stat buf;
	if (lstat(name.c_str(), &buf) < 0)
		throw runtime_error(string("lstat fail:") + strerror(errno));
	if (S_ISDIR(buf.st_mode))
		rmr(name);
	else
		if (remove(name.c_str()) != 0)
			throw runtime_error(string("remove fail:") + strerror(errno));
}

int main()
{
	DeleteFolder("test");
	return 0;
}