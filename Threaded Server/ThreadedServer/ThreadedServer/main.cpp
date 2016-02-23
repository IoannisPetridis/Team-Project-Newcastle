#include "Server.h"
#include <thread>


int main() {
	Server *server = new Server();
	Server *ptr;
	std::thread t1(&Server::run,ptr);
	
}