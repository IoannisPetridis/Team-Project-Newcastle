#include "Network.h"

class Server : public Network {
public:
	Server();
	~Server();
	void _stdcall bindSocket();
	void _stdcall listenSocket();
	bool _stdcall acceptCon();
	char * getMessage();
	SOCKET getListeningSocket();
	SOCKET getIncSocket();
private:
	SOCKET inc = NULL;
	struct sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
};