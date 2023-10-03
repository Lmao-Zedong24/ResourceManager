#include "ResourceManager.h"

namespace OpenGl
{
	void ResourceManager::loadBasicResources()
	{
		auto& rm = *this;

		rm.Add<Texture>("png-clipart-barack-obama-barack-obama.png");
		rm.Add<Texture>("red.png");
		rm.Add<Texture>("green.png");
		rm.Add<Texture>("blue.png");
		rm.Add<Texture>("white.png");
		rm.Add<Texture>("grey.png");
		rm.Add<Texture>("black.png");
		rm.Add<Model>("Sting-Sword-lowpoly.obj");
		rm.Add<Model>("cube.obj");
		rm.Add<Model>("sphere.obj");
		rm.Add<Model>("cylindre.obj");

		for (int i = 2; i <= 10; i++) //Sting-Sword-lowpoly - Copy (2).obj
			rm.Add<Model>(std::string("Sting-Sword-lowpoly - Copy (") + std::to_string(i) + std::string(").obj"));

		for (auto& resource : m_resources)
			resource.second.get()->ThreadUnsafeSetup();
	}

	void ResourceManager::loadBasicScene(EntityManager* entityManager, PlayerGO** player, CameraG0** camGO)
	{
		auto& rm = *this;
		auto green = rm.getResource<Texture>("png-clipart-barack-obama-barack-obama.png");
		auto red = rm.getResource<Texture>("red.png");
		auto grey = rm.getResource<Texture>("grey.png");
		auto model1 = rm.getResource<Model>("Sting-Sword-lowpoly.obj"); 
		auto modelCube = rm.getResource<Model>("cube.obj");				
		auto modelSphere = rm.getResource<Model>("sphere.obj");			
		auto modelCylindre = rm.getResource<Model>("cylindre.obj");

		// Setup Entities
		EntityManager& em = *entityManager;

		GameObject* floor = em.Add<GameObject>("floor", nullptr, modelCube, grey);
		floor->GetLocalTransform().translate(0, -1.0f, 0);
		floor->GetLocalTransform().scale(100, 1, 100);

		GameObject* cube = em.Add<GameObject>("cube", nullptr, modelCube, green);
		GameObject* swrd = em.Add<GameObject>("swrd", nullptr, model1, green);

		cube->AddCapsuleChild(3, 0.5f, modelSphere,
			modelCylindre,
			red);
		swrd->AddCapsuleChild(1, 1, modelSphere,
			modelCylindre,
			red);

		auto& cbe = *em.Get<GameObject>("cube");
		auto& swoard1 = *em.Get<GameObject>("swrd");
		auto& swr = *em.Get<GameObject>("swrd");

		cbe.GetLocalTransform().scale(3);
		cbe.GetLocalTransform().translate(3, 0, -2);
		swr.GetLocalTransform().translate(-3, 0, -2);

		*player = em.Add<PlayerGO>("player", nullptr);
		(*player)->GetLocalTransform().translate(0, 4, 0);
		*camGO = (*player)->GetChild<CameraG0>(PlayerGO::CameraName);

		Transform& t1 = (*camGO)->AddChild<GameObject>("crosshair1", modelCube, red)->GetLocalTransform();
		t1.translate(0, 0, -0.5f);
		t1.scale(0.1f);
		t1.scale(1.0f, 0.06f, 0.06f);

		Transform& t2 = (*camGO)->AddChild<GameObject>("crosshair2", modelCube, red)->GetLocalTransform();
		t2.translate(0, 0, -0.5f);
		t2.scale(0.1f);
		t2.scale(0.06f, 1.0f, 0.06f);
	}


	void ResourceManager::Delete(const std::string& p_fileName)
	{
		if (this->m_resources.count(p_fileName) != 0)
			this->m_resources.at(p_fileName)->Delete();
	}

	void ResourceManager::DeleteAll()
	{
		this->m_resources.erase(m_resources.begin(), m_resources.end());
	}
}
