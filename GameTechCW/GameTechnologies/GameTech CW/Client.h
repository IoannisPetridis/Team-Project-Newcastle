#include "Network.h"
#include <sstream>
#include <vector>


class Client : public Network {
public:
	Client();
	~Client();
	void run();
	void initial_run();
	void ready();
	bool _stdcall connection();
	void _stdcall receiveMessage(SOCKET sock);
	SOCKET getListeningSocket();
	SOCKET getIncSocket();
private:
	static vector<Player*> IncomingPlayers;
	bool start = false;
	SOCKET inc = NULL;
	sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
};