#include "Client.h"

/*Connection to server*/
bool Client::connection() {
	if (connect(listening_sock, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable to connect to server \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		//exit(1);
		return false;
	}
	else {
		printf("\nConnected to the server .\n");
		return true;
	}
}

/*Get the incoming socket ?*/
SOCKET Client::getIncSocket() {
	return inc;
}

/*Get the active listening socket*/
SOCKET Client::getListeningSocket() {
	return listening_sock;
}

/*Client constructor*/
Client::Client() {
}

/*Client deconstructor*/
Client::~Client() {
	closesocket(getIncSocket());
	closesocket(getListeningSocket());
}

