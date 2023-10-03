#include "EntityManager.h"

void EntityManager::DrawAllEntities(Shader& p_shader, Camera& p_camera)
{
	for (auto& pair : m_entities)
		pair.second->DrawNodes(p_shader, p_camera);
}
