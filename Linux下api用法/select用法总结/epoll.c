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
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENTS 10000
#define port 5000


int main()
{
    char *buf = malloc(1024);
    struct epoll_event ev;
	struct epoll_event *events = (struct epoll_event *)malloc(sizeof(ev)*MAX_EVENTS);
    int n,sockfd, conn_sock, nfds, epollfd;

    /* Code to set up listening socket, 'sockfd',
       (socket(), bind(), listen()) omitted */
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
    if (listen(sockfd,20) < 0)
    {
        perror("listen fail:");
        return -1;
    }

    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
    {
        perror("epoll_ctl: sockfd");
        exit(EXIT_FAILURE);
    }
    socklen_t addrlen = sizeof(client_addr);
    for (;;)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == sockfd)
            {
                conn_sock = accept(sockfd,
                                   (struct sockaddr *) &client_addr, &addrlen);
                if (conn_sock == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                //setnonblocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                              &ev) == -1)
                {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                //do_use_fd(events[n].data.fd);
                reuse = recv(events[n].data.fd,buf,1024,0);
                if(reuse <= 0)
                {

                    if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[n].data.fd,&ev) == -1)
                    {
                        perror("epoll_ctl: conn_sock");
                        exit(EXIT_FAILURE);
                    }
                    close(events[n].data.fd);
                }
                else
                {
                    printf("receive:%s",buf);
                }
            }
        }
    }
	free(buf);
	free(events);
	close(epollfd);
}
