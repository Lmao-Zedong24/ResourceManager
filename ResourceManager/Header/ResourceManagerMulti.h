#pragma once
#include "IResource.h"
#include "IResourceManager.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <future>

namespace Multi
{
	class ResourceManager : public IResourceManager
	{
	public:
		ResourceManager() = default;
		ResourceManager(const ResourceManager&) = default;
		ResourceManager(ResourceManager&&) = default;
		~ResourceManager() = default;

		template <typename T>
		std::future<IResource*> addRessource(const std::string& p_fileName);

		void loadBasicResources()override;
		void loadBasicScene(EntityManager* em, PlayerGO** player, CameraG0** camGO)override;

		template <typename T>
		T* getResource(const std::string& fileName);

		void Delete(const std::string& p_fileName);
		void DeleteAll()override;

	private:
		std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources;
		std::vector<std::thread> m_threads;
	};

}

