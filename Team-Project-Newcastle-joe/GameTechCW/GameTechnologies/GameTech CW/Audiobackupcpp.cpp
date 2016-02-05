//FMOD


//INITIALISEGL
//
//
///*result = FMOD::System_Create(&system2);
//result = system2->init(100, FMOD_INIT_NORMAL, extradriverdata);*/
//result = system2->createSound("drumloop.wav", FMOD_3D, 0, &sound1);
//result = sound1->setMode(FMOD_LOOP_NORMAL);
//vel = { 0.0f, 0.0f, 0.0f };
//result = sound1->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 1000.0f * DISTANCEFACTOR);
////result = system2->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
//
//result = system2->createSound("swish.wav", FMOD_DEFAULT, 0, &sound2);
//
//
//FMOD_VECTOR pos = { m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z };
//
//
//
//result = system2->playSound(sound1, 0, true, &channel1);
//result = system2->playSound(sound2, 0, true, &channel2);
//result = channel1->set3DAttributes(&pos, &vel);
//
//
//
//
//result = channel1->setPaused(false);
//
//



// UPDATE SCENE

//	{
//		//static float t = 0;
//		static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
//
//		FMOD_VECTOR forward = { Proj_dir.x, Proj_dir.y, Proj_dir.z };
//
//		Vector3 Right = Vector3::Cross(Proj_dir, Vector3(0.0f, 1.0f, 0.0f));
//		Vector3 Up = Vector3::Cross(Right, Proj_dir);
//
//		FMOD_VECTOR up = { Up.x, Up.y, Up.z };
//		FMOD_VECTOR playervel = { 0.0f, 0.0f, 0.0f };
//		Vector3 listenerposition = m_Camera->GetPosition();
//		FMOD_VECTOR listenerpos = { m_Camera->GetPosition().z, m_Camera->GetPosition().y, m_Camera->GetPosition().x };
//
//		//listenerpos.x = (float)sin(t * 0.05f) * 24.0f * DISTANCEFACTOR; // left right pingpong
//		const float LISTENDIST = 2.0f;
//		listenerpos.x = cos(msec * 0.5f) * 24.0f * DISTANCEFACTOR;// LISTENDIST;
//		listenerpos.y = sin(msec * 0.5f) * 24.0f * DISTANCEFACTOR;//* LISTENDIST;
//		listenerpos.z = sin(msec * 0.5f) * 24.0f * DISTANCEFACTOR; //*LISTENDIST;
//
//
//		playervel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
//		playervel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
//		playervel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);
//
//		lastpos = listenerpos;
//
//		result = system2->set3DListenerAttributes(0, &listenerpos, &playervel, &forward, &up);
//
//
//		//t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example
//
//	}
//
//result = system2->update();


//
