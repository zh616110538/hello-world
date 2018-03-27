#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#define port 5000
#define bufsize 1024


int main()
{
    char *buf = malloc(bufsize);
    int i,sockfd, connfd,ret;
    ssize_t n;
    socklen_t clilen;

    struct sockaddr_in sockfdaddr,client_addr;;

    // setup socket address structure
    memset(&sockfdaddr,0,sizeof(sockfdaddr));
    sockfdaddr.sin_family = AF_INET;
    sockfdaddr.sin_port = htons(port);
    sockfdaddr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (!sockfd)
    {
        perror("socket fail:");
        return -1;
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        perror("setsockopt fail:");
        return -1;
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(sockfd,(const struct sockaddr *)&sockfdaddr,sizeof(sockfdaddr)) < 0)
    {
        perror("bind fail:");
        return -1;
    }

    // convert the socket to listen for incoming connections
    if (listen(sockfd,SOMAXCONN) < 0)
    {
        perror("listen fail:");
        return -1;
    }
    connfd = accept(sockfd,(struct sockaddr *)&client_addr,&clilen);
    if(connfd < 0)
    {
        perror("accept fail:");
	return -1;
    }
    while(1){
        if((n = read(connfd,buf,bufsize))<= 0)
	    close(connfd);
        else
	    printf("recv:%s\n",buf);
        if(--ret <= 0)
	    break;
    }
    close(sockfd);
    free(buf);
}
