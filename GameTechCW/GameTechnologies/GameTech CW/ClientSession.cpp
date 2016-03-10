#include "ClientSession.h"
#include <sstream>
#include "Server.h"

ClientSession::ClientSession(Server* parent, SOCKET inc, const std::string& client_ip)
{
	this->client_sock = inc;
	this->parent = parent;
	this->ip = client_ip;
	this->is_open = true;


}

ClientSession::~ClientSession()
{
	//Close Socket connection if open
	if (is_open)
	{
		closesocket(client_sock);
		is_open = false;
	}
}

void ClientSession::HandleConnection()
{
	while (is_open)
	{
		if (ReceiveMessage())
		{
			//Yay It worked!! :D
		}
	}
}

bool ClientSession::ReceiveMessage()
{
	char packet_length[4];
	int length;
	bool ret = false;
	while ((bytesreceived = recv(client_sock, packet_length, 4, MSG_PEEK)) >= 4)
	{
		length = *reinterpret_cast<int*>(&packet_length);
		bytesreceived = recv(client_sock, buff, length + 4, MSG_PEEK);
		if (bytesreceived < length + 4)
		{
			return false; // We will read the whole packet next frame!
		}



		bytesreceived = recv(client_sock, packet_length, 4, 0);

		length = *reinterpret_cast<int*>(&packet_length);
		bytesreceived = recv(client_sock, buff, length, 0);
		if (bytesreceived == -1) {
			printf("Error receiving\n");
			printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
			return false;
		}


		//Convert '*' to white space
		/*for (int i = 0; i < BUFFSIZE; ++i) {
			if (buff[i] == '*') {
			buff[i] = ' ';
			}
			}*/
		buff[bytesreceived] = '\0';


		//Convert Byte Buffer to string
		std::vector <std::string> data;
		std::stringstream ss(buff);
		std::string temp;
		/*while (ss >> temp) {
			data.push_back(temp);
			}*/

#if VERBOSE_MODE
		printf("Recieved Packet:\n-------------\n%s\n---------\n", buff);
#endif
		while (std::getline(ss, temp, '*')) {
			data.push_back(temp);
		}

		//Now vector data contains the client's message information

		
		switch (buff[0]) {
		case '0':	//Network initialization stuff
			ret = InitializeConnection(data);
			break;
		case '1':	//Physics
			ret = ReceivePhysicsUpdatePacket(data);
			break;
		case '2':	//Android
			break;
		case '3':
			break;
		}

		buff[bytesreceived] = '\0';
		//messageQueue->push_back("Message received. Received " + std::to_string(bytesreceived) + " bytes.\nMessage is: " + buff);
#if VERBOSE_MODE
		printf("Message received. Received %d bytes.\nMessage is: %s", bytesreceived, buff);
#endif
	}
	return ret; //True if message recieved and processed successfully
}

bool ClientSession::InitializeConnection(const packet_data& data)
{
	
	//Here the server gets to know if the client is ready to start playing the game, so he receives a message and sets that client's status accordingly
	//Example message:	string msg = "0*1*car*Vector3*Quaternion";
	//0 for not ready, 1 for ready
	std::string ip_in_packet = (std::string)data.at(2);
	if (ip_in_packet.compare(ip) != 0)
	{
		printf("ERROR: Recieved data from different IP Address!!");
		return false;
	}

	std::string::size_type sz;
	//Server should check when all clients are ready, and ignore messages before that point
	//min = localtime(&rawtime)->tm_min;
	//sec = localtime(&rawtime)->tm_sec;
	{
		std::lock_guard<std::mutex> lk(mutex);
		gameObject.objName = data.at(3); //+ std::to_string(car_counter);
		gameObject.position = Vector3(std::stof(data.at(4), &sz), std::stof(data.at(5), &sz), std::stof(data.at(6), &sz));
		gameObject.orientation = Quaternion(std::stof(data.at(7), &sz), std::stof(data.at(8), &sz), std::stof(data.at(9), &sz), std::stof(data.at(10), &sz));
		gameObject.velocity = Vector3(std::stof(data.at(11), &sz), std::stof(data.at(12), &sz), std::stof(data.at(13), &sz));
		gameObject.angular = Vector3(std::stof(data.at(14), &sz), std::stof(data.at(15), &sz), std::stof(data.at(16), &sz));

		gameObject.ballName = data.at(17); //+ std::to_string(car_counter);
		gameObject.ballposition = Vector3(std::stof(data.at(18), &sz), std::stof(data.at(19), &sz), std::stof(data.at(20), &sz));
		gameObject.ballorientation = Quaternion(std::stof(data.at(21), &sz), std::stof(data.at(22), &sz), std::stof(data.at(23), &sz), std::stof(data.at(24), &sz));
		gameObject.ballvelocity = Vector3(std::stof(data.at(25), &sz), std::stof(data.at(26), &sz), std::stof(data.at(27), &sz));
		gameObject.ballangular = Vector3(std::stof(data.at(28), &sz), std::stof(data.at(29), &sz), std::stof(data.at(30), &sz));
	}

	if (data.at(1) == "1" && ready == false) {
		ready = true;
		//parent->ThreadSafeNotifyReadyState(true);//
		parent->TSUpdateReadyStatus();
	}
	return true;
}

bool ClientSession::ReceivePhysicsUpdatePacket(const packet_data& data)
{
	std::string ip_in_packet = (std::string)data.at(1);
	if (ip_in_packet.compare(ip) != 0)
	{
		printf("ERROR: Recieved data from different IP Address!!");
		return false;
	}
	std::string::size_type sz;

	{
		std::lock_guard<std::mutex> lk(mutex);
		gameObject.objName = data.at(2); //+ std::to_string(car_counter);
		gameObject.position = Vector3(std::stof(data.at(3), &sz), std::stof(data.at(4), &sz), std::stof(data.at(5), &sz));
		gameObject.orientation = Quaternion(std::stof(data.at(6), &sz), std::stof(data.at(7), &sz), std::stof(data.at(8), &sz), std::stof(data.at(9), &sz));
		gameObject.velocity = Vector3(std::stof(data.at(10), &sz), std::stof(data.at(11), &sz), std::stof(data.at(12), &sz));
		gameObject.angular = Vector3(std::stof(data.at(13), &sz), std::stof(data.at(14), &sz), std::stof(data.at(15), &sz));

		gameObject.ballName = data.at(16); //+ std::to_string(car_counter);
		gameObject.ballposition = Vector3(std::stof(data.at(17), &sz), std::stof(data.at(18), &sz), std::stof(data.at(19), &sz));
		gameObject.ballorientation = Quaternion(std::stof(data.at(20), &sz), std::stof(data.at(21), &sz), std::stof(data.at(22), &sz), std::stof(data.at(23), &sz));
		gameObject.ballvelocity = Vector3(std::stof(data.at(24), &sz), std::stof(data.at(25), &sz), std::stof(data.at(26), &sz));
		gameObject.ballangular = Vector3(std::stof(data.at(27), &sz), std::stof(data.at(28), &sz), std::stof(data.at(29), &sz));
	}

	return true;
}

void ClientSession::SendClientData(const std::string& msg)
{ 
	std::lock_guard<std::mutex> lk(mutex);
	
	char *message = new char[msg.length() + 1];
	strcpy_s(message, msg.length() + 1, msg.c_str());

	int len = msg.length();
	char* int_length = (char*)reinterpret_cast<char*>(&len);
	send(client_sock, int_length, 4, 0);

	send(client_sock, message, strlen(message), 0);
#if VERBOSE_MODE
	printf("Sent data to client: \"%s\"\n", ip.c_str());
#endif
	delete[] message;
}
