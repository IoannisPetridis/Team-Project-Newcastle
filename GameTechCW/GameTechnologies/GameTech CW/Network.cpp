#include "Network.h"
//#pragma comment(lib,"ws2_32.lib")
//#pragma comment(lib,"wsock32.lib")
#include <sstream>

/*Converts a string to char*/
char * Network::stringToCharStar(std::string str) {
	char *result = new char[str.length() + 1];
	strcpy_s(result, str.length() + 1, str.c_str());
	return result;
}

/*Initializes the Windows Sockets library*/
int Network::init() {
	int error = WSAStartup(MAKEWORD(HIGHVERSION, LOWVERSION), &wsaData);
	if (error != 0) {
		messageQueue->push_back("WSAStartup failed with error "+std::to_string(error)+". \n");
		//fprintf(stderr, "WSAStartup failed with error %d. \n", error);
		return 1;
	}
	//Check version values
	if (LOBYTE(wsaData.wVersion) != LOWVERSION || HIBYTE(wsaData.wVersion) != HIGHVERSION) {
		printf("The version requested cannot be supported .\n");
		printf("Version set is %d.%d\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
		WSACleanup();
		return 1;
	}
	else {
		printf("The Winsock API has been successfully initialised .\nYou are using version %d.%d.\n\n", HIBYTE(wsaData.wVersion), LOBYTE(wsaData.wVersion));
		return 0;
	}

}

/*Sorts out the addressing structs to create a socket*/
int Network::addressing() {
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
	messageQueue->push_back("Addressing information :\n");
	//printf("Addressing information :\n");

	int i = 0;
	for (temp = addr; temp != NULL; temp = temp->ai_next) {
		printf("\nEntry %d:\n", ++i);
		switch (temp->ai_family) {
		case AF_INET:
			messageQueue->push_back("\tAddress family : AF_INET \n");
			//printf("\tAddress family : AF_INET \n");
			break;
		case AF_INET6:
			messageQueue->push_back("\tAddress family : AF_INET6 \n");
			//printf("\tAddress family : AF_INET6 \n");
			break;
		}
		switch (temp->ai_protocol) {
		case IPPROTO_TCP:
			messageQueue->push_back("\tProtocol : TCP \n");
			//printf("\tProtocol : TCP \n");
			break;
		case IPPROTO_UDP:
			messageQueue->push_back("\tProtocol : UDP \n");
			//printf("\tProtocol : UDP \n");
			break;
		}
		switch (temp->ai_socktype) {
		case SOCK_STREAM:
			messageQueue->push_back("\tSocket type : Stream \n");
			//printf("\tSocket type : Stream \n");
			break;
		case SOCK_DGRAM:
			messageQueue->push_back("\tSocket type : Datagram \n");
			//printf("\tSocket type : Datagram \n");
			break;
		}
	}
	return 0;
}

/*Creates a socket*/
void Network::createSocket() {
	if ((listening_sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == INVALID_SOCKET) {
		printf("Unable to create a socket \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		exit(1);
	}
	else {
		messageQueue->push_back("\nSocket created successfully .\n");
		//printf("\nSocket created successfully .\n");
	}
}

/*Free addrinfo struct*/
void Network::freeaddr() {
	freeaddrinfo(addr);
}


/*Receive the message*/
void Network::receiveMessage(SOCKET sock) {

}

/*Set the message to send*/
void Network::setMessage(char *msg) {
	message = msg;
}

/*Get the latest message to be sent*/
char * Network::getMessage() {
	return message;
}

std::vector<std::string>* Network::getMessageQueue() {
	return messageQueue;
}

/*Send message to the server*/
void Network::sendMessage(SOCKET sock) {
	send(sock, message, strlen(message), 0);
}

/*Network Constructor*/
Network::Network() {
	messageQueue = new std::vector<std::string>();
	init();
	addressing();
	createSocket();
}

/*Network Destructor*/
Network::~Network() {
	freeaddr();
	closesocket(listening_sock);
	WSACleanup();
	delete messageQueue;
}