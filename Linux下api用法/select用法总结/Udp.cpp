/*
 * udp.c
 *
 *  Created on: 2018-3-27
 *      Author: 朱浩
 */

#include "udp.h"


Udp::Udp():timeout(0)
{
	struct timeval tv;
	tv.tv_sec = timeout;
	tv.tv_usec = 0;

    this->fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&this->ser_addr, 0, sizeof(this->ser_addr));

    if(setsockopt(this->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))<0)
    	exit(-1);
}


Udp::Udp(int port,int time):timeout(time)
{
	struct timeval tv;
	tv.tv_sec = timeout;
	tv.tv_usec = 0;

    this->fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd<0)
    	exit(-1);

    memset(&this->ser_addr, 0, sizeof(this->ser_addr));
    this->ser_addr.sin_family = AF_INET;
    this->ser_addr.sin_port = htons(port);  //注意网络序转换
    this->ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET,addr.c_str(),&ser_addr.sin_addr.s_addr);

    if(::bind(fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr)))
    	exit(-1);

    if(setsockopt(this->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))<0)
    	exit(-1);
}

Udp::~Udp()
{
	int reuse = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	close(fd);
}

void Udp::bind(int port)
{
    memset(&this->ser_addr, 0, sizeof(this->ser_addr));
    this->ser_addr.sin_family = AF_INET;
    this->ser_addr.sin_port = htons(port);  //注意网络序转换
    this->ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET,addr.c_str(),&ser_addr.sin_addr.s_addr);

    if(::bind(fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr)))
    	exit(-1);
}

int Udp::send(const std::string msg,const std::string addr,int port)
{
	struct sockaddr_in dst = set_addr_port(addr,port);
    socklen_t len;
	len = sizeof(dst);
	return sendto(fd, msg.c_str(), msg.length(), 0, (struct sockaddr*)&dst, len);
}

int Udp::recv(std::string &s)
{
    char buf[1024];  //接收缓冲区，1024字节
    memset(buf,0,1024);
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
	len = sizeof(clent_addr);
	count = recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
	s = buf;
	return count;
}

int Udp::recv(std::string &s,std::string &addr,int &port)
{
    char buf[1024];  //接收缓冲区，1024字节
    memset(buf,0,1024);
    socklen_t len;
    int count;
    struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
	len = sizeof(clent_addr);
	count = recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
	s = buf;
	addr = inet_ntoa(clent_addr.sin_addr);
	port = ntohs(clent_addr.sin_port);
	return count;
}

void Udp::set_timeout(int time)
{
	timeout = time;
	struct timeval tv;
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
    if(setsockopt(this->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))<0)
    	exit(-1);
}

void Udp::show_timeout()
{
	std::cout<<"timeout is "<<timeout<<" s"<<std::endl;
}

struct sockaddr_in Udp::set_addr_port(const std::string ip,int port)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);  //注意网络序转换
    inet_pton(AF_INET,ip.c_str(),&addr.sin_addr.s_addr);
    return addr;
}

