#include "Client.h"

int main(void) {

	Client *client = new Client();
	client->connection();
	//client->receiveMessage(client->getIncSocket());
	client->setMessage("Hello Nina, could you please inform me if everything's alright ?");
	client->sendMessage();
	//delete client;
	while (1);
}