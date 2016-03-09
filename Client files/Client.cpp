#include "Client.h"
#include <ncltech\CuboidCollisionShape.h>
#include <../ncltech/AssetsManager.h>
#include <thread>
vector<Player*> Client::IncomingPlayers;

/* Returns a string corresponding to this client's IPV4 */
std::string Client::getIP() {
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(1, 1);
	char *ip;

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	if (gethostname(name, sizeof(name)) == 0)
	{
		printf("Host name: %s\n", name);

		if ((hostinfo = gethostbyname(name)) != NULL)
		{
			int nCount = 0;
			while (hostinfo->h_addr_list[nCount])
			{
				ip = inet_ntoa(*(
				struct in_addr *)hostinfo->h_addr_list[nCount]);

				printf("IP #%d: %s\n", ++nCount, ip);
				return ip;
			}
		}
	}
}

/*Connection to server*/
bool Client::connection() {
	if (connect(listening_sock, addr->ai_addr, addr->ai_addrlen) != 0) {
		printf("Unable to connect to server \n");
		printf("Failed with error : %d\n%s\n", WSAGetLastError(), gai_strerror(WSAGetLastError()));
		//exit(1);
		return false;
	}
	else {
		printf("\nConnected to the server .\n");
		return true;
	}
}

/*Sends the initial values to the server*/
void Client::initial_run() {
	while (!start) {
		//Get the player name from the GUI and the object's position and orientation
		std::string playername = MainWindow::GetPlayerName();
		std::string msg = "0*1*"; //= "0*1*player2*0*1*2*3*4*5*6";	//Network message, player2 is ready, Position is (0,1,2), Orientation is (3,4,5,6,7)
		GameObject *g = scene->m_RootGameObject->FindGameObject(playername);
		GameObject *b = scene->m_RootGameObject->FindGameObject("ball");
		//std::vector<GameObject*>& children = g->GetChildren();
		msg += ip+"*";
		msg += playername + "*";
		msg += (std::to_string(g->Physics()->GetPosition().x) + "*" + std::to_string(g->Physics()->GetPosition().y) + "*" + std::to_string(g->Physics()->GetPosition().z) + "*");
		msg += (std::to_string(g->Physics()->GetOrientation().x) + "*" + std::to_string(g->Physics()->GetOrientation().y) + "*" + std::to_string(g->Physics()->GetOrientation().z) + "*" + std::to_string(g->Physics()->GetOrientation().w) +"*");
		msg += b->GetName() + "*";
		msg += (std::to_string(b->Physics()->GetPosition().x) + "*" + std::to_string(b->Physics()->GetPosition().y) + "*" + std::to_string(b->Physics()->GetPosition().z) + "*");
		msg += (std::to_string(b->Physics()->GetOrientation().x) + "*" + std::to_string(b->Physics()->GetOrientation().y) + "*" + std::to_string(b->Physics()->GetOrientation().z) + "*" + std::to_string(b->Physics()->GetOrientation().w));
		char * message = stringToCharStar(msg);
		setMessage(message);
		sendMessage(getListeningSocket());
		receiveMessage(getListeningSocket());
		std::cout << std::endl;
		if (start) {
			break;
		}
	}
	return;
}

/*Send data to server for physics update*/
void Client::run() {
	std::string msg="1*";//= "1*object*0.3*0.5*0.4*1.0*0.2*1.3*2*5*3*1*2*3*4";
	if (connection()) {
		//std::cout << "Please enter the message you want to send" << std::endl;
		//std::cin >> msg;
		
		//Here we need to find the object that belong to this player and the ball
		std::string playername = MainWindow::GetPlayerName();
		GameObject *g = scene->m_RootGameObject->FindGameObject(playername);
		GameObject *b = scene->m_RootGameObject->FindGameObject("ball");
		//std::vector<GameObject*>& children = g->GetChildren();
		msg += ip + "*";
		msg += playername + "*";
		msg += (std::to_string(g->Physics()->GetPosition().x) + "*" + std::to_string(g->Physics()->GetPosition().y) + "*" + std::to_string(g->Physics()->GetPosition().z) + "*");
		msg += (std::to_string(g->Physics()->GetOrientation().x) + "*" + std::to_string(g->Physics()->GetOrientation().y) + "*" + std::to_string(g->Physics()->GetOrientation().z) + "*" + std::to_string(g->Physics()->GetOrientation().w) + "*");
		msg += b->GetName() + "*";
		msg += (std::to_string(b->Physics()->GetPosition().x) + "*" + std::to_string(b->Physics()->GetPosition().y) + "*" + std::to_string(b->Physics()->GetPosition().z) + "*");
		msg += (std::to_string(b->Physics()->GetOrientation().x) + "*" + std::to_string(b->Physics()->GetOrientation().y) + "*" + std::to_string(b->Physics()->GetOrientation().z) + "*" + std::to_string(b->Physics()->GetOrientation().w));

		char * message = stringToCharStar(msg);
		setMessage(message);
		sendMessage(getListeningSocket());
		receiveMessage(getListeningSocket());
		std::cout << std::endl;
		//closesocket(client->getIncSocket());
		//closesocket(client->getListeningSocket());
	}
}

void Client::receiveMessage(SOCKET sock) {
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
		std::string obj; //= data.at(2);
		while (ss >> temp) {
			data.push_back(temp);
		}
		//Now vector data contains the client's message information

		std::string::size_type sz;
		GameObject *g = scene->m_RootGameObject;//->FindGameObject(obj);

		switch (buff[0]) {
		case '0':	//Network initialization stuff
			//Here the server gets to know if the client is ready to start playing the game, so he receives a message and sets that client's status accordingly in the clients vector
			//Example message:	string msg = "0*1";
			//0 for not ready, 1 for ready
			if (data.at(1) == "1") {
				start = true;
				min = stoi(data.at(2));
				for (int i = 3; i < data.size(); i += 8) {
					obj = data.at(i);
					if (g->FindGameObject(obj) == NULL) {
						//Create a new physics object and mesh for the other players' cars
						Vector3 pos = Vector3(std::stof(data.at(i + 1), &sz), std::stof(data.at(i + 2), &sz), std::stof(data.at(i + 3), &sz));
						Quaternion ori = Quaternion(std::stof(data.at(i + 4), &sz), std::stof(data.at(i + 5), &sz), std::stof(data.at(i + 6), &sz), std::stof(data.at(i + 7), &sz));

						IncomingPlayers.push_back(new Player(obj));
						Player* Temp = IncomingPlayers.at(IncomingPlayers.size() - 1);

						//set scene
						Temp->SetScene(g->GetScene());

						Temp->SetMesh(AssetsManager::Cube(), false);
						//settexture&bumpMap

						Temp->SetTexture(AssetsManager::m_ThrowTex, false);
						Temp->SetBumpMap(AssetsManager::m_ThrowTexBUMP, false);
						//
						Temp->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 5.0f)));
						Temp->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
						Temp->SetBoundingRadius(1.0f * 1.0f);

						Temp->Physics()->name = obj;
						Temp->Physics()->SetInverseMass(0.06f);
						Temp->Physics()->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
						Temp->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 2.0f)));

						Matrix3 inertia(0.1f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f, 0.0f, 0.1f);

						Temp->Physics()->SetInverseInertia(inertia);

						g->GetScene()->AddGameObject(Temp);
					}
				}
				//break;
			}
			else {
				for (int i = 2; i < data.size(); i += 8) {
					obj = data.at(i);
					if (g->FindGameObject(obj) == NULL) {
						//Create a new physics object and mesh for the other players' cars
						Vector3 pos = Vector3(std::stof(data.at(i + 1), &sz), std::stof(data.at(i + 2), &sz), std::stof(data.at(i + 3), &sz));
						Quaternion ori = Quaternion(std::stof(data.at(i + 4), &sz), std::stof(data.at(i + 5), &sz), std::stof(data.at(i + 6), &sz), std::stof(data.at(i + 7), &sz));

						IncomingPlayers.push_back(new Player(obj));
						Player* Temp = IncomingPlayers.at(IncomingPlayers.size() - 1);

						//set scene
						Temp->SetScene(g->GetScene());

						Temp->SetMesh(AssetsManager::Cube(), false);
						//settexture&bumpMap

						Temp->SetTexture(AssetsManager::m_ThrowTex, false);
						Temp->SetBumpMap(AssetsManager::m_ThrowTexBUMP, false);
						//
						Temp->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 5.0f)));
						Temp->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
						Temp->SetBoundingRadius(1.0f * 1.0f);

						Temp->Physics()->name = obj;
						Temp->Physics()->SetInverseMass(0.06f);
						Temp->Physics()->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
						Temp->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 2.0f)));

						Matrix3 inertia(0.1f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f, 0.0f, 0.1f);

						Temp->Physics()->SetInverseInertia(inertia);

						g->GetScene()->AddGameObject(Temp);
					}
				}
			}

			break;
		case '1':	//Physics
			/*This is how we get each gameObject:

			for (auto &item : *clients) {
			for (auto &object :item.gameObjects) {
			//object.objName;
			//object.position;
			//object.orientation;
			//object.inpForce;
			//object.inpOrientation;
			}
			}

			Example message of a scene with a total of 4 objects
			1 lol 1 2 3 4 5 6 7 kaka 1 2 3 4 5 6 7 peos 1 2 3 4 5 6 7 eleos 1 2 3 4 5 6 7

			*/
			////Now client and server send all the object data in one message and receive it likewise 
			//The code below is for receiving all the items at once
			//for (auto &item : *clients) {
			//	if (item.ip == last_client) {
			//		for (auto &object : item.gameObjects) {
			//			//if (object.objName == obj) {
			//			for (int i = 0; i < item.gameObjects.size()*8; i+=8) {	//This iteration should be correct! :S
			//				object.objName = data.at(i+1);
			//				object.position = Vector3(std::stof(data.at(i+2), &sz), std::stof(data.at(i + 3), &sz), std::stof(data.at(i + 4), &sz)); //calculated position
			//				object.orientation = Quaternion(std::stof(data.at(i + 5), &sz), std::stof(data.at(i + 6), &sz), std::stof(data.at(i + 7), &sz), std::stof(data.at(i + 8), &sz)); //calculated orientation
			//				//object.inpForce = Vector3(std::stof(data.at(i + 7), &sz), std::stof(data.at(i + 8), &sz), std::stof(data.at(i + 9), &sz)); //force applied for the next update
			//				//object.inpOrientation = Quaternion(std::stof(data.at(i + 10), &sz), std::stof(data.at(i + 11), &sz), std::stof(data.at(i + 12), &sz), std::stof(data.at(i + 13), &sz)); //orientation for the next update
			//				//break;
			//			}
			//			//}
			//		}
			//		break;
			//	}
			//}

			for (int i = 2; i < data.size(); i += 8) {
				obj = data.at(i);
				g->FindGameObject(obj)->Physics()->SetPosition(Vector3(std::stof(data.at(i+1), &sz), std::stof(data.at(i+2), &sz), std::stof(data.at(i+3), &sz)));
				g->FindGameObject(obj)->Physics()->SetOrientation(Quaternion(std::stof(data.at(i+4), &sz), std::stof(data.at(i+5), &sz), std::stof(data.at(i+6), &sz), std::stof(data.at(i+7), &sz)));
				g->FindGameObject("ball")->Physics()->SetPosition(Vector3(std::stof(data.at(i + 8), &sz), std::stof(data.at(i + 9), &sz), std::stof(data.at(i + 10), &sz)));
				g->FindGameObject("ball")->Physics()->SetOrientation(Quaternion(std::stof(data.at(i + 11), &sz), std::stof(data.at(i + 12), &sz), std::stof(data.at(i + 13), &sz), std::stof(data.at(i + 14), &sz)));
			}
			/*
			//The code below is for receiving just the player's car
			for (auto &item : *clients) {
				if (item.ip == last_client) {
					//for (auto &object : item.gameObjects) {
					//if (object.objName == obj) {
					//for (int i = 0; i < item.gameObjects.size() * 8; i += 8) {	//This iteration should be correct! :S
					//object.objName = data.at(i + 1);
					item.gameObject.position = Vector3(std::stof(data.at(2), &sz), std::stof(data.at(3), &sz), std::stof(data.at(4), &sz)); //calculated position
					item.gameObject.orientation = Quaternion(std::stof(data.at(5), &sz), std::stof(data.at(6), &sz), std::stof(data.at(7), &sz), std::stof(data.at(8), &sz)); //calculated orientation
					//object.inpForce = Vector3(std::stof(data.at(i + 7), &sz), std::stof(data.at(i + 8), &sz), std::stof(data.at(i + 9), &sz)); //force applied for the next update
					//object.inpOrientation = Quaternion(std::stof(data.at(i + 10), &sz), std::stof(data.at(i + 11), &sz), std::stof(data.at(i + 12), &sz), std::stof(data.at(i + 13), &sz)); //orientation for the next update
					//break;
					//}
					//}
					//}
					break;
				} 
			}
			*/
			messageQueue->push_back("Data received from Client (" + std::string(last_client) + ")");
			//Now the Client's and the Server's gameobjectData is filled with the proper data
			break;
		case '2':	//Android
			break;
		case '3':
			if (data.at(1) == "1") {
				start = true;
			}
			else {
				start = false;
			}
			break;
		}
		buff[bytesreceived] = '\0';
		messageQueue->push_back("Message received. Received " + std::to_string(bytesreceived) + " bytes.\nMessage is: " + buff);
		//printf("Message received. Received %d bytes.\nMessage is: %s", bytesreceived, buff);
	}
}

int Client::get_Min() {
	return min;
}

/*Get the incoming socket ?*/
SOCKET Client::getIncSocket() {
	return inc;
}

/*Get the active listening socket*/
SOCKET Client::getListeningSocket() {
	return listening_sock;
}


/*Client constructor*/
Client::Client(Scene *newscene) {
	scene = newscene;
	ip = getIP();
}

/*Client deconstructor*/
Client::~Client() {
	closesocket(getIncSocket());
	closesocket(getListeningSocket());
}

/*#include "Client.h"
using namespace std;

int main(void) {
	Client *client = new Client();
	string msg;//= "1*object*0.3*0.5*0.4*1.0*0.2*1.3*2*5*3*1*2*3*4";
		if (client->connection()) {
				cout << "Please enter the message you want to send" << endl;
				cin >> msg;
				char * message = client->stringToCharStar(msg);
				client->setMessage(message);
				client->sendMessage(client->getListeningSocket());
				client->receiveMessage(client->getListeningSocket());
				cout << endl;
				//closesocket(client->getIncSocket());
				//closesocket(client->getListeningSocket());
		}
		system("PAUSE");
			//delete msg;
			//msg = NULL;
		delete client;
		}*/