#pragma once
#include "IResource.h"
#include "IResourceManager.h"
#include "ThreadPool.h"
#include "ThreadableResource.h"
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
		std::future<IResource*> addRessource(const std::string& fileName)
		{
			if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
				throw "Template not an IResource\n";

			if (this->m_resources.count(fileName) != 0)
				this->m_resources.erase(fileName);

			m_resources.emplace(fileName, std::make_unique<T>());
			auto resource = m_resources[fileName].get();

			std::promise<IResource*>	promise;
			auto						future = promise.get_future();

			//if (static_assert(std::is_base_of_v<ThreadableResource, T>)) //break compiler if false
			if constexpr (std::is_base_of_v<ThreadableResource, T>)
				dynamic_cast<T*>(resource)->movePromise(std::move(promise));
			else
				promise.set_value(resource);

			std::function<void()> func = std::bind(&IResource::Initialize, resource, fileName);
			Multi::ThreadPoll::getInstance()->addFuncToThread(func);

			return future;
		};

		template <typename T>
		T* getResource(const std::string& fileName)
		{
			if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
				return nullptr;

			if (m_resources.count(fileName) != 0)
				return dynamic_cast<T*>(m_resources.at(fileName).get());

			return nullptr;
		};

		void loadResources()override;
		void Delete(const std::string& p_fileName);
		void DeleteAll()override;

	private:
		std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources;
		std::vector<std::thread> m_threads;
	};

}

