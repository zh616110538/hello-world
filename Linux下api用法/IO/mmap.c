#include <sys/mman.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/stat.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  

int main(int argc,char *argv[])
{
	struct stat stat;
	int fd1,fd2;
	char *p1,*p2;
	if(argc != 3)
		fprintf(stderr,"error para\n");
	fd1 = open(argv[1],O_RDWR);
	fd2 = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd1 < 0 || fd2 < 0)
		fprintf(stderr,"open file error\n");
	fstat(fd1,&stat);
	p1 = (char *)mmap(NULL,stat.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);
	//p2 = (char *)mmap(NULL,stat.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
	if(p1 == MAP_FAILED || p2 == MAP_FAILED)
		fprintf(stderr,"mmap error\n");
	write(fd2,p1,stat.st_size);
	munmap(p1,stat.st_size);
	munmap(p2,stat.st_size);
	return 0;
}
