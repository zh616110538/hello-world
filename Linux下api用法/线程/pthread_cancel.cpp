#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *fun(void *arg)
{
    while(1){
        cout<<"test"<<endl;
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    void *tret;
    pthread_create(&tid,NULL,fun,NULL);
    sleep(5);
    pthread_cancel(tid);
    pthread_join(tid,&tret);
    return 0;
}
