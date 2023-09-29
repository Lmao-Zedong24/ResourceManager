#pragma once
#include "IResource.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <mutex>

namespace Multi
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		ResourceManager(const ResourceManager&) = default;
		ResourceManager(ResourceManager&&) = default;
		~ResourceManager() = default;

		enum ProductId
		{
			Model,
			Texture
		};

		//TODO: add resources then generate them? or mutex magic
		const IResource* CreateResource(const std::string& fileName, ProductId id);
		const IResource* GetResource(const std::string& fileName);

		void Delete(const std::string& p_fileName);
		void DeleteAll();

	private:
		void CreateResourceThread(const std::string& fileName, ProductId id);

		std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources;
		std::vector<std::thread> m_threads;
	};

}

