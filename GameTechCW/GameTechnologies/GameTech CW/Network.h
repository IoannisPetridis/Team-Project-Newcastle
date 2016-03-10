#pragma once
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib,"wsock32.lib")

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <../ncltech/GameObject.h>
#include <time.h>


#define HIGHVERSION 2
#define LOWVERSION 2
#define PORT "4376"
#define FAMILY AF_UNSPEC
#define TYPE SOCK_STREAM
#define FLAGS AI_PASSIVE
#define PROTOCOL IPPROTO_TCP
#define BACKLOG 10
#define BUFFSIZE 1200	//A bit more than the size of the message for 9 objects and the delimiters



struct gameObjectData {
	std::string objName;
	Vector3 position,velocity,angular;	//Calculated data
	Quaternion  orientation;	//Calculated data
	std::string ballName;
	Vector3 ballposition,ballvelocity,ballangular;	//Calculated data
	Quaternion  ballorientation;	//Calculated data
};

struct clientInfo {
	std::string ip;
	int player_id;
	boolean ready = false;
	std::string min;
	std::string sec;
	gameObjectData gameObject;
};


class Network : public GameObject {
	//friend class GameObject;
	friend class GameObjectMag;
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
	virtual std::vector<std::string>* getMessageQueue();
	virtual void _stdcall sendMessage(SOCKET sock);
	virtual void _stdcall receiveMessage(SOCKET sock);


protected:
	WSAData wsaData;
	struct addrinfo *addr;
	SOCKET listening_sock = NULL;

	char *message;
	std::vector<std::string> *messageQueue;
	PCSTR HOST = "10.66.67.185"; //pointer to constant string
	time_t rawtime;
	struct tm *timeinfo;
};