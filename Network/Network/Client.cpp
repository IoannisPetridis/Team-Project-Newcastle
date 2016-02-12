#include "Server.h"

int main(void) {
	SOCKET s = NULL;

	//Initialise socket library
	if (init()) {
		printf("Unable to initialise the Winsock library\n");
		exit(1);
	}

	//Initialise addressing information
	if (addressing() != 0) {
		printf("Unable to initialise addressing information\n");
		exit(1);
	}

	//Create a socket for the server to listen on
	if ((s = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == INVALID_SOCKET) {
		printf("Unable to create a socket \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		exit(1);
	}
	else {
		printf("\nSocket created successfully .\n");
	}

	//Connect to server
	if (connect(s, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable to connect to server \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		//exit(1);
	}
	else {
		printf("\nConnected to the server .\n");
	}
	
	//Finished with addrinfo struct
	freeaddrinfo(addr);

	//Accept message from server and close
	int bytesreceived;
	char buff[BUFFSIZE];

	if ((bytesreceived = recv(s, buff, BUFFSIZE - 1, 0)) == -1) {
		printf("Error receiving\n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		buff[bytesreceived] = '\0';
		printf("Message received. Reeceived %d bytes.\nMessage is: %s", bytesreceived, buff);
	}

	char *hw = "Hello Server";
	send(s, hw, strlen(hw), 0);

	closesocket(s);
	WSACleanup();

	while (1);
	//exit(0);
}