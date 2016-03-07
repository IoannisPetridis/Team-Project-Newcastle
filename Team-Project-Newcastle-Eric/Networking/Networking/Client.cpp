#include "Client.h"

/*Connection to server*/
void Client::connection() {
	if (connect(s, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable to connect to server \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		//exit(1);
	}
	else {
		printf("\nConnected to the server .\n");
	}
}

SOCKET Client::getIncSocket() {
	return inc;
}

/*Client constructor*/
Client::Client() {
}

/*Client deconstructor*/
Client::~Client() {
}