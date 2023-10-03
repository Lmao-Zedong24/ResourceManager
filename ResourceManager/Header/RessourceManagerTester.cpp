#include "RessourceManagerTester.h"
#include "ResourceManagerMulti.h"
#include "ResourceManager.h"
#include "ThreadPool.h"

void RessourceManagerTester::setManager(ManagerTypes type)
{
	switch (type)
	{
	case RessourceManagerTester::SINGLE:	m_manager = std::make_unique<OpenGl::ResourceManager>();	break;
	case RessourceManagerTester::MULTI:		m_manager = std::make_unique<Multi::ResourceManager>();
											Multi::ThreadPoll::getInstance()->setMaxPollSize();			break;
	default:
		break;
	}
}

void RessourceManagerTester::loadRessources()
{
	m_manager->loadBasicResources();
}

void RessourceManagerTester::loadScene(EntityManager* em, PlayerGO** player, CameraG0** camGO)
{
	m_manager->loadBasicScene(em, player, camGO);
}

void RessourceManagerTester::destroy()
{
	m_manager.release();
}
