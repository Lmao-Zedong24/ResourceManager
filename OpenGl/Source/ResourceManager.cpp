#include "ResourceManager.h"

namespace OpenGl
{
	void ResourceManager::loadResources()
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
			resource.second.get()->OpenGlSetup();
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
