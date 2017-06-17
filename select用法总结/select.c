#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define MAX_EVENTS 10
#define port 5000
#define bufsize 1024


int main()
{
    char *buf = malloc(bufsize);
    int i,maxi,maxfd,sockfd, connfd,ret,client[MAX_EVENTS];
    ssize_t n;
    fd_set rset,allset;
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
    maxfd = sockfd;
    maxi = -1;
    memset(client,-1,MAX_EVENTS*sizeof(int));
    FD_ZERO(&allset);
    FD_SET(sockfd,&allset);
    for(;;)
    {
        rset = allset;
        ret = select(maxfd+1,&rset,NULL,NULL,NULL);
        if(ret < 0)
        {
            perror("select fail:");
            return -1;
        }
        if(FD_ISSET(sockfd,&rset))
        {
            clilen = sizeof(client_addr);
            connfd = accept(sockfd,(struct sockaddr *)&client_addr,&clilen);
            if(connfd < 0)
            {
                perror("accept fail:");
                continue;
            }
            for(i=0; i<MAX_EVENTS; ++i)
            {
                if(client[i]<0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if(i == MAX_EVENTS)
            {

                send(connfd,"bye",4,0);
                close(connfd);
                client[i] = -1;
                continue;
            }
            FD_SET(connfd,&allset);
            if(connfd > maxfd)
                maxfd = connfd;
            if(i > maxi)
                maxi = i;
            if( --ret <= 0)
                continue;
        }
        for(i=0; i<=maxi; ++i)
        {
            if(client[i] < 0)
                continue;
            if(FD_ISSET(client[i],&rset))
            {
                if((n = read(client[i],buf,bufsize))<= 0)
                {
                    close(client[i]);
                    FD_CLR(client[i],&allset);
                    client[i] = -1;
                }
                else
                    printf("recv:%s\n",buf);
                if(--ret <= 0)
                    break;
            }
        }
    }
    free(buf);
}
