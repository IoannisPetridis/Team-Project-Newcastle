#include "Network.h"

class Client : public Network {
public:
	Client();
	~Client();
	bool _stdcall connection();
	SOCKET getListeningSocket();
	SOCKET getIncSocket();
private:
	SOCKET inc = NULL;
	sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);
};