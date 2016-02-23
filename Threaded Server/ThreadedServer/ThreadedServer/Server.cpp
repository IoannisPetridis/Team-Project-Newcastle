#include "Server.h"
#include <thread>

//#include "winsock2.h"
//using namespace std;

/*Binds the current socket*/
void Server::bindSocket() {
	if (bind(listening_sock, addr->ai_addr, addr->ai_addrlen) != 0) {
		messageQueue->push_back("Unable fo bind to socket\nFailed with error: " + std::to_string(WSAGetLastError()) + "\n");
		//printf("Unable fo bind to socket\n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		messageQueue->push_back("Bound to socket\n");
		//printf("Bound to socket\n");
	}
}

/*Start listening to the current socket*/
void Server::listenSocket() {
	if (listen(listening_sock, BACKLOG) != 0) {
		messageQueue->push_back("Unable to listen on socket\nFailed with error: " + std::to_string(WSAGetLastError()) + "\n");
		//printf("Unable to listen on socket\n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		messageQueue->push_back("Listening on the socket...\n");
		//printf("Listening on the socket...\n");
	}
}

/*Accept new connection from a client*/
bool Server::acceptCon() {
	if ((inc = accept(listening_sock, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
		messageQueue->push_back("Unable to accept new connection \nFailed with error: " + std::to_string(WSAGetLastError()) + "\n");
		//printf("Unable to accept new connection \n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		return false;
	}
	else {
		int temp[4];
		for (int i = 2; i < sizeof(inc_addr.__ss_pad1); ++i) {
			if (int(inc_addr.__ss_pad1[i]) < 0) { 
				temp[i-2] = 256 + inc_addr.__ss_pad1[i]; 
			}
			else temp[i-2] = inc_addr.__ss_pad1[i];
			//std::cout << temp[i-2] << std::endl;
		}
		//Don't even ask me what I am doing here...
		
		std::string client = (std::to_string(temp[0]) + "." + std::to_string(temp[1]) + "." + std::to_string(temp[2]) + "." + std::to_string(temp[3]));
		PCSTR new_client = client.c_str(); //THIS FUCKING WORKS
		messageQueue->push_back("Received connection from IP: " + (std::string)new_client+"\n");
		//cout << "Received connection from IP: " << new_client << endl;
		char *last_ip = new char[client.length() + 1];
		strcpy_s(last_ip, sizeof(client), client.c_str());
		last_client = last_ip;

		//Check if the client has already been identified by the server
		if (std::find(clientList->begin(), clientList->end(), new_client) != clientList->end()) {
			//If the server knows about that IP, do nothing
			messageQueue->push_back("Known IP: " + (std::string)new_client + "\n");
			//cout << "Known IP: " << new_client << endl;
		}
		else {
			//Else insert that IP into the clientList vector of the server
			messageQueue->push_back("New IP: " + (std::string)new_client + "\n");
			//cout << "New IP: " << new_client << endl;
			clientList->push_back(new_client);
			clientInfo newclient;
			newclient.ip = new_client;
			clients->push_back(newclient);
		}
		messageQueue->push_back("Accepted a new connection ...\n");
		//printf("Accepted a new connection ...\n");
		return true;
	}
}

/*Server run function*/
void Server::run() {
	while (1) {
		//cout << endl << "Waiting for connections..." << endl;
		messageQueue->push_back("\nWaiting for connections...\n");
		while (!getMessageQueue()->empty()) {
			std::cout << getMessageQueue()->front();
			getMessageQueue()->erase(getMessageQueue()->begin());
		}
		if (acceptCon()) {
			bool all_rdy = true;
			if (clients->size() >= 2) {
				for (auto ob : *clients) {
					all_rdy = all_rdy && ob.ready;
				}
				if (all_rdy) {
					std::thread *t2 = new std::thread(&Server::notify_client, this);
					t2->join();
				}
			}
			std::thread *t = new std::thread(&Server::thread_run, this);
			//t->join();
			//while (1) {
				
				//break;
			//}
			//server->bindSocket();
			//listenSocket();
		}
	}
}

/*Notifies the client when everyone is ready to start updating*/
void Server::notify_client() {
	std::string msg = "3";
	receiveMessage(getIncSocket());
	messageQueue->push_back("\n");
	char *message = stringToCharStar(msg);
	setMessage(message);
	send(getIncSocket(), getMessage(), strlen(getMessage()), 0);
	closesocket(getIncSocket());
	while (!getMessageQueue()->empty()) {
		std::cout << getMessageQueue()->front();
		getMessageQueue()->erase(getMessageQueue()->begin());
	}
	listenSocket();
}

void Server::thread_run() {
	std::string msg = "1";
	/*std::string msg = "Your IP is: ";
	std::string ip(getLastClient());
	std::string mes = msg + ip;*/
	receiveMessage(getIncSocket());
	messageQueue->push_back("\n");

	/*GameObject *g ;
	GameObject *parent = g->GetParent();
	for (auto m : parent->GetChildren()) {
		msg += m->GetName() + "*";
		msg += (std::to_string(m->Physics()->GetPosition().x) + "*" + std::to_string(m->Physics()->GetPosition().y) + "*" + std::to_string(m->Physics()->GetPosition().z) + "*");
		msg += (std::to_string(m->Physics()->GetOrientation().x) + "*" + std::to_string(m->Physics()->GetOrientation().y) + "*" + std::to_string(m->Physics()->GetOrientation().z) + "*" + std::to_string(m->Physics()->GetOrientation().w));
	}*/

	for (auto &item : *clients) {
		//if (item.ip = last_client) {
			//for (auto &object : item.gameObjects) {
		msg += "*" + item.gameObject.objName + "*";
		msg += std::to_string(item.gameObject.position.x) + "*" + std::to_string(item.gameObject.position.y) + "*" + std::to_string(item.gameObject.position.z) + "*";
		msg += std::to_string(item.gameObject.orientation.x) + "*" + std::to_string(item.gameObject.orientation.y) + "*" + std::to_string(item.gameObject.orientation.z) + "*" + std::to_string(item.gameObject.orientation.w);
				//msg += std::to_string(object.inpForce.x) + "*" + std::to_string(object.inpForce.y) + "*" + std::to_string(object.inpForce.z) + "*";
				//msg += std::to_string(object.inpOrientation.x) + "*" + std::to_string(object.inpOrientation.y) + "*" + std::to_string(object.inpOrientation.z) + "*" + std::to_string(object.inpOrientation.x) + "*" + std::to_string(object.inpOrientation.w) +"*";

			//}
		//}
	}
	char *message = stringToCharStar(msg);
	setMessage(message);
	send(getIncSocket(), getMessage(), strlen(getMessage()), 0);
	closesocket(getIncSocket());
	while (!getMessageQueue()->empty()) {
		std::cout << getMessageQueue()->front();
		getMessageQueue()->erase(getMessageQueue()->begin());
	}
	listenSocket();
}

/*Get the pointer to the vector containing all the clients*/
std::vector<PCSTR> *Server::getClientList() {
	return clientList;
}

/*Return the last connected client's IP*/
char * Server::getLastClient() {
	return last_client;
}

SOCKET Server::getListeningSocket() {
	return listening_sock;
}

SOCKET Server::getIncSocket() {
	return inc;
}

/*Server constructor*/
Server::Server() {
	clientList = new std::vector<PCSTR>();
	clients = new std::vector<clientInfo>();
	bindSocket();
	freeaddrinfo(addr);
	listenSocket();

	
	/*GameObject *g;
	GameObject *parent = g->GetParent();
	
	for (auto m : parent->GetChildren()) {
		for (auto &item : *clients) {
			for (auto &object : item.gameObjects) {
				object.objName = g.GetName();
				object.position = m->Physics()->GetPosition;
				object.orientation = m->Physics()->GetOrientation();
			}
		}
	}*/
}

/*Server destructor*/
Server::~Server() {
	closesocket(getIncSocket());
	closesocket(getListeningSocket());
	delete clientList;
	clientList = NULL;
	delete clients;
	clients = NULL;
}

/*#include "Server.h"
using namespace std;

//template <typename T> char * convertToCharStar(T& a) {
//	string temp = std::to_string(a);
//	char *result = new char[a.length() + 1];
//	//memset(result, a, sizeof(a));
//	strcpy_s(result, sizeof(temp), temp.c_str());
//	return result;
//}

int main(void) {

	Server *server = new Server();
	server->runServer();
	
	//std::queue<std::string>* messages = server->getMessageQueue(); 
	
	delete server;
	}*/