#include "file.h"

file::file(const char *s = "./"):path(s)
{
    //ctor
}

file::~file()
{
    //dtor
}

void
file::listfile()
{
    l.push_back(path);
    int ret = 1;
    while(ret)
    {
        ret = 0;
        for(list<string>::iterator it = l.begin(); it != l.end(); ++it)
            ret += once_add(it);
    }
}

void
file::show()
{
    for(list<string>::iterator it = l.begin();it != l.end();++it)
        cout<<*it<<endl;
}

int
file::once_add(list<string>::iterator& it)
{
    DIR *pDir;
    struct dirent *ent;
    char name[512];
    pDir = opendir((*it).c_str());
    if(pDir == nullptr) return 0;
    list<string>::iterator tmp = it++;
    while( (ent = readdir(pDir))!= nullptr )
    {
        if(ent->d_type & DT_DIR)
            if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)
                continue;
        memset(name,0,512);
        strcat(name,(*tmp).c_str());
        if(name[strlen(name)-1] !='/')
        {
            strcat(name,"/");
        }
        strcat(name,ent->d_name);
        l.insert(it,name);
    }
    l.erase(tmp);
    --it;
    return 1;
}
