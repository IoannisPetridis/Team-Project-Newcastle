#include "Network.h"

class Server : public Network {
public:
	Server();
	~Server();
	void _stdcall bindSocket();
	void _stdcall listenSocket();
	void _stdcall acceptCon();
	SOCKET getIncSocket();
private:
	SOCKET inc = NULL;
	sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
};