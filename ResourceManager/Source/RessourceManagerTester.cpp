#include "RessourceManagerTester.h"
#include "ResourceManagerMulti.h"
#include "ResourceManager.h"
#include "ThreadPool.h"

void RessourceManagerTester::setManager(ManagerTypes type)
{
	switch (type)
	{
	case RessourceManagerTester::SINGLE:	m_manager = std::make_unique<OpenGl::ResourceManager>();	break;
	case RessourceManagerTester::MULTI:		m_manager = std::make_unique<OpenGl::ResourceManager>();
											Multi::ThreadPoll::getInstance()->startMaxPollSize();			break;
	default:
		break;
	}
}

void RessourceManagerTester::loadRessources()
{
	m_manager->loadResources();
}

void RessourceManagerTester::destroy()
{
	m_manager.release();
}
