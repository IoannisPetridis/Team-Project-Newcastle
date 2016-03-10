/*#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"*/
//#include "Game.h"
#include "Server.h"



int main() {
	Server *server = new Server();
	std::thread t1(&Server::run, server);
	t1.join();
	delete server;
}