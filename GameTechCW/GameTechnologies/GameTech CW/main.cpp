#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"
#include "dialog.h"
#include "mainwindow.h"

//qt includes
#include "..\..\Qt\include\QtCore\QtPlugin"
#include "..\..\Qt\include\QtCore\qcoreapplication.h"
#include "..\..\Qt\include\QtWidgets\qapplication.h"
#include "..\..\Qt\include\QtWidgets\qstylefactory.h"
//end

Scene* scene = NULL;
Scene* Loading_scene = NULL;
Scene* Transition_scene = NULL;

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

//initialises qt window (called in main)
int main2(int argc, char *argv[])
{
	//QApp manages GUI control flow & settings
	QApplication a(argc, argv);

	//loads base window
	MainWindow w;
	w.setWindowTitle("Rocket League V2");
	w.setFixedSize(480, 400); //width x height

	//w.setWindowOpacity(0.2);
	w.setWindowIcon(QIcon("../../Qt/Icons/sicklogo.bmp"));
	w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	w.setAttribute(Qt::WA_TranslucentBackground);

	//finds primary screen height and width
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect screensize = screen->availableGeometry();
	int centreX = (screensize.width() - w.width()) / 2.f;
	int centreY = (screensize.height() - w.height()) / 2.f;

	////sets qt window to centre of screen
	QPoint screencoords;
	screencoords.setX(centreX);
	screencoords.setY(centreY);
	w.move(screencoords);

	w.show();

	return a.exec();
}

//= = = = = =
//ACCESS THE PLAYER'S STATS AT:
//MainWindow::playersize
//MainWindow::playerskill
//MainWindow::playertexture
//MainWindow::playername
//= = = = = =

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

	{
		GameObjectMag* GOM_Loading = new GameObjectMag();
		GOM_Loading->SetID(0);
		Loading_scene = new MyScene(Window::GetWindow(), GOM_Loading);
		Loading_scene->RenderScene();
	}


	//~~~QT SHIT~~~ (UNCOMMENT THIS IF THE WINDOW IS ANNOYING YOU)
	char *argv[] = { "windowinwindow", "arg1", "arg2", NULL };	//argv array with ptrs to strings, given values by the environment
	int argc = sizeof(argv) / sizeof(char*)-1; 	//argc is the no. of usable elements in argv inc. the program name
	main2(argc, argv); 	//call the qt window
	//~~~ END QT SHIT~~~

	//if they clicked the exit button, don't progress
	if (MainWindow::WannaExit){
		return Quit();
	}

	//Initialise the PhysicsEngine
	//Create GameObject Iterate Root Node upon which the GameObject List will be built
	PhysicsEngine::Instance();
	
	GameObjectMag* GOM_GamePlay = new GameObjectMag();
	//1 gameplay screen
	GOM_GamePlay->SetID(1);
	scene = new MyScene(Window::GetWindow(), GOM_GamePlay);

	//Initialise the ActionHandler Instnace
	ActionHandler::Instance();
	ActionHandler::Instance()->SetDefaultScene(scene);

	if (!scene->HasInitialised())
	{
		return Quit(true, "Renderer failed to initialise!");
	}

	GameTimer engine_timer;

	std::string PlayerName = MainWindow::playername;

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

			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "CURRENT PLAYER: " + MainWindow::playername);

			//Render the Scene
			scene->RenderScene();

			{
				int SC = ActionHandler::Instance()->ScoreCheck();
				if (SC == 1) {
					for (int i = 0; i < 50; i++) {
						Loading_scene->RenderScene();
					}
				}
				else if (SC == 2) {
					for (int i = 0; i < 50; i++) {
						Loading_scene->RenderScene();
					}
				}
			}

			PhysicsEngine::Instance()->PhysicsEngineClear();
		}
	}

	//Cleanup
	AssetsManager::ReleaseMeshes();
	return Quit();
}