#include "PFAGM.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "ModelMulti.h"
#include "RigidBody.h"
#include "Angle.h"
#include "AllGO.h"
#include "Timer.h"
#include "ThreadPool.h"


using namespace LibMath::Literal;

namespace Multi
{
	void OpenGLGM::Init()
	{
		Stopwatch stopWatch;

		bool isMulti = false;
		while (true)
		{
			std::cout << "Press (s) for single thread, (m) for multi thread, (g) to start scene" << std::endl;
			char c;
			std::cin >> c;

			if (c == 's' || c == 'm')
			{
				if (isMulti = (c == 's'))
					m_resourceManager = std::make_unique<OpenGl::ResourceManager>();
				else if (isMulti = (c == 'm'))
				{
					m_resourceManager = std::make_unique<Multi::ResourceManager>();
					Multi::ThreadPoll::getInstance()->startMaxPollSize();
				}
				stopWatch.Start();
				m_resourceManager.get()->loadResources();
				std::cout << "Resources loaded in: " << stopWatch.Stop() << "ms" << std::endl;
				Multi::ThreadPoll::getInstance()->stop();
			}
			else if (c == 'g')
				break;
			else
				std::cout << "Enter valid input" << std::endl;
		}

		createScene(isMulti);
	}

	void OpenGLGM::Update()
	{
		if (m_currentCam)
		{
			BackGorund();
			m_entityManager.Update();

			m_entityManager.DrawAllEntities(m_shader, *m_currentCam);
		}
	}

	void OpenGLGM::PlayerInputs(GLFWwindow* p_window)
	{
		// TODO : should be in input scaner
		PlayerGO* player = m_entityManager.Get<PlayerGO>("player");
		player->Inputs(p_window);
	}

	OpenGLGM* OpenGLGM::GetInstance()
	{
		if (!m_PFAGM)
			m_PFAGM = std::make_unique<OpenGLGM>();

		return m_PFAGM.get();
	}

	void OpenGLGM::BackGorund()
	{
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}



	void OpenGLGM::createScene(bool isMulti)
	{
		Texture* green, *red, *grey, *blue, *white, *blackT, *joe;
		Model* model1, *modelCube, *sphere, *phone;

		if (!isMulti)
		{
			auto& manager = *(OpenGl::ResourceManager*)m_resourceManager.get();
			green = manager.getResource<Texture>("green.png");
			red = manager.getResource<Texture>("red.png");
			grey = manager.getResource<Texture>("grey.png");
			blue = manager.getResource<Texture>("blue.png");
			white = manager.getResource<Texture>("white.png");
			blackT = manager.getResource<Texture>("phoneTexture.png");
			joe = manager.getResource<Texture>("png-clipart-barack-obama-barack-obama.png");
			model1 = manager.getResource<Model>("Sting-Sword-lowpoly.obj");
			modelCube = manager.getResource<Model>("cube.obj");
			sphere = manager.getResource<Model>("sphere.obj");
			phone = manager.getResource<Model>("phone2.obj");
		}
		else
		{
			auto& manager = *(Multi::ResourceManager*)m_resourceManager.get();
			green = manager.getResource<Texture>("green.png");
			red = manager.getResource<Texture>("red.png");
			grey = manager.getResource<Texture>("grey.png");
			blue = manager.getResource<Texture>("blue.png");
			white = manager.getResource<Texture>("white.png");
			blackT = manager.getResource<Texture>("phoneTexture.png");
			joe = manager.getResource<Texture>("png-clipart-barack-obama-barack-obama.png");
			model1 = manager.getResource<Model>("Sting-Sword-lowpoly.obj");
			modelCube = manager.getResource<Model>("cube.obj");
			sphere = manager.getResource<Model>("sphere.obj");
			phone = manager.getResource<Model>("phone2.obj");
		}


		m_collisionManager = OpenGl::CollisionManager::GetInstance();

		//floor
		{
			LibMath::Vector3 pos(0, -10.0f, 0);
			LibMath::Vector3 dim(120, 4, 120);
			RigidGO* floor = m_entityManager.Add<RigidGO>("floor", nullptr, modelCube, white);
			floor->GetLocalTransform().translate(pos);
			floor->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

			floor->SetLayer(GameObject::FetchLayer("floor"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));

			floor->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(floor), colVec));
		}

		//wall gray
		{
			std::vector<std::pair<LibMath::Vector3, LibMath::Vector3>> dimPos =
			{
				{ LibMath::Vector3(100, 60, 4), LibMath::Vector3(0, 0, 50) },
				{ LibMath::Vector3(4, 60, 100), LibMath::Vector3(-50, 0, 0) },
				{ LibMath::Vector3(100, 60, 4), LibMath::Vector3(0, 0, -50) },
				{ LibMath::Vector3(4, 60, 100), LibMath::Vector3(50, 0, 0) },
				{ LibMath::Vector3(80, 60, 8),  LibMath::Vector3(-25, 0, 0) }
			};
			int i = 1;
			for (auto& pair : dimPos)
			{
				LibMath::Vector3& dim = pair.first;
				LibMath::Vector3& pos = pair.second;
				std::stringstream name("wall");
				name << i;
				RigidGO* wall = m_entityManager.Add<RigidGO>(name.str(), nullptr, modelCube, grey);
				wall->GetLocalTransform().translate(pos);
				wall->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

				wall->SetLayer(GameObject::FetchLayer("wall"));

				std::vector<std::unique_ptr<ICollidable>> colVec;
				colVec.emplace_back(std::make_unique<BoxCollider>(dim, pos));

				wall->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(wall), colVec));
				i++;
			}
		}

		//with color
		{
			LibMath::Vector3 pos(-30, 6, 20);
			LibMath::Vector3 dim(1, 20, 50);
			RigidGO* wall = m_entityManager.Add<RigidGO>("wallB", nullptr, modelCube, green);
			wall->GetLocalTransform().translate(pos);
			wall->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

			wall->SetLayer(GameObject::FetchLayer("wall"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));

			wall->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(wall), colVec));
			wall->SetColor(GameObject::Color::GREEN);
		}

		{
			LibMath::Vector3 pos(-20, 6, 30);
			LibMath::Vector3 dim(1, 20, 50);
			RigidGO* wall = m_entityManager.Add<RigidGO>("wallG", nullptr, modelCube, blue);
			wall->GetLocalTransform().translate(pos);
			wall->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

			wall->SetLayer(GameObject::FetchLayer("wall"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));

			wall->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(wall), colVec));
			wall->SetColor(GameObject::Color::BLUE);
		}

		//color cube 1
		{
			LibMath::Vector3 pos(-10, 0, -20);
			LibMath::Vector3 dim(4, 4, 4);
			RigidLerpGO* cube = m_entityManager.Add<RigidLerpGO>("cube1", nullptr, modelCube, green);
			cube->GetLocalTransform().translate(pos);
			cube->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

			cube->SetLayer(GameObject::FetchLayer("cubeColor"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));

			cube->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(cube), colVec));

			cube->SetColor(GameObject::Color::GREEN);
			//cube->SetupLerpPos(	cube->GetLocalTransform().getPosition(), 
			//					cube->GetLocalTransform().getPosition() + LibMath::Vector3(0, 5, 0));

			cube->SetupLerpDir(LibMath::Vector3(0, 5, 0));
		}

		//color cube 2
		{
			LibMath::Vector3 pos(-25, -4, 20);
			LibMath::Vector3 dim(4, 4, 4);
			RigidGO* cube = m_entityManager.Add<RigidGO>("cube3", nullptr, modelCube, blue);
			cube->GetLocalTransform().translate(pos);
			cube->GetLocalTransform().scale(dim.m_x, dim.m_y, dim.m_z);

			cube->SetLayer(GameObject::FetchLayer("cubeColor"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));

			cube->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(cube), colVec));

			cube->SetColor(GameObject::Color::BLUE);
		}

		//child tests
		{
			GameObject* swrd = m_entityManager.Add<GameObject>("swrd", nullptr, model1, red);
			auto& swr = *m_entityManager.Get<GameObject>("swrd");

			swr.GetLocalTransform().translate(-35, 6, 25);
			swr.GetLocalTransform().rotateEulerAngles(LibMath::Degree(90), LibMath::Degree(0), LibMath::Degree(0));
		}

		//Player
		PlayerGO* player = m_entityManager.Add<PlayerGO>("player", nullptr);
		{
			LibMath::Vector3 pos(40, 0, 40);
			LibMath::Vector3 dim(2, 8, 2);

			player->GetLocalTransform().translate(pos);
			player->SetLayer(GameObject::FetchLayer("player"));

			auto boxCol(std::make_unique<BoxCollider>(dim, pos));
			std::vector<std::unique_ptr<ICollidable>> colVec;
			colVec.push_back(std::move(boxCol));


			player->SetRigidBodyCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(player), colVec));
			player->SetRigidBodyFuncs();

			auto rayCol(std::make_unique<CapsuleCollider>(LibMath::Vector3(0, 0, 0),
														  LibMath::Vector3(0, 0, -25),
														  0.0f,
														  player->GetLocalTransform().getTransform()));
			colVec.push_back(std::move(rayCol));
			player->SetRayCastCollider(m_collisionManager->AddCollider(dynamic_cast<GameObject*>(player), colVec));
			player->SetRayCastFuncs();

			player->SetColor(GameObject::Color::RED);
		}

		//CAMERA
		CameraGO* camGO = player->GetChild<CameraGO>(PlayerGO::CameraName);

		// HUD
		{
			//CROSSHAIR
			Transform& t1 = camGO->AddChild<GameObject>("crosshair1", modelCube, red)->GetLocalTransform();
			t1.translate(0, 0, -0.5f);
			t1.scale(0.05f);
			t1.scale(1.0f, 0.06f, 0.06f);

			Transform& t2 = camGO->AddChild<GameObject>("crosshair2", modelCube, red)->GetLocalTransform();
			t2.translate(0, 0, -0.5f);
			t2.scale(0.05f);
			t2.scale(0.06f, 1.0f, 0.06f);

			//PHONE
			Transform& pho = camGO->AddChild<GameObject>("phone", phone, blackT)->GetLocalTransform();
			pho.translate(0.2f, -0.2f, -0.2f);
			pho.scale(0.004f);
			pho.rotateEulerAngles(-90_deg, -10_deg, 30_deg);

			GameObject* phone = camGO->AddChild<GameObject>("phoneColor", sphere, red);
			auto& phoTrans = phone->GetLocalTransform();
			phoTrans.scale(0.12f);
			phoTrans.translate(2.2f, -2.2f, -2.3f);

			phone->SetColor(GameObject::Color::RED);
		}

		//SET CURENT CAMERA
		camGO->Update();
		m_currentCam = &camGO->GetCamera();

		//SET CURRENT SHADER
		m_shader.Initialize("shaderBuffer.txt");
		m_shader.Link();
	}
}
