#include "Client.h"
using namespace std;

int main(void) {

	Client *client = new Client();
	while (1) {
		printf("\nWaiting for connections...\n");
		if (client->acceptCon()) {

			server->setMessage("Hello Server this is the Client");
			send(server->getIncSocket(), server->getMessage(), strlen(server->getMessage()), 0);

			server->receiveMessage(server->getIncSocket());
			closesocket(server->getIncSocket());
		}
	}
	closesocket(server->getListeningSocket());
	delete server;
}