#include "Client.h"

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

/*Get the incoming socket ?*/
SOCKET Client::getIncSocket() {
	return inc;
}

/*Get the active listening socket*/
SOCKET Client::getListeningSocket() {
	return listening_sock;
}

/*Client constructor*/
Client::Client() {
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