/*#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"*/
//#include "Game.h"
#include "Server.h"



int main() {

	//SYNCHRONIZE EVERYTHING WITH LOCAL TIME ! ! !

	Server *server = new Server();
	std::thread t1(&Server::run, server);
	t1.join();

	/*Client *client = new Client();
	std::thread t2(&Client::initial_run, client);
	t2.join();*/


	
	/*Game *game = new Game();
	Game *ptr;
	std::thread t1(&Game::run,ptr);
	t1.join();*/

	//game->join();
	//delete game;
	//delete server;
}