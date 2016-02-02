#pragma once

#include <nclgl\Mesh.h>
#include <ncltech\Scene.h>
#include <ncltech\SimpleMeshObject.h>

class MyScene : public Scene
{
public:
	MyScene(Window& window);
	~MyScene();

	bool InitialiseGL()	override;
	void RenderScene() override;
	void UpdateScene(float dt)  override;
	void shootBall();
	void shootBox();
	void shootPiramid();
	//static void move(GameObject* obj, Vector3 des);
	static void MyScene::move(GameObject* obj, Vector3 des)
	{
		obj->start = obj->Physics()->GetPosition();
		obj->end = des;
		obj->distance = (des - obj->start).Length();
		obj->direction = des - obj->start;
		obj->direction.Normalise();
		obj->isMove = true;
	};
	void shootHook();
	float speed = 0;
	float elapsed = 0.01f;
protected:
	float fade = 0.0f;
	bool isFadeIn = true;
	float totalFadeTime = 0;
	bool isDrawFade;
	GLuint			  m_TargetTexture;
	int score = 0;
	std::vector<Vector3> m_TrajectoryPoints;
	//SimpleMeshObject* AI = new SimpleMeshObject("AI");
};