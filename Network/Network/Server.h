#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define HIGHVERSION 2
#define LOWVERSION 2
#define HOST "127.0.0.1"
#define PORT "4376"
#define FAMILY AF_UNSPEC
#define TYPE SOCK_STREAM
#define FLAGS AI_PASSIVE
#define PROTOCOL IPPROTO_TCP
#define BACKLOG 10
#define BUFFSIZE 100

WSAData wsaData;
struct addrinfo *addr;



/*Initializes the Windows Sockets library*/
int init() {
	int error = WSAStartup(MAKEWORD(HIGHVERSION, LOWVERSION), &wsaData);
	if (error != 0) {
		fprintf(stderr, "WSAStartup failed with error %d. \n", error);
		return 1;
	}
	
	
	//Check version values
	if (LOBYTE(wsaData.wVersion) != LOWVERSION || HIBYTE(wsaData.wVersion) != HIGHVERSION) {
		printf("The version requested cannot be supported .\n");
		printf("Version set is %d.%d\n", LOBYTE(wsaData.wVersion),HIBYTE(wsaData.wVersion));
		WSACleanup();
		return 1;
	}
	else {
		printf("The Winsock API has been successfully initialised .\nYou are using version %d.%d.\n\n", HIBYTE(wsaData.wVersion), LOBYTE(wsaData.wVersion));
		return 0;
	}

}

/*Sorts out the addressing structs to create a socket*/
int addressing() {
	int result;
	struct addrinfo hints;
	struct addrinfo *temp;

	//initialize the hints struct
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = FAMILY;
	hints.ai_socktype = TYPE;
	hints.ai_flags = FLAGS;
	hints.ai_protocol = PROTOCOL;
	result = getaddrinfo(HOST, PORT, &hints, &addr);

	if (result != 0) {
		printf("getaddrinfo () failed with error : \n%d: %s\n", result, gai_strerror(WSAGetLastError()));
		WSACleanup();
		return 1;
	}

	//traverse the linked list
	printf("Addressing information :\n");

	int i = 0;
	for (temp = addr; temp != NULL; temp = temp->ai_next) {
		printf("\nEntry %d:\n", ++i);
		switch (temp->ai_family) {
		case AF_INET:
			printf("\tAddress family : AF_INET \n");
			break;
		case AF_INET6:
			printf("\tAddress family : AF_INET6 \n");
			break;
		}
		switch (temp -> ai_protocol) {
		case IPPROTO_TCP:
			printf("\tProtocol : TCP \n");
			break;
		case IPPROTO_UDP:
			printf("\tProtocol : UDP \n");
			break;
		}
		switch (temp -> ai_socktype) {
		case SOCK_STREAM:
			printf("\tSocket type : Stream \n");
			break;
		case SOCK_DGRAM:
			printf("\tSocket type : Datagram \n");
			break;
		}
	}
	return 0;
}