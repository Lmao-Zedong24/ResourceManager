#include "ResourceManager.h"
#include "ResourceManagerMulti.h"
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "ThreadPool.h"
#include "EntityManager.h"
#include "Texture.h"
#include <future>

namespace Multi
{
	void ResourceManager::Delete(const std::string& p_fileName)
	{
		if (this->m_resources.count(p_fileName) != 0)
			m_resources.erase(p_fileName);
	}

	void ResourceManager::DeleteAll()
	{
		this->m_resources.erase(m_resources.begin(), m_resources.end());
	}

	ResourceManager::ResourceManager()
	{
		auto tp = ThreadPoll::getInstance();
		m_poolId = tp->getPoolId();
	}

	void ResourceManager::loadBasicResources()
	{
		auto& rm = *this;

		rm.addRessource<Texture>("png-clipart-barack-obama-barack-obama.png");
		rm.addRessource<Texture>("red.png");
		rm.addRessource<Texture>("green.png");
		rm.addRessource<Texture>("blue.png");
		rm.addRessource<Texture>("white.png");
		rm.addRessource<Texture>("grey.png");
		rm.addRessource<Texture>("black.png");
		rm.addRessource<Model>("Sting-Sword-lowpoly.obj");
		rm.addRessource<Model>("cube.obj");
		rm.addRessource<Model>("sphere.obj");
		rm.addRessource<Model>("cylindre.obj");

		for (int i = 2; i <= 10; i++) //Sting-Sword-lowpoly - Copy (2).obj
			rm.addRessource<Model>(std::string("Sting-Sword-lowpoly - Copy (") + std::to_string(i) + std::string(").obj"));

		ThreadPoll::getInstance()->waitUntilTasksAreDone(m_poolId);
		ThreadPoll::getInstance()->stop();

		//unsafe functions
		for (auto& resource : m_resources)
			resource.second.get()->ThreadUnsafeSetup();
	}

	void ResourceManager::loadBasicScene(EntityManager* entityManager, PlayerGO** player, CameraG0** camGO)
	{
		auto& rm = *this;
		auto green = rm.getResource<Texture>("png-clipart-barack-obama-barack-obama.png");
		auto red = rm.getResource<Texture>("red.png");
		auto grey = rm.getResource<Texture>("grey.png");
		auto model1 = rm.getResource<Model>("Sting-Sword-lowpoly.obj"); model1->SetVAO();
		auto modelCube = rm.getResource<Model>("cube.obj");				modelCube->SetVAO();
		auto modelSphere = rm.getResource<Model>("sphere.obj");			modelSphere->SetVAO();
		auto modelCylindre = rm.getResource<Model>("cylindre.obj");		modelCylindre->SetVAO();

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

	template<typename T>
	void ResourceManager::addRessource(const std::string& fileName)
	{
		if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
			return;

		if (this->m_resources.count(fileName) != 0)
			this->m_resources.erase(fileName);

		m_resources.emplace(fileName, std::make_unique<T>());
		auto resource = m_resources[fileName].get();

		//auto llamda = [] {}
		std::function<void()> func = std::bind(&IResource::Initialize, resource, fileName);
		Multi::ThreadPoll::getInstance()->addFuncToThread(func, m_poolId);
	};

	template<typename T>
	inline T* ResourceManager::getResource(const std::string& fileName)
	{
		if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
			return nullptr;

		if (m_resources.count(fileName) != 0)
			return dynamic_cast<T*>(m_resources.at(fileName).get());

		return nullptr;
	}
}