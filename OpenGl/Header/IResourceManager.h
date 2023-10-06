#pragma once
#include "EntityManager.h"
#include "PlayerGO.h"
#include "CameraG0.h"

class IResourceManager
{
public:
	void virtual loadResources() {};
	void virtual DeleteAll() {};
};