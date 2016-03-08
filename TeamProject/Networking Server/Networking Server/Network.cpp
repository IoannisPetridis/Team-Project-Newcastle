#include "Network.h"
#include <vector>
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
	if ((bytesreceived = recv(sock, buff, BUFFSIZE - 1, 0)) == -1) {
		printf("Error receiving\n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		//// //Start parsing the message
		//for (int i = 0; i < BUFFSIZE; ++i) {
		//	if (buff[i] == '*') {
		//		buff[i] = ' ';
		//	}
		//}
		//std::vector <std::string> data;
		//std::stringstream ss(buff);
		//std::string temp;
		//std::string obj;
		//while (ss >> temp) {
		//	data.push_back(temp);
		//}
		////Now vector data contains the client's message information
		//
		//obj = data.at(1);	//objName
		//std::string::size_type sz;
		//
		//switch (buff[0]) {
		//case '0':	//Network initialization stuff
		//	//Here the server gets to know if the client is ready to start playing the game, so he receives a message and sets that client's status accordingly in the clients vector
		//	//Example message:	string msg = "0*1";
		//	//0 for not ready, 1 for ready
		//	for (auto &item : *clients) {
		//		if (item.ip == last_client) {
		//			if (data.at(1)=="1") {
		//				item.ready = true;
		//				messageQueue->push_back("Client (" + std::string(last_client) + ") is READY");
		//			}
		//			break;
		//		}
		//	}
		//	break;
		//case '1':	//Physics
		//	//Vector3 pos = Vector3(data.at(2),data.at(3),data.at(4));
		//	//Quaternion ori = Quaternion(data.at(5),data.at(6),data.at(7),data.at(8));
		//	//Vector3 inpF = Vector3(data.at(9),data.at(10),data.at(11));
		//	//Quaternion inpOri = Quaternion(data.at(12),data.at(13),data.at(14),data.at(15));

		//	/*This is how we get each gameObject:

		//	for (auto &item : *clients) {
		//		for (auto &object :item.gameObjects) {
		//			//object.objName;
		//			//object.position;
		//			//object.orientation;
		//			//object.inpForce;
		//			//object.inpOrientation;
		//		}
		//	}

		//	*/
		//	//Now sends all the object data in one message
		//	for (auto &item : *clients) {
		//		if (item.ip == last_client) {
		//			for (auto &object : item.gameObjects) {
		//				//if (object.objName == obj) {
		//				for (int i = 2; i <= item.gameObjects.size()*15; i+=15) {
		//					object.objName = data.at(i - 1);
		//					object.position = Vector3(std::stof(data.at(i), &sz), std::stof(data.at(i + 1), &sz), std::stof(data.at(i + 2), &sz)); //calculated position
		//					object.orientation = Quaternion(std::stof(data.at(i + 3), &sz), std::stof(data.at(i + 4), &sz), std::stof(data.at(i + 5), &sz), std::stof(data.at(i + 6), &sz)); //calculated orientation
		//					object.inpForce = Vector3(std::stof(data.at(i + 7), &sz), std::stof(data.at(i + 8), &sz), std::stof(data.at(i + 9), &sz)); //force applied for the next update
		//					object.inpOrientation = Quaternion(std::stof(data.at(i + 10), &sz), std::stof(data.at(i + 11), &sz), std::stof(data.at(i + 12), &sz), std::stof(data.at(i + 13), &sz)); //orientation for the next update
		//					break;
		//				}
		//				//}
		//			}
		//			break;
		//		}
		//	}
		//	messageQueue->push_back("Data received from Client (" + std::string(last_client) + ")");
		//	//Now the client's gameobjectData is filled with the proper data
		//	break;
		//case '2':	//Android
		//	break;
		//}
		buff[bytesreceived] = '\0';
		messageQueue->push_back("Message received. Received " + std::to_string(bytesreceived) + " bytes.\nMessage is: " + buff);
		//printf("Message received. Received %d bytes.\nMessage is: %s", bytesreceived, buff);
	}
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