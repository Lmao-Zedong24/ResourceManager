#pragma once
#include "EntityManager.h"
#include "PlayerGO.h"
#include "CameraG0.h"

class IResourceManager
{
public:
	void virtual loadBasicResources() {};
	void virtual loadBasicScene(EntityManager* em, PlayerGO** player, CameraG0** camGO) {};
	void virtual DeleteAll() {};
};