#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"
#include "dialog.h"
#include "mainwindow.h"
#include <thread>
//qt includes
#include "..\..\Qt\include\QtCore\QtPlugin"
#include "..\..\Qt\include\QtCore\qcoreapplication.h"
#include "..\..\Qt\include\QtWidgets\qapplication.h"
#include "..\..\Qt\include\QtWidgets\qstylefactory.h"
//end

Scene* scene = NULL;
Scene* Loading_scene = NULL;
Scene* Transition_scene = NULL;

bool isStillLoad = true;
bool isScoring = false;
bool GameStart = false;

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

void Loading()
{
	GameObjectMag* GOM_Loading = new GameObjectMag();

	GOM_Loading->SetID(0);
	Loading_scene = new MyScene(Window::GetWindow(), GOM_Loading);
	int i = 0;

	while (isStillLoad)
	{
		Loading_scene->RenderScene();
		Loading_scene->GetCamera()->SetYaw(i);
		NCLDebug::Log(Vector3(1, 1, 1), std::to_string(i));
		i++;
	}
}

void Scoring()
{
	GameObjectMag* GOM_Loading = new GameObjectMag();

	GOM_Loading->SetID(0);
	Loading_scene = new MyScene(Window::GetWindow(), GOM_Loading);
	int i = 0;

	while (isScoring)
	{
		Loading_scene->RenderScene();
		Loading_scene->GetCamera()->SetYaw(i);
		NCLDebug::Log(Vector3(1, 1, 1), std::to_string(i));
		i++;
	}
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

	GameObjectMag* GOM_Loading = new GameObjectMag();

	GOM_Loading->SetID(0);
	Transition_scene = new MyScene(Window::GetWindow(), GOM_Loading);
	
	thread loading(Loading);     // spawn new thread
	//thread Scoring(Scoring);

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
	
	isStillLoad = false;
	loading.join();
	
	//Create main game-loop
	Audio::AddSound({ 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel6, Audio::Start, 5);

	while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		

		float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f;	//How many milliseconds since last update?

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_P))
		{	
				PhysicsEngine::Instance()->SetPaused(!PhysicsEngine::Instance()->IsPaused());
		}
	
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_M)){
			Audio::AddSound({ 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, Audio::channel6, Audio::Start, 5);
		}
	
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_NUMPAD1)){
			if (PhysicsEngine::Instance()->GetDebug()){
				PhysicsEngine::Instance()->SetDebug(false);
				PhysicsEngine::Instance()->toggledebugdraw();
			}
			else{
				PhysicsEngine::Instance()->SetDebug(true);
				PhysicsEngine::Instance()->toggledebugdraw();
			}
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
			if (PhysicsEngine::Instance()->GetDebug()){
				/*NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Camera X:" + std::to_string((int)m_Camera->GetPosition().x)
					+ " Y:"
					+ std::to_string((int)m_Camera->GetPosition().y)
					+ " Z:"
					+ std::to_string((int)m_Camera->GetPosition().z)
					+ " Pitch:"p1
					+ std::to_string((float)m_Camera->GetPitch())
					+ " Yaw:"
					+ std::to_string((float)m_Camera->GetYaw())
					+ " cord:" 
					+ std::to_string((float)Proj_dir.x) + " "
					+ std::to_string((float)Proj_dir.y) + " "
					+ std::to_string((float)Proj_dir.z) + " "
					);*/

				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Engine: %s (Press P to toggle)", PhysicsEngine::Instance()->IsPaused() ? "Paused" : "Enabled");
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "--------------------------------");
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Collision Detection Distance: " + std::to_string(PhysicsEngine::Instance()->GetCollisionDetectionDis()));
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Timestep : %5.2fms (%5.2f FPS)", PhysicsEngine::Instance()->GetUpdateTimestep() * 1000.0f, 1.0f / PhysicsEngine::Instance()->GetUpdateTimestep());
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Graphics Timestep: %5.2fms (%5.2f FPS)", dt * 1000.0f, 1.0f / dt);
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Update: %5.2fms", physics_ms);
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Scene Update  : %5.2fms", update_ms);
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "CURRENT PLAYER: " + MainWindow::playername);
				//NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "TIME REMAINING: " + std::to_string(MyScene::timeremaining));
				NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "PowerUp  :" + AssetsManager::Player_1->GetPowerUpState());
			//	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "SCORE: BLUE " + std::to_string(ActionHandler::BLUESCORE) + " - " + std::to_string(ActionHandler::REDSCORE) + " RED");

			}
				//Render the Scene

			scene->RenderScene();

			{
				int SC = ActionHandler::Instance()->ScoreCheck();
				if (SC == 1) {
					for (int i = 0; i < 100; i++) {
						Transition_scene->RenderScene();
						//Scoring.join();
						isScoring = true;
						//isStillLoad = true;
						
						NCLDebug::DrawTextClipSpace(Vector4(-0.4f, 0.0f, 0.0f, 1.0f),
							40.0,
							"Red Team Score !",
							TEXTALIGN_LEFT,
							Vector4(1.0, 1.0, 1.0, 1.0));;
						Window::GetWindow().GetTimer()->GetTimedMS();
					}
					isScoring = false;
					isStillLoad = false;
				}
				else if (SC == 2) {
					for (int i = 0; i < 100; i++) {
						Transition_scene->RenderScene();
						//Scoring.join();
						isScoring = true;
						isStillLoad = true;

						NCLDebug::DrawTextClipSpace(Vector4(-0.4f, 0.0f, 0.0f, 1.0f),
							40.0f,
							"Blue Team Score !",
							TEXTALIGN_LEFT,
							Vector4(1.0, 1.0, 1.0, 1.0));
						Window::GetWindow().GetTimer()->GetTimedMS();
					}
					isScoring = false;
					isStillLoad = false;
				}
			}

			PhysicsEngine::Instance()->PhysicsEngineClear();
		}
	}

	//Cleanup
	AssetsManager::ReleaseMeshes();
	return Quit();
}