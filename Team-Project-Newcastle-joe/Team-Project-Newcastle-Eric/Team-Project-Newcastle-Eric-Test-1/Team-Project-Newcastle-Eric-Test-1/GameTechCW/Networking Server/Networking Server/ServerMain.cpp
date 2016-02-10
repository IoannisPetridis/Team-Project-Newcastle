#include "Server.h"
using namespace std;

int main(void) {

	Server *server = new Server();
	while (1) {
		server->acceptCon();
		server->receiveMessage(server->getIncSocket());
		//server->setMessage("Hello Client, this is the Server talking to you");
		//server->sendMessage();
	}
}