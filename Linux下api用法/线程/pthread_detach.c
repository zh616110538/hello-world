#include <stdio.h>
#include <string.h>
#include <pthread.h>
void my111(void *arg)
{
	printf("123124\n");
}

int main ()
{
	void *tret;
    pthread_t       tid;
    pthread_attr_t  attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, (void *)my111, NULL);
    printf("%d\n",pthread_join(tid,&tret));
	return 0;
}
