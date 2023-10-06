#include "ResourceManagerMulti.h"
#include "Texture.h"
#include "ModelMulti.h"
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

	void ResourceManager::loadResources()
	{
		auto& rm = *this;
		std::vector<std::future<IResource*>> futures;

		futures.emplace_back(rm.addRessource<Texture>("png-clipart-barack-obama-barack-obama.png"));
		futures.emplace_back(rm.addRessource<Texture>("red.png"));
		futures.emplace_back(rm.addRessource<Texture>("green.png"));
		futures.emplace_back(rm.addRessource<Texture>("blue.png"));
		futures.emplace_back(rm.addRessource<Texture>("white.png"));
		futures.emplace_back(rm.addRessource<Texture>("grey.png"));
		futures.emplace_back(rm.addRessource<Texture>("black.png"));
		futures.emplace_back(rm.addRessource<ModelMulti>("cube.obj"));
		futures.emplace_back(rm.addRessource<ModelMulti>("Sting-Sword-lowpoly.obj"));
		futures.emplace_back(rm.addRessource<ModelMulti>("sphere.obj"));
		futures.emplace_back(rm.addRessource<ModelMulti>("cylindre.obj"));

		for (int i = 2; i <= 10; i++) //Sting-Sword-lowpoly - Copy (2).obj
			futures.emplace_back(	rm.addRessource<ModelMulti>(
									std::string(	"Sting-Sword-lowpoly - Copy (") + 
													std::to_string(i) + 
													std::string(").obj")));

		//thread unsafe functions
		for (auto& future : futures)
			future.get()->OpenGlSetup();
	}
}