#ifndef FILE_H
#define FILE_H

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <list>
#include <stdio.h>
using namespace std;

class file
{
public:
    file(const char *);
    virtual ~file();
    void listfile();
    void show();
protected:

private:
    string path;
    list<string> l;
    int once_add(list<string>::iterator&);
};

#endif // FILE_H
