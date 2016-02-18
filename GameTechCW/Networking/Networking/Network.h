#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>


#define HIGHVERSION 2
#define LOWVERSION 2
//#define HOST "127.0.0.1" //ipconfig in cmd and copy the IPV4 command here, YULONG: 10.66.67.181
#define PORT "4376"
#define FAMILY AF_UNSPEC
#define TYPE SOCK_STREAM
#define FLAGS AI_PASSIVE
#define PROTOCOL IPPROTO_TCP
#define BACKLOG 10
#define BUFFSIZE 100


class Network {
public:
	Network();
	~Network();
	char * stringToCharStar(std::string str);
	int init();
	int addressing();
	void _stdcall createSocket();
	virtual void _stdcall freeaddr();
	virtual void _stdcall setMessage(char *msg);
	virtual char * getMessage();
	virtual void _stdcall sendMessage(SOCKET sock);
	virtual void _stdcall receiveMessage(SOCKET sock);

protected:
	WSAData wsaData;
	struct addrinfo *addr;
	SOCKET listening_sock = NULL;
	char *message;
	int bytesreceived;
	char buff[BUFFSIZE];
	PCSTR HOST = "10.66.67.185"; //pointer to constant string
};