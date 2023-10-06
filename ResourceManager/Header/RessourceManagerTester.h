#pragma once
#include "IResourceManager.h"
#include "EntityManager.h"
#include "PlayerGO.h"
#include "CameraG0.h"

class RessourceManagerTester
{
public:
	RessourceManagerTester() = default;
	~RessourceManagerTester() = default;

	enum ManagerTypes
	{
		DEFAULT,
		SINGLE,
		MULTI
	};

	void setManager(ManagerTypes type);
	void loadRessources();
	void destroy();

private:
	std::unique_ptr<IResourceManager>	m_manager;
	ManagerTypes						m_type = DEFAULT;
};