#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"

//#include "../../Networking Server/Networking Server/Server.h"

Scene* scene = NULL;

int Quit(bool pause = false, const string &reason = "") {
	if (scene)
	{
		delete scene;
		scene = NULL;
	}

	Window::Destroy();

	if (pause) {
		std::cout << reason << std::endl;
		system("PAUSE");
	}

	return 0;
}

int main()
{
	//-------------------
	//--- MAIN ENGINE ---
	//-------------------

	//Initialise the Window
	if (!Window::Initialise("Engine", 1280, 800, false))
	{
		return Quit(true, "Window failed to initialise!");
	}

	//Initialise the PhysicsEngine
	//Create GameObject Iterate Root Node upon which the GameObject List will be built
	PhysicsEngine::Instance();

	//Initialise the Scene, complete scene graph list
	//All Game Assets will be pre-loaded in
	//by initialising GameAssetsManager
	scene = new MyScene(Window::GetWindow());

	//Initialise the ActionHandler Instnace
	ActionHandler::Instance();
	ActionHandler::Instance()->SetDefaultScene(scene);

	if (!scene->HasInitialised())
	{
		return Quit(true, "Renderer failed to initialise!");
	}

	GameTimer engine_timer;

	//Server* server = new Server();
	//server->runServer();

	//Create main game-loop
	while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f;	//How many milliseconds since last update?

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_P))
		{
			PhysicsEngine::Instance()->SetPaused(!PhysicsEngine::Instance()->IsPaused());
		}

		engine_timer.GetTimedMS();

		if (!PhysicsEngine::Instance()->IsGameover()) {
			
			PhysicsEngine::Instance()->Feedback();
			ActionHandler::Instance()->Update(dt);
			PhysicsEngine::Instance()->Update(dt);

			float physics_ms = engine_timer.GetTimedMS();

			scene->UpdateScene(dt);

			if (PhysicsEngine::Instance()->IsGameover()) {
				continue;
			}

			float update_ms = engine_timer.GetTimedMS();

			//Debug Data
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Engine: %s (Press P to toggle)", PhysicsEngine::Instance()->IsPaused() ? "Paused" : "Enabled");
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "--------------------------------");
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Collision Detection Distance: " + std::to_string(PhysicsEngine::Instance()->GetCollisionDetectionDis()));
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Timestep : %5.2fms (%5.2f FPS)", PhysicsEngine::Instance()->GetUpdateTimestep() * 1000.0f, 1.0f / PhysicsEngine::Instance()->GetUpdateTimestep());
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Graphics Timestep: %5.2fms (%5.2f FPS)", dt * 1000.0f, 1.0f / dt);
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Update: %5.2fms", physics_ms);
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Scene Update  : %5.2fms", update_ms);

			//Render the Scene
			scene->RenderScene();

			PhysicsEngine::Instance()->PhysicsEngineClear();
		}
	}

	//Cleanup
	return Quit();
}