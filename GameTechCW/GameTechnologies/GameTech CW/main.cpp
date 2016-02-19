/*#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"*/
#include "Game.h"



int main() {
	/*Server *server = new Server();
	server->run();
	server->join();*/
	
	Game *game = new Game();
	Game *ptr;
	std::thread t1(&Game::run,ptr);
	t1.join();

	//game->join();
	delete game;
}