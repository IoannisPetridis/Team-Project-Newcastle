#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <mutex>
#include "Network.h"

#define BUFFSIZE 1200	//A bit more than the size of the message for 9 objects and the delimiters

class Server;

typedef std::vector<std::string> packet_data;

class ClientSession {
public:
	ClientSession(Server* parent, SOCKET inc, const std::string& client_ip);
	~ClientSession();

	void HandleConnection(); //Infinite loop on seperate thread

	void SendClientData(const std::string& msg); //<- THREAD SAFE



	const std::string& GetIPAddress() { return ip; }
	const gameObjectData& GetGameObject() { return gameObject; }
	std::mutex mutex;


	void SetSocket(SOCKET socket) {
		client_sock = socket;
	}
protected:
	bool ReceiveMessage();

	bool InitializeConnection(const packet_data& data);
	bool ReceivePhysicsUpdatePacket(const packet_data& data);


private:
	//Game Data
	int player_id;
	boolean ready = false;
	std::string min;
	std::string sec;

	


	bool is_open;
	std::string ip;
	Server* parent;

	//Buffered Data
	WSAData wsaData;
	struct addrinfo *addr;
	SOCKET client_sock = NULL;

	int bytesreceived;
	char buff[BUFFSIZE];

	int bytessent;

	gameObjectData gameObject;
};