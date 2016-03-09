#include "Server.h"
#include <sstream>

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
SOCKET Server::acceptCon() {
	if ((inc = accept(listening_sock, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
		messageQueue->push_back("Unable to accept new connection \nFailed with error: " + std::to_string(WSAGetLastError()) + "\n");
		//printf("Unable to accept new connection \n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		return inc;
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
		//PCSTR new_client = client.c_str(); //THIS FUCKING WORKS
		messageQueue->push_back("Received connection from IP: " + client + "\n");
		//cout << "Received connection from IP: " << new_client << endl;

		//Check if the client has already been identified by the server
		if (std::find(clientList->begin(), clientList->end(), client) != clientList->end()) {
			//If the server knows about that IP, do nothing
			messageQueue->push_back("Known IP: " + client + "\n");
			//cout << "Known IP: " << new_client << endl;
		}
		else {
			//Else insert that IP into the clientList vector of the server
			messageQueue->push_back("New IP: " + client + "\n");
			//cout << "New IP: " << new_client << endl;
			clientList->push_back(client);
			clientInfo *newclient = new clientInfo();
			newclient->ip = client;
			clients->push_back(newclient);
		}
		messageQueue->push_back("Accepted a new connection ...\n");
		//printf("Accepted a new connection ...\n");
		return inc;
	}
}



/*Server main loop function*/
void Server::run() {
	while (1) {
		if (all_rdy) {
			std::thread *t3 = new std::thread(&Server::thread_run, this, inc);
		}
		messageQueue->push_back("\nWaiting for connections...\n");
		while (!getMessageQueue()->empty()) {
			std::cout << getMessageQueue()->front();
			getMessageQueue()->erase(getMessageQueue()->begin());
		}
		SOCKET new_client;
		if (new_client = acceptCon()) {
			std::cout << "Attempting to create SOCKET" << std::endl;
			std::thread *t2 = new std::thread(&Server::notify_client, this, inc);
		}
	}
}

/*Notifies the client when everyone is ready to start updating*/
void Server::notify_client(SOCKET new_client) {
	while (!all_rdy) {
		if (clients->size() >= 2) {
			int rdy_count = 0;
			for (auto ob : *clients) {
				if (ob->ready) {
					rdy_count++;
				}
			}
			if (clientList->size() == rdy_count) {
				all_rdy = true;
				break;
			}
		}
		receiveMessage(new_client);
			//notify_client(new_client);
		}
	std::cout << "I AM OUT!" << std::endl;
	return;
}

/*Thread for updating physics*/
void Server::thread_run(SOCKET new_client) {
	/*std::string msg = "Your IP is: ";
	std::string ip(getLastClient());
	std::string mes = msg + ip;*/
	while (1) {
		receiveMessage(new_client);
		messageQueue->push_back("\n");
	}
}

/*Returns the client whose message reached the server earlier*/
std::string getForemostClientIP(std::vector<clientInfo*> &clients) {
	int foremostMin = 61;
	int foremostSec = 61;
	int size = clients.size();
	int counter=0;

	//Determine the min that the earliest message arrived at
	for (auto &item : clients) {
		if (stoi(item->min) < foremostMin) {
			foremostMin = stoi(item->min);
		}
		if (stoi(item->sec) < foremostSec) {
			foremostSec = stoi(item->sec);
		}
	}
	for (auto &item : clients) {
		if (stoi(item->min) == foremostMin) {
			counter++;
		}
	}
	if (counter == size) { //That means that all client's messages arrived at the same minute
		//Check for the message that arrived earlier in seconds and return that client's name
		for (auto &item : clients) {
			if (stoi(item->sec) == foremostSec) {
				return item->ip;
			}
		}
	}
	else { //That means that not all clients arrived at the same minute
		for (auto &item : clients) {
			if (stoi(item->min) > foremostMin) {
				continue;
			}
			if (stoi(item->sec) == foremostSec) {
				return item->ip;
			}
		}

	}
}

/*Receive the message*/
void Server::receiveMessage(SOCKET sock) {
	if ((bytesreceived = recv(sock, buff, BUFFSIZE - 1, 0)) == -1) {
		printf("Error receiving\n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		// //Start parsing the message
		for (int i = 0; i < BUFFSIZE; ++i) {
			if (buff[i] == '*') {
				buff[i] = ' ';
			}
		}
		std::vector <std::string> data;
		std::stringstream ss(buff);
		std::string temp;
		std::string obj;
		while (ss >> temp) {
			data.push_back(temp);
		}
		//Now vector data contains the client's message information
		std::string::size_type sz;
		std::string msg;
		char *message;
		std::string foremostClient;
		std::string ip;
		switch (buff[0]) {
		case '0':	//Network initialization stuff
			//Here the server gets to know if the client is ready to start playing the game, so he receives a message and sets that client's status accordingly
			//Example message:	string msg = "0*1*car*Vector3*Quaternion";
			//0 for not ready, 1 for ready
			ip = (std::string)data.at(2);
			for (auto &item : *clients) {
				for (auto &client : *clientList) {
					if (item->ip == ip) { //HERE IS THE MISTAKE I THINK!
						if (data.at(1) == "1") {
							item->ready = true;
							messageQueue->push_back("Client (" + std::string(last_client) + ") is READY\n");
						}
						//item->min = localtime(&rawtime)->tm_min;
						//item->sec = localtime(&rawtime)->tm_sec;
						item->gameObject.objName = data.at(3); //+ std::to_string(car_counter);
						item->gameObject.position = Vector3(std::stof(data.at(4), &sz), std::stof(data.at(5), &sz), std::stof(data.at(6), &sz));
						item->gameObject.orientation = Quaternion(std::stof(data.at(7), &sz), std::stof(data.at(8), &sz), std::stof(data.at(9), &sz), std::stof(data.at(10), &sz));
						item->gameObject.ballName = data.at(11); //+ std::to_string(car_counter);
						item->gameObject.ballposition = Vector3(std::stof(data.at(12), &sz), std::stof(data.at(13), &sz), std::stof(data.at(14), &sz));
						item->gameObject.ballorientation = Quaternion(std::stof(data.at(15), &sz), std::stof(data.at(16), &sz), std::stof(data.at(17), &sz), std::stof(data.at(18), &sz));
						break;
					}
					break;
				}
			}
			msg = "0*";
			if (all_rdy) {
				timeinfo = localtime(&rawtime);
				msg += "1*" + std::to_string(timeinfo->tm_min+1);
			}
			else {
				msg += "0*";
			}
			for (auto &item : *clients) {
				//if (item.ip = last_client) {
				//for (auto &object : item.gameObjects) {
				msg += item->gameObject.objName + "*";
				msg += std::to_string(item->gameObject.position.x) + "*" + std::to_string(item->gameObject.position.y) + "*" + std::to_string(item->gameObject.position.z) + "*";
				msg += std::to_string(item->gameObject.orientation.x) + "*" + std::to_string(item->gameObject.orientation.y) + "*" + std::to_string(item->gameObject.orientation.z) + "*" + std::to_string(item->gameObject.orientation.w) +"*";
				msg += item->gameObject.ballName + "*";
				msg += std::to_string(item->gameObject.ballposition.x) + "*" + std::to_string(item->gameObject.ballposition.y) + "*" + std::to_string(item->gameObject.ballposition.z) + "*";
				msg += std::to_string(item->gameObject.ballorientation.x) + "*" + std::to_string(item->gameObject.ballorientation.y) + "*" + std::to_string(item->gameObject.ballorientation.z) + "*" + std::to_string(item->gameObject.ballorientation.w);
				//msg += std::to_string(object.inpForce.x) + "*" + std::to_string(object.inpForce.y) + "*" + std::to_string(object.inpForce.z) + "*";
				//msg += std::to_string(object.inpOrientation.x) + "*" + std::to_string(object.inpOrientation.y) + "*" + std::to_string(object.inpOrientation.z) + "*" + std::to_string(object.inpOrientation.x) + "*" + std::to_string(object.inpOrientation.w) +"*";

				//}
				//}
			}
			message = stringToCharStar(msg);
			setMessage(message);
			send(getIncSocket(), getMessage(), strlen(getMessage()), 0);
			messageQueue->push_back("Message " + msg + " send to the Client!\n");
			//closesocket(getIncSocket());
			//closesocket(getListeningSocket());
			while (!getMessageQueue()->empty()) {
				std::cout << getMessageQueue()->front();
				if (!getMessageQueue()->empty()) {
					getMessageQueue()->erase(getMessageQueue()->begin());
				}
			}
			//listenSocket();
			break;
		case '1':	//Physics

			foremostClient = getForemostClientIP(*clients);
			ip = data.at(1);
			//The code below is for receiving just the player's car
			for (auto &item : *clients) {
				for (auto &client : *clientList) {
					if (item->ip.compare(ip)) {
						//for (auto &object : item.gameObjects) {
						//if (object.objName == obj) {
						//for (int i = 0; i < item.gameObjects.size() * 8; i += 8) {	//This iteration should be correct! :S
						//object.objName = data.at(i + 1);
						item->gameObject.objName = data.at(2);
						item->gameObject.position = Vector3(std::stof(data.at(3), &sz), std::stof(data.at(3), &sz), std::stof(data.at(4), &sz)); //calculated position
						item->gameObject.orientation = Quaternion(std::stof(data.at(5), &sz), std::stof(data.at(6), &sz), std::stof(data.at(7), &sz), std::stof(data.at(8), &sz)); //calculated orientation
						item->gameObject.ballName = data.at(9);
						item->gameObject.ballposition = Vector3(std::stof(data.at(10), &sz), std::stof(data.at(11), &sz), std::stof(data.at(12), &sz)); //calculated position
						item->gameObject.ballorientation = Quaternion(std::stof(data.at(13), &sz), std::stof(data.at(14), &sz), std::stof(data.at(15), &sz), std::stof(data.at(16), &sz)); //calculated orientation
						//object.inpForce = Vector3(std::stof(data.at(i + 7), &sz), std::stof(data.at(i + 8), &sz), std::stof(data.at(i + 9), &sz)); //force applied for the next update
						//object.inpOrientation = Quaternion(std::stof(data.at(i + 10), &sz), std::stof(data.at(i + 11), &sz), std::stof(data.at(i + 12), &sz), std::stof(data.at(i + 13), &sz)); //orientation for the next update
						//break;
						//}
						//}
						//}
						break;
					}
					break;
				}
			}
			msg = "1";
			for (auto &item : *clients) {
				msg += "*" + item->gameObject.objName + "*";
				msg += std::to_string(item->gameObject.position.x) + "*" + std::to_string(item->gameObject.position.y) + "*" + std::to_string(item->gameObject.position.z) + "*";
				msg += std::to_string(item->gameObject.orientation.x) + "*" + std::to_string(item->gameObject.orientation.y) + "*" + std::to_string(item->gameObject.orientation.z) + "*" + std::to_string(item->gameObject.orientation.w);
				if (item->ip == foremostClient) {
					msg += item->gameObject.ballName + "*";
					msg += std::to_string(item->gameObject.ballposition.x) + "*" + std::to_string(item->gameObject.ballposition.y) + "*" + std::to_string(item->gameObject.ballposition.z) + "*";
					msg += std::to_string(item->gameObject.ballorientation.x) + "*" + std::to_string(item->gameObject.ballorientation.y) + "*" + std::to_string(item->gameObject.ballorientation.z) + "*" + std::to_string(item->gameObject.ballorientation.w);
				}
			}
			message = stringToCharStar(msg);
			setMessage(message);
			send(getIncSocket(), getMessage(), strlen(getMessage()), 0);
			//closesocket(getIncSocket());
			while (!getMessageQueue()->empty()) {
				std::cout << getMessageQueue()->front();
				if (!getMessageQueue()->empty()) {
					getMessageQueue()->erase(getMessageQueue()->begin());
				}
			}
			//listenSocket();
			messageQueue->push_back("Data received from Client (" + std::string(last_client) + ")");
			break;
		case '2':	//Android
			break;
		case '3':
			/*msg = "3";
			if (all_rdy) {
			msg += "*1";
			}
			else {
			msg += "*0";
			}
			char *message = stringToCharStar(msg);
			setMessage(message);
			send(getIncSocket(), getMessage(), strlen(getMessage()), 0);
			messageQueue->push_back("\nClient " + std::string(last_client) + " is notified\n");
			closesocket(getIncSocket());
			while (!getMessageQueue()->empty()) {
			std::cout << getMessageQueue()->front();
			getMessageQueue()->erase(getMessageQueue()->begin());
			}*/
			//closesocket(getIncSocket());
			//listenSocket();
			break;
		}
		buff[bytesreceived] = '\0';
		messageQueue->push_back("Message received. Received " + std::to_string(bytesreceived) + " bytes.\nMessage is: " + buff);
		//printf("Message received. Received %d bytes.\nMessage is: %s", bytesreceived, buff);
	}
}

/*Get the pointer to the vector containing all the clients*/
std::vector<std::string> *Server::getClientList() {
	return clientList;
}

/*Return the last connected client's IP*/
std::string Server::getLastClient() {
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
	clientList = new std::vector<std::string>();
	clients = new std::vector<clientInfo*>();
	bindSocket();
	freeaddrinfo(addr);
	listenSocket();
	time(&rawtime);
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