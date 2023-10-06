#pragma once
#include <unordered_map>
#include "IResource.h"
#include "IResourceManager.h"
#include <memory>
#include <string>

namespace OpenGl
{
	class ResourceManager : public IResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		template <typename T>
		T* Add(const std::string& p_fileName)
		{
			if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
				return nullptr;

			if (this->m_resources.count(p_fileName) != 0)
				this->m_resources.erase(p_fileName);

			this->m_resources.insert({ p_fileName,
										std::make_unique<T>()});

			T* resource = static_cast<T*>(m_resources.at(p_fileName).get());
			resource->Initialize(p_fileName);
			return resource;
		};

		template <typename T>
		T* getResource(const std::string& p_fileName)
		{
			if (this->m_resources.count(p_fileName) != 0)
				return static_cast<T*>(this->m_resources.at(p_fileName).get());

			return nullptr;
		};

		void loadResources()override;

		void Delete(const std::string& p_fileName);
		void DeleteAll()override;

	private:
		std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources;
	};
}


