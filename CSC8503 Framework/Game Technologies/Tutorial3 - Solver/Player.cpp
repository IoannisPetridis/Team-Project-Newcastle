
#include "Player.h"
#include <nclgl\Window.h>
#include <nclgl\OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\CommonMeshes.h>
#include <ncltech\CuboidCollisionShape.h>
#include <iostream>
#include <mmsystem.h>
#include <windows.h>
Player::Player(const std::string& name) : GameObject(name)
{
	m_pMesh = new OBJMesh(MESHDIR"BatmobileCenter.obj");
	//m_pMesh->GenerateNormals();

	Physics()->SetPosition(Vector3(0.0f, 0.5f, 0.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.3f, 5.0f)));

	Physics()->SetIsGlobal(true);
	Physics()->SetIsWake(true);
	SetColour(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	GLuint dTex, nTex;

	//dTex = SOIL_load_OGL_texture(TEXTUREDIR"raptor.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//glBindTexture(GL_TEXTURE_2D, dTex);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
	//glBindTexture(GL_TEXTURE_2D, 0);

	//nTex = SOIL_load_OGL_texture(TEXTUREDIR"raptor_normal.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//glBindTexture(GL_TEXTURE_2D, nTex);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
	//glBindTexture(GL_TEXTURE_2D, 0);

	//m_pMesh->SetTexture(dTex);
	//m_pMesh->SetBumpMap(nTex);
}

Player::~Player()
{
	if (m_pMesh)
	{
		delete m_pMesh;
		m_pMesh = NULL;
	}
}

void Player::OnUpdateObject(float dt)
{
	float mv_speed = 20.f * dt;			//Meters per second
	const float rot_speed = 90.f * dt;			//Degrees per second
	Physics()->SetIsWake(true);

	if (Window::GetKeyboard()->KeyHeld(KEYBOARD_CONTROL))
	{
		mv_speed = 35.0f *dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN))
	{
		Physics()->SetPosition(Physics()->GetPosition() +
			Physics()->GetOrientation().ToMatrix3() * Vector3(0.0f, 0.0f, -mv_speed));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP))
	{
		Physics()->SetPosition(Physics()->GetPosition() +
		Physics()->GetOrientation().ToMatrix3()* Vector3(0.0f, 0.0f, mv_speed));
		
	}
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_UP))
	{
	PlaySound(TEXT("sound/drive.wav"), NULL, SND_ASYNC);
	}
	

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT))
	{
		Physics()->SetOrientation(Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), rot_speed));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT))
	{
		Physics()->SetOrientation(Physics()->GetOrientation() *
			Quaternion::AxisAngleToQuaterion(Vector3(0.0f, 1.0f, 0.0f), -rot_speed));
	}
}

void Player::OnRenderObject()
{
	GameObject::OnRenderObject();
	//fix child problem
	if (((ChildMeshInterface*)(m_pMesh))->childSize())
	{
		((OBJMesh*)(m_pMesh))->Draw();
	}
	else
		m_pMesh->Draw();
}