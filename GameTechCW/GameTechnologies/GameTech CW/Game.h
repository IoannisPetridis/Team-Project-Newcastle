#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"
#include <thread>
#include "Server.h"


class Game {
private:
	GameTimer engine_timer;
public:
	Game();
	~Game();
	void run();
	int Quit(bool pause = false, const string &reason = "");
};