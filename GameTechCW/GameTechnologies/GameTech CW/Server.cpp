#include "Server.h"
#include <sstream>

//#include "winsock2.h"
//using namespace std;

/*Binds the current socket*/
void Server::bindSocket() {
	if (bind(listening_sock, addr->ai_addr, addr->ai_addrlen) != 0) {
		std::cout << "Unable fo bind to socket\nFailed with error: " << std::to_string(WSAGetLastError()) << "\n";
		//printf("Unable fo bind to socket\n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else
	{
		std::cout << "Bound to socket\n";
		//printf("Bound to socket\n");
	}
}

/*Start listening to the current socket*/
void Server::listenSocket() {
	if (listen(listening_sock, BACKLOG) != 0) {
		std::cout << "Unable to listen on socket\nFailed with error: " << std::to_string(WSAGetLastError()) << "\n";;
		//printf("Unable to listen on socket\n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
	}
	else {
		std::cout << "Listening on the socket...\n";
		//printf("Listening on the socket...\n");
	}
}

/*Accept new connection from a client*/
ClientSession* Server::acceptCon() {
	SOCKET inc;
	struct sockaddr_storage inc_addr;
	socklen_t inc_size = sizeof(inc_addr);

	if ((inc = accept(listening_sock, (struct sockaddr *) &inc_addr, &inc_size)) == INVALID_SOCKET) {
		std::cout << "Unable to accept new connection \nFailed with error: " << std::to_string(WSAGetLastError()) << "\n";
		//printf("Unable to accept new connection \n");
		//printf("Failed with error: %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		return NULL; 
	}
	else {
		u_long iMode = 1;
		ioctlsocket(inc, FIONBIO, &iMode);

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
		messageQueue->push_back("Received connection from IP: " + client + "\n");

		//Check if the client has already been identified by the server
		int foundIdx = -1;
		for (int i = 0; foundIdx == -1 && i < clients.size(); ++i)
		{
			if (clients[i]->GetIPAddress().compare(client) == 0)
				foundIdx = i;
		}

		if (foundIdx > -1) {
			//If the server knows about that IP, do nothing
			messageQueue->push_back("Known IP: " + client + "\n");
			clients[foundIdx]->SetSocket(inc);
			return clients[foundIdx];
		}
		else {
			//Else insert that IP into the clientList vector of the server
			messageQueue->push_back("New IP: " + client + "\n");

			ClientSession* new_client = new ClientSession(this, inc, client);

			clients.push_back(new_client);
			//foremostClient = new_client;
			return new_client;
		}
		//messageQueue->push_back("Accepted a new connection ...\n");
		//printf("Accepted a new connection ...\n");
		
	}
}



/*Server main loop function*/
void Server::run() {
	while (1) {
		//Is there a client waiting to connect????
		ClientSession* new_client;
		if (new_client = acceptCon()) {
			std::cout << "Attempting to create SOCKET" << std::endl;
			std::thread *t2 = new std::thread(&ClientSession::HandleConnection, new_client);
		}
	
		messageQueue->push_back("\nWaiting for connections...\n");
		while (!getMessageQueue()->empty()) {
			std::cout << getMessageQueue()->front();
			getMessageQueue()->erase(getMessageQueue()->begin());
		}
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


/*Get the pointer to the vector containing all the clients*/
const std::vector<ClientSession*>& Server::getClientList() {
	return clients;
}


SOCKET Server::getListeningSocket() {
	return listening_sock;
}


void Server::sendUpdateLoop() {
	Sleep(500);
	while (1) {
		Sleep(8);

		//Construct Scene Packet
		std::string msg;
		msg = "1" + GetWorldPacket();
		

		//Send to clients
		for (ClientSession* client : clients)
		{
			client->SendClientData(msg);
		}
#if VERBOSE_MODE
		printf("Sent Data To Clients!!\n---------------\n%s\n-------------\n\n", msg.c_str());
#endif
	}
}

std::string Server::GetWorldPacket()
{
	std::string msg;
	Vector3 ballPos = Vector3(0, 0, 0);
	Quaternion ballRot = Quaternion(0, 0, 0, 0);
	Vector3 ballVel = Vector3(0, 0, 0);
	Vector3 ballAng = Vector3(0, 0, 0);

	for (ClientSession* client : clients)
	{
		std::lock_guard<std::mutex> lk(client->mutex);
		const gameObjectData& gameObject = client->GetGameObject();

		msg += "*" + gameObject.objName + "*";
		msg += std::to_string(gameObject.position.x) + "*" + std::to_string(gameObject.position.y) + "*" + std::to_string(gameObject.position.z) + "*";
		msg += std::to_string(gameObject.orientation.x) + "*" + std::to_string(gameObject.orientation.y) + "*" + std::to_string(gameObject.orientation.z) + "*" + std::to_string(gameObject.orientation.w) + "*";
		msg += std::to_string(gameObject.velocity.x) + "*" + std::to_string(gameObject.velocity.y) + "*" + std::to_string(gameObject.velocity.z) + "*";
		msg += std::to_string(gameObject.angular.x) + "*" + std::to_string(gameObject.angular.y) + "*" + std::to_string(gameObject.angular.z);


		ballPos += gameObject.ballposition;
		ballVel += gameObject.ballvelocity;
		ballAng += gameObject.ballangular;
		ballRot.x += gameObject.ballorientation.x;
		ballRot.y += gameObject.ballorientation.y;
		ballRot.z += gameObject.ballorientation.z;
		ballRot.w += gameObject.ballorientation.w;

	/*	if (client == foremostClient) {

		msg += "*" + gameObject.ballName + "*";
		msg += std::to_string(gameObject.ballposition.x) + "*" + std::to_string(gameObject.ballposition.y) + "*" + std::to_string(gameObject.ballposition.z) + "*";
		msg += std::to_string(gameObject.ballorientation.x) + "*" + std::to_string(gameObject.ballorientation.y) + "*" + std::to_string(gameObject.ballorientation.z) + "*" + std::to_string(gameObject.ballorientation.w);
		msg += std::to_string(gameObject.ballvelocity.x) + "*" + std::to_string(gameObject.ballvelocity.y) + "*" + std::to_string(gameObject.ballvelocity.z) + "*";
		msg += std::to_string(gameObject.ballangular.x) + "*" + std::to_string(gameObject.ballangular.y) + "*" + std::to_string(gameObject.ballangular.z);
		}*/
	}
	float div = 1.0f / (float)(clients.size());
	ballPos *= div;
	ballVel *= div;
	ballAng *= div;
	ballVel.y -= 9.81 * 0.0166666f;

	ballRot.x *= div;
	ballRot.y *= div;
	ballRot.z *= div;
	ballRot.w *= div;

	ballRot.Normalise();

	msg += "*ball*";
	msg += std::to_string(ballPos.x) + "*" + std::to_string(ballPos.y) + "*" + std::to_string(ballPos.z) + "*";
	msg += std::to_string(ballRot.x) + "*" + std::to_string(ballRot.y) + "*" + std::to_string(ballRot.z) + "*" + std::to_string(ballRot.w) + "*";
	msg += std::to_string(ballVel.x) + "*" + std::to_string(ballVel.y) + "*" + std::to_string(ballVel.z) + "*";
	msg += std::to_string(ballAng.x) + "*" + std::to_string(ballAng.y) + "*" + std::to_string(ballAng.z);
	return msg;
}

void Server::SendStartGamePacket()
{
	std::string msg = "0*";
	msg += "1*3" +GetWorldPacket();

	//Send to clients
	for (ClientSession* client : clients)
	{
		client->SendClientData(msg);
	}
#if VERBOSE_MODE
	printf("Sent Data To Clients!!\n---------------\n%s\n-------------\n\n", msg.c_str());
	printf("\n");
#endif
}

void Server::TSUpdateReadyStatus()
{
	std::lock_guard<std::mutex> lk(mutex);
	ready_count++;

	if (ready_count == NUM_PLAYERS) //2 Clients
	{
		all_rdy = true;

		//Send A 'Hello' / 'Start Game Packet'!!
		SendStartGamePacket();

		std::thread *t2 = new std::thread(&Server::sendUpdateLoop, this);
	}
}


/*Server constructor*/
Server::Server() {
	bindSocket();
	freeaddrinfo(addr);
	listenSocket();
	time(&rawtime);
}

/*Server destructor*/
Server::~Server() {
	for (ClientSession* client : clients)
	{
		delete client;
	}
	clients.clear();

	closesocket(getListeningSocket());
}

