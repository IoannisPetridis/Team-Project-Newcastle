#include "Server.h"

/*Binds the current socket*/
void Server::bindSocket() {
	if (bind(s, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable fo bind to socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Bound to socket\n");
	}
}

/*Start listening to the current socket*/
void Server::listenSocket() {
	if (listen(s, BACKLOG) != 0) {
		printf("Unable to listen on socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Listening on the socket .\n");
	}
}

/*Accept new connection from a client*/
void Server::acceptCon() {
	if ((inc = accept(s, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
		printf("Unable to accept new connection \n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Accepted a new connection ...\n");
	}
}

SOCKET Server::getIncSocket() {
	return inc;
}

/*Server constructor*/
Server::Server() {
	bindSocket();
	listenSocket();
}

/*Server destructor*/
Server::~Server() {

}