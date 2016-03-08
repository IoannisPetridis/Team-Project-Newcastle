#include "Server.h"

/*Binds the current socket*/
void Server::bindSocket() {
	if (bind(listening_sock, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable fo bind to socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Bound to socket\n");
	}
}

/*Start listening to the current socket*/
void Server::listenSocket() {
	if (listen(listening_sock, BACKLOG) != 0) {
		printf("Unable to listen on socket\n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		printf("Listening on the socket...\n");
	}
}

/*Accept new connection from a client*/
bool Server::acceptCon() {
	if ((inc = accept(listening_sock, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
		printf("Unable to accept new connection \n");
		printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		return false;
	}
	else {
		printf("Accepted a new connection ...\n");
		return true;
	}
}

/*Get the latest message to be sent*/
char * Server::getMessage() {
	return message;
}

/*Get the active listening socket*/
SOCKET Server::getListeningSocket() {
	return listening_sock;
}

/*Get the incoming socket ?*/
SOCKET Server::getIncSocket() {
	return inc;
}

/*Server constructor*/
Server::Server() {
	bindSocket();
	freeaddrinfo(addr);
	listenSocket();
}

/*Server destructor*/
Server::~Server() {
	closesocket(inc);
}