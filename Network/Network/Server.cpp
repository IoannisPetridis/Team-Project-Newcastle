#include "Server.h"
using namespace std;

int main(void) {
	SOCKET s = NULL;

	//Initialise socket library
	if (init()){
		printf("Unable to initialise the Winsock library\n");
		exit(1);
	}

	//Initialise addressing information

	if (addressing() != 0) {
		printf(" Uanble to initialise addressing information \n");
		exit(1);
	}

	//Create a socket for the server to listen on
	if ((s = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == INVALID_SOCKET) {
		printf(" Unable to create a socket \n");
		printf(" Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		exit(1);
	}
	else {
		printf("\nSocket created successfully .\n");
	}

	//bind to the socket created above
	if (bind(s, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable fo bind to socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Bound to socket\n");
	}

	//Finished with addrinfo struct now
	freeaddrinfo(addr);

	//Listen on the socket
	if (listen(s, BACKLOG) != 0) {
		printf("Unable to listen on socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Listening on the socket .\n");
	}

	//Continually accept  new connections
	while (1) 
	{
		printf("\nWaiting for connections ...\n");
		SOCKET inc = NULL;
		struct sockaddr_storage inc_addr;
		socklen_t inc_size = sizeof (inc_addr);

		//Accept new connection from a client
		if ((inc = accept(s, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
			printf("Unable to accept new connection \n");
			printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		}
		else {
			printf(" Accepted a new connection ...\n");
		}

		//Send test message to the client
		char *hw = "Hello Client";
		send(inc, hw, strlen(hw), 0);

		//Receive message from client
		int bytesreceived;
		char buff[BUFFSIZE];

		if ((bytesreceived = recv(inc, buff, BUFFSIZE - 1, 0)) == -1) {
			printf(" Error receiving \n");
			printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		}
		else {
			buff[bytesreceived] = '\0';
			printf("Message received. Received %d bytes.\nMessage is: %s\n", bytesreceived, buff);
		}
		//Close socket
		closesocket(inc);
	}

	//Close socket
	closesocket(s);
	WSACleanup();
}