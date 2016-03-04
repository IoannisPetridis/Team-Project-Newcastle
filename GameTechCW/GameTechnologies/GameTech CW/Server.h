#include "Network.h"
#include <thread>

class Server : public Network {
public:
	Server();
	~Server();
	void _stdcall bindSocket();
	void _stdcall listenSocket();
	bool _stdcall acceptCon();
	void  run();
	void notify_client();
	void thread_run();
	void _stdcall receiveMessage(SOCKET sock);
	PCSTR _stdcall getLastClient();
	std::vector<PCSTR> * getClientList();
	SOCKET getListeningSocket();
	SOCKET getIncSocket();
private:
	bool all_rdy = false;
	SOCKET inc = NULL;
	struct sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
};