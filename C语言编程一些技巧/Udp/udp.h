/*
 * udp.h
 *
 *  Created on: 2018-3-27
 *      Author: 朱浩
 */

#ifndef UDP_H_
#define UDP_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <string>

class Udp
{
public:
	Udp();
	Udp(int port,int time = 0);
	~Udp();
	void bind(int port);
	int send(const std::string msg,const std::string addr,int port);
	int recv(std::string &s);
	int recv(std::string &s,std::string &addr,int &port);
	void set_timeout(int time);
	void show_timeout();
private:
	struct sockaddr_in set_addr_port(const std::string addr,int port);
	int fd;
	int timeout;
	struct sockaddr_in ser_addr;
};

#endif /* UDP_H_ */

