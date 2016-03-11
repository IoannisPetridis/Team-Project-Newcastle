#pragma once
#include "Network.h"
#include <thread>
#include "ClientSession.h"
#include <mutex>

#define VERBOSE_MODE FALSE

#define NUM_PLAYERS 1

class Server : public Network {
public:
	Server();
	~Server();

	void _stdcall bindSocket();
	void _stdcall listenSocket();

	ClientSession* acceptCon();


	const std::vector<ClientSession*>& getClientList();
	SOCKET getListeningSocket();

	void run();

	void TSUpdateReadyStatus();

	void sendUpdateLoop();
	void SendStartGamePacket();
	std::string GetWorldPacket();
private:
	std::mutex mutex;
	int ready_count = 0;

	bool all_rdy = false;
	std::vector<ClientSession*> clients;
	ClientSession* foremostClient = NULL;
};