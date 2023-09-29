#include "ResourceManager.h"
#include "GameObject.h"

namespace Multi
{
	const IResource* ResourceManager::CreateResource(const std::string& fileName, ProductId id)
	{
		auto& thread = m_threads.emplace_back(&ResourceManager::CreateResourceThread, this, fileName, id);
		thread.join(); //TODO : cant do this
		return (m_resources.at(fileName).get());
	}

	const IResource* ResourceManager::GetResource(const std::string& fileName)
	{
		if (m_resources.count(fileName) != 0)
			return m_resources.at(fileName).get();

		return nullptr;
	};

	void ResourceManager::CreateResourceThread(const std::string& fileName, ProductId id)
	{
		if (this->m_resources.count(fileName) != 0)
			this->m_resources.erase(fileName);


		std::unique_ptr<IResource> resource = nullptr;
		switch (id)
		{
		case Multi::ResourceManager::Model:		resource = std::make_unique<Model>;		break;
		case Multi::ResourceManager::Texture:	resource = std::make_unique<Texture>;	break;
		default:
			break;
		}

		resource->Initialize(fileName);
		m_resources.emplace(fileName, std::move(resource));
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