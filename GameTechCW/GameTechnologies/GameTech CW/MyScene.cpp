#include "MyScene.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#define PI 3.14159265f

MyScene::MyScene(Window& window) : Scene(window)
{
	if (init == true)	{}
		init = InitialiseGL();

	UpdateWorldMatrices(m_RootGameObject, Matrix4());

	GOM = new GameObjectMag();	//initialize the GOM

	PhysicsEngine::Instance()->SetUpdateTimestep(1.0f / 60.0f);		//60 Updates per second
}

MyScene::~MyScene()
{
	//delete any texture used
	if (m_TargetTexture)
	{
		glDeleteTextures(1, &m_TargetTexture);
		m_TargetTexture = NULL;
	}
}

bool MyScene::InitialiseGL()
{

	m_Camera->SetPosition(Vector3(-10.0f, 4.0f, 0.0f));
	m_Camera->SetYaw(-90.0f);

	//Fucntionality
	ai_toggle = true;
	travese_toggle = true;
	gameover = false;
	ai_state = true;
	cooldown = false;
	ballnum = 50;
	diff = 1;
	T_counter = 0;
	DebugMode = 2;
	Str_c = 0;
	score = 0;
	friction = 0.5f;
	start_strong = -1.0f;
	timer = 0.0f;
	filename = "leaderboard.txt";
	//end

	std::ifstream f(filename.c_str(), std::ios::in);
	if (f) {
		while (!f.eof()) {
			std::string name;
			std::string score;
			f >> name;
			f >> score;
			LB_name.push_back(name);
			LB_score.push_back(score);
		}
	}
	f.close();

	Proj_dir = Vector3(.0f, .0f, .0f);
	planenormal = Vector3(-1.0f, 0.0f, 0.0f);

	PhysicsEngine::Instance()->SetGravity(Vector3(0.0f, -9.81f, 0.0f));		
	PhysicsEngine::Instance()->SetDampingFactor(0.988f);						
	
	//Plan the GameObject
	GOM->GOMInit(this, 
		m_Sphere,
		throw_S,
		target,
		goal,
		plane);

	return true;
}

void MyScene::UpdateScene(float msec)
{
	Scene::UpdateScene(msec);

	//Track Camera FOV direction
	Proj_dir.x = -sin(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	//rotate goal
	if (!PhysicsEngine::Instance()->IsPaused())
	{	
		//rotate the physical and graphical representation of goal simultaneously
		GameObject* temp_1 = m_RootGameObject->FindGameObject("goal");
		Quaternion rot = temp_1->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 1.0f);
		temp_1->Physics()->SetOrientation(rot);	
	
		temp_1 = m_RootGameObject->FindGameObject("goal_shape");
		rot = temp_1->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 1.0f);
		temp_1->Physics()->SetOrientation(rot);

		temp_1 = m_RootGameObject->FindGameObject("bulb");
		rot = temp_1->Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 1.0f);
		temp_1->Physics()->SetOrientation(rot);
	
		for (auto temp_1 : subshapes) {
			rot = temp_1->Physics()->GetOrientation() *
				Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), 1.0f);
			temp_1->Physics()->SetOrientation(rot);
		}
	}
	//end

	//Create Projectile with cooldown timer when Z pressed
	if (cooldown) {
		timer += engine_timer.GetTimedMS() / 1000.0f;
		if (timer > 0.5f) {
			timer = 0.0f;
			cooldown = false;
		}
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Z) && !cooldown) {
		cooldown = true;

		throw_S = new SimpleMeshObject("ThrowSphere");
		throw_S->SetMesh(AssetsManager::Sphere(), false);
		throw_S->SetTexture(AssetsManager::m_ThrowTex, false);
		throw_S->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
		throw_S->SetColour(Vector4(1.0f, 0.3f, 0.5f, 1.0f));
		throw_S->SetBoundingRadius(1.0f);

		throw_S->Physics()->name = "TS";
		throw_S->Physics()->SetInverseMass(1.0f);
		throw_S->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
		throw_S->Physics()->SetInverseInertia(throw_S->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));
		throw_S->Physics()->SetLinearVelocity(Proj_dir * 20.0f);
		throw_S->Physics()->SetPosition(m_Camera->GetPosition() + (Proj_dir * 1.2f));

		m_RootGameObject->FindGameObject("gk")->Physics()->colarch[0] = false;

		this->AddGameObject(throw_S);
		T_counter++;
		ballnum--;

		//tracking the num of balls on screen and make it less than 5
		if (T_counter > 5) {
			GameObject* temp = m_RootGameObject->FindGameObject("ThrowSphere");
			auto found_loc = std::find(m_RootGameObject->GetChildren().begin(),
				m_RootGameObject->GetChildren().end(), temp);
			if (found_loc != m_RootGameObject->GetChildren().end())
			{
				m_RootGameObject->GetChildren().erase(found_loc);
			}
			PhysicsEngine::Instance()->RemovePhysicsObject(temp->Physics());
		}
	}

	//charged strong atk
	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_Q)) {
		if (start_strong == -1.0f) {
			start_strong = 20.0f;
		}
		start_strong += (engine_timer.GetTimedMS() / 1000.0f) * 12.0f;
		//strongest atk at 40.0f
		start_strong = min(start_strong, 40.0f);
		if (start_strong != 40.0f) {
			NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "ATK Charging: " + std::to_string(start_strong));
		}
	}
	if (!Window::GetKeyboard()->KeyHeld(KEYBOARD_Q) 
		&& start_strong > 0.0f) {
		throw_S = new SimpleMeshObject("ThrowSphere");
		throw_S->SetMesh(AssetsManager::Sphere(), false);
		throw_S->SetTexture(AssetsManager::m_ThrowTex, false);
		throw_S->SetLocalTransform(Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
		throw_S->SetColour(Vector4(1.0f, 0.3f, 0.5f, 1.0f));
		throw_S->SetBoundingRadius(1.0f);

		throw_S->Physics()->name = "TS";
		m_RootGameObject->FindGameObject("gk")->Physics()->colarch[0] = false;

		throw_S->Physics()->SetInverseMass(1.0f);
		throw_S->Physics()->SetCollisionShape(new SphereCollisionShape(0.5f));
		throw_S->Physics()->SetInverseInertia(throw_S->Physics()->GetCollisionShape()->BuildInverseInertia(1.0f));

		throw_S->Physics()->SetLinearVelocity(Proj_dir * start_strong);
		throw_S->Physics()->SetPosition(m_Camera->GetPosition() + (Proj_dir * 1.2f));

		this->AddGameObject(throw_S);

		T_counter++;
		ballnum--;
		if (T_counter > 5) {
			GameObject* temp = m_RootGameObject->FindGameObject("ThrowSphere");
			auto found_loc = std::find(m_RootGameObject->GetChildren().begin(),
				m_RootGameObject->GetChildren().end(), temp);
			if (found_loc != m_RootGameObject->GetChildren().end())
			{
				m_RootGameObject->GetChildren().erase(found_loc);
			}
			PhysicsEngine::Instance()->RemovePhysicsObject(temp->Physics());
		}
		start_strong = -1.0f;
	}
	

	//Sphere-Sphere Collision
	{
		GameObject* temp = m_RootGameObject->FindGameObject("mSphere");
		CollisionData coldata;
		if (CollisionDetection::Instance()->CheckSphereSphereCollision(
			temp->Physics(), throw_S->Physics(),
			temp->Physics()->GetCollisionShape(),
			throw_S->Physics()->GetCollisionShape(),
			&coldata))
		{
			NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "SPHERE SPHERE COLLISION");
			if (temp->Physics()->GetLinearVelocity() == Vector3(0.0f, 0.0f, 0.0f)){
				temp->Physics()->SetLinearVelocity(throw_S->Physics()->GetLinearVelocity() * 0.8f);
			}
			else {
				temp->Physics()->SetLinearVelocity(temp->Physics()->GetLinearVelocity());
			}
			throw_S->Physics()->SetLinearVelocity(-throw_S->Physics()->GetLinearVelocity() * 0.8f);
		}
	}

	//Sphere-Plane Collision
	{
		Vector3 temp_pos = throw_S->Physics()->GetPosition();
		if ((temp_pos.y <= 12.0f && temp_pos.y >= 8.0f)
			&& (temp_pos.z >= -24.0f && temp_pos.z <= -20.0f)) {
			bool plane_hit_chekc = false;
			if (abs(Vector3::Dot(throw_S->Physics()->GetPosition(),
				plane->GetNormal()) - plane->GetDistance()) 
				<= (throw_S->GetBoundingRadius())) {
				plane_hit_chekc = true;
			}
			if (plane_hit_chekc) {
				NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "PLANE SPHERE COLLISION");
				throw_S->Physics()->SetLinearVelocity(-throw_S->Physics()->GetLinearVelocity());
			}
		}
	}

	//debug mode
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_M)) {
		DebugMode = (DebugMode + 1) % 3;
		switch (DebugMode)
		{
		case 0:
			for (auto child : m_RootGameObject->GetChildren()) {
				Vector4 colour = child->GetColour();
				if (colour.w == 0.0f) {
					colour = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
				}
				colour.w = 0.0f;
				child->SetColour(colour);
				Scene::SetClearColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			}
			PhysicsEngine::Instance()->toggledebugdraw();
			NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "DebugMode 0");
			break;
		case 1:
			for (auto child : m_RootGameObject->GetChildren()) {
				Vector4 colour = child->GetColour();
				if (colour.ToVector3() == Vector3(0.0f, 0.0f, 0.0f)) {
					child->SetColour(colour);
				}
				else{
					colour.w = 1.0f;
					child->SetColour(colour);
				}
			}
			NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "DebugMode 1");
			break;
		case 2:
			PhysicsEngine::Instance()->toggledebugdraw();
			Scene::SetClearColor(Vector4(0.6f, 0.6f, 0.6f, 1.f));
			NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "DebugMode 2");
			break;
		}
	}
	//to update debugmode 0 after it being launched the first time
	if (DebugMode == 0) {
		for (auto child : m_RootGameObject->GetChildren()) {
			Vector4 colour = child->GetColour();
			colour.w = 0.0f;
			child->SetColour(colour);
		}
	}
	//complete

	//AI
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_K)) {
		ai_toggle = !ai_toggle;
	}
	if (ai_toggle){
		GameObject* temp = m_RootGameObject;
		GameObject* gk = m_RootGameObject->FindGameObject("gk");

		//Idle State detection
		float dist = (gk->Physics()->GetPosition() - m_Camera->GetPosition()).Length();
		if (std::abs(dist) > 12.0f) {
			ai_state = false;
		}
		else { ai_state = true; }

		//Main AI update loop
		if (ai_state) {
			//Only check if it is collided with projectile but other objects in scene
			for (auto child : m_RootGameObject->GetChildren()) {
				if (child->Physics()->name == "TS") {
					temp = child;
				}
			}

			Vector3 ball_pos = temp->Physics()->GetPosition();
			Vector3 GK_pos = m_RootGameObject->FindGameObject("gk")->Physics()->GetPosition();

			//Only block balls that is approaching the goal yet not pass the goal keeper
			if ((ball_pos.x * ball_pos.x + ball_pos.z * ball_pos.z) >
				(GK_pos.x * GK_pos.x + GK_pos.z * GK_pos.z)
				&& ball_pos.y > GK_pos.y
				&& ball_pos.x < GK_pos.x) {
				CollisionData coldata;

				//Only block balls that have not collided with goal yet
				if (CollisionDetection::Instance()->CheckCollision(
					temp->Physics(), gk->Physics(),
					temp->Physics()->GetCollisionShape(),
					gk->Physics()->GetCollisionShape(),
					&coldata))
				{
					gk->Physics()->colarch[0] = true;
				}

				//Make goal keeper try to block approaching projectile
				if (gk->Physics()->colarch[0] != true) {
					m_RootGameObject->FindGameObject("gk")->Physics()->SetForce(ball_pos *
						min((float(score) + 2000.0f) / 16.0f, 800.0f));
					diff = int(min((float(score) + 2000.0f) / 16.0f, 800.0f)) / 100;
				}
				else {
					m_RootGameObject->FindGameObject("gk")->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
				}
			}
			else {
				m_RootGameObject->FindGameObject("gk")->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
			}

			//Set the position of one of distance constraint point that is bound to goal keeper 
			//to appropriate point along the distance vector between goal and camera
			m_RootGameObject->FindGameObject("point")->Physics()->SetPosition(
				Target_Pos - m_Camera->GetPosition() * -0.4f);
		}
		//when goal keeper in idle, push it back to its spawn position
		else {
			if (gk->Physics()->GetPosition() != GK_Init_Pos) {
				gk->Physics()->SetLinearVelocity(GK_Init_Pos * 0.05f);
			}
			else {
				gk->Physics()->SetLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
			}
		}
	}
	//complete

	//traverse
	//Additional code starts on line 246 in PhysicsEngine.cpp
	if (!PhysicsEngine::Instance()->IsPaused()) {
		GameObject* bulb = m_RootGameObject->FindGameObject("bulb");

		GameObject* temp_color = m_RootGameObject->FindGameObject("goal_shape");	//graphical rep
		GameObject* temp = m_RootGameObject->FindGameObject("goal");				//physical rep 
		Vector4 colour = temp_color->GetColour();

		if (colour.w <= 0) travese_toggle = false;
		if (colour.w >= 1) travese_toggle = true;

		if (travese_toggle) {
			colour.w -= msec / 20.0f;
			temp->Physics()->SetFriction(colour.w * friction);
		}
		if (!travese_toggle) {
			colour.w += msec / 20.0f;
			temp->Physics()->SetFriction(colour.w * friction);
		}

		if (colour.w < 0.7f) {
			//turn off manifold building and collision detection
			std::function<bool(PhysicsObject*)> callback = [](PhysicsObject* colliding_obj){ return false; };
			temp->Physics()->SetOnCollisionCallback(callback);
		}

		CollisionData coldata;
		for (auto child : m_RootGameObject->GetChildren()) {
			if (child->FindGameObject("ThrowSphere") == child) {
				if (child->Physics()->GetCollisionShape() != NULL) {
					if (CollisionDetection::Instance()->CheckCollision(
						bulb->Physics(), child->Physics(),
						bulb->Physics()->GetCollisionShape(),
						child->Physics()->GetCollisionShape(),
						&coldata)){
						score += 1500;
						NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "Hit Bulb, Score 1500!");
					}

					if (CollisionDetection::Instance()->CheckCollision(
						temp->Physics(), child->Physics(),
						temp->Physics()->GetCollisionShape(),
						child->Physics()->GetCollisionShape(),
						&coldata)) {

						if (child->Physics()->colarch.empty()) {
							child->Physics()->colarch.push_back(true);
						}
						else {
							child->Physics()->score_counter += 5;
							score += 5;
							NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "Ball Touched target, you got bouns score "
								+ std::to_string(child->Physics()->score_counter)
								+ " !");
							if (child->Physics()->colarch[child->Physics()->colarch.size() - 1] != true) {
								child->Physics()->colarch.push_back(true);
							}
						}
					}

					else {
						if (child->Physics()->colarch.empty()) {
							child->Physics()->colarch.push_back(false);
						}
						else {
							if (child->Physics()->colarch[child->Physics()->colarch.size() - 1] != false) {
								child->Physics()->colarch.push_back(false);
							}
						}
					}

					if (child->Physics()->colarch.size() == 3) {
						//make colarch.size = 4 to exclude this child out afterwards for good
						child->Physics()->colarch.push_back(false); 

						child->Physics()->SetForce(Vector3(0.0f, 0.0f, 0.0f));
						NCLDebug::Log(Vector3(1.0f, 0.0f, 0.0f), "Ball bounded or traversed through the target, Score 1000!");
						score += 1000;
					}

					if (child->Physics()->colarch.size() == 2 && temp_color->GetColour().w >= 1.0f) {
						//make colarch.size = 4 to exclude this child out afterwards for good
						child->Physics()->colarch.push_back(false);
						child->Physics()->colarch.push_back(false);

						NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "Ball Traped inside! Game Over!");
						gameover = true;
					}
					}
				}
			}
	temp_color->SetColour(colour);
	}
	//end

	//Check if balls were used up
	if (ballnum == -1 && gameover == false) {
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "Used up all the balls! Game Over!.");
		gameover = true;
	}

	//Clean Exit
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_X)) {
		gameover = true;
	}
	if (gameover) {
		NCLDebug::Log(Vector3(1.0f, 1.0f, 0.0f), "Game Over!");
		PhysicsEngine::Instance()->SetGameover(true);
		for (GameObject* obj : m_RootGameObject->GetChildren())
		{
			delete obj;
		}
		m_RootGameObject->GetChildren().clear();
		delete m_RootGameObject;
		PhysicsEngine::Instance()->Release();
		PhysicsEngine::Instance()->SetGameover(true);

		m_RootGameObject = new GameObject();	//root is created here
		m_RootGameObject->SetScene(this);
	}
	//end

	//Generate LeaderBoard
	if (gameover) {
		gameover = false;
		string pname;
		string temp_name_1, temp_score_1, temp_name_2, temp_score_2;
		std::ofstream f(filename.c_str(), std::ios::out);
		for (unsigned int i = 0; i < LB_score.size(); i++) {
			if (atoi(LB_score[i].c_str()) < score) {
				for (unsigned int j = i; j < LB_score.size() - 1; j++) {
					if (i == j) {
						temp_score_1 = LB_score[j + 1]; temp_name_1 = LB_name[j + 1];
						LB_score[j + 1] = LB_score[j];
						LB_name[j + 1] = LB_name[j];
					}
					else {
						temp_score_2 = LB_score[j + 1]; temp_name_2 = LB_name[j + 1];
						LB_score[j + 1] = temp_score_1;
						LB_name[j + 1] = temp_name_1;
						temp_score_1 = temp_score_2; temp_name_1 = temp_name_2;
					}
				}
				LB_score[i] = std::to_string(score);
				system("CLS");
				std::cout << "Please Enter your name: ";
				std::cin >> pname;
				LB_name[i] = pname;
				std::cout << "Please Return to Graphic Interface.";
				break;
			}
		}
		if (f) {
			for (unsigned int i = 0; i < LB_score.size(); i++) {
				f << LB_name[i]; f << "\t";
				if (i == LB_score.size() - 1) {
					f << LB_score[i];
				}
				else {
					f << LB_score[i]; f << "\n";
				}
			}
		}
		f.close();
	}
	//complete

	//NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Camera X:" + std::to_string((int)m_Camera->GetPosition().x)
	//	+ " Y:"
	//	+ std::to_string((int)m_Camera->GetPosition().y)
	//	+ " Z:"
	//	+ std::to_string((int)m_Camera->GetPosition().z)
	//	+ " Pitch:"
	//	+ std::to_string((float)m_Camera->GetPitch())
	//	+ " Yaw:"
	//	+ std::to_string((float)m_Camera->GetYaw())
	//	+ " cord:" 
	//	+ std::to_string((float)Proj_dir.x) + " "
	//	+ std::to_string((float)Proj_dir.y) + " "
	//	+ std::to_string((float)Proj_dir.z) + " "
	//	);
	
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.0f, 0.0f, 1.0f), "Press Z Regular ATK(0.5s Cooldown), Hold Q Charged ATK");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.0f, 0.0f, 1.0f), "Score: " + std::to_string(score));
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.0f, 0.0f, 1.0f), "Ball Left: " + std::to_string(ballnum));
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.0f, 0.0f, 1.0f), "AI Difficulty: " +
		std::to_string(diff));
	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "--------------------------------");
	NCLDebug::AddStatusEntry(Vector4(0.9f, 0.4f, 0.6f, 1.0f), "LeaderBoard:"); 
	NCLDebug::AddStatusEntry(Vector4(0.9f, 0.4f, 0.6f, 1.0f), "Rank\tName\tScore");
	for (unsigned int i = 0; i < LB_name.size(); i++) {
		NCLDebug::AddStatusEntry(Vector4(0.9f, 0.4f, 0.6f, 1.0f), "No." + std::to_string(i + 1) + "\t"
			+ LB_name[i] + "\t" + LB_score[i]);
	}
	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "--------------------------------");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Goal Keeper AI: %s (Press K to toggle)",
		ai_toggle ? "Enabled" : "Disabled");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Goal Keeper AI State: %s",
		ai_state ? "Active" : "Idle");
}

void MyScene::RenderScene()
{
	Scene::RenderScene();
}



