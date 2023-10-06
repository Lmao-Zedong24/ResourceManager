#include "WallGO.h"

void RigidGO::SetRigidBodyCollider(Collider* p_rigidBody)
{
    m_rigidBody = p_rigidBody;
}

const Collider& RigidGO::GetRigidBody()
{
	return *m_rigidBody;
}

void RigidLerpGO::SetupLerpPos(LibMath::Vector3 p_posA, LibMath::Vector3 p_posB)
{
	m_posA = p_posA;
	m_posB = p_posB;
}

void RigidLerpGO::SetupLerpDir(LibMath::Vector3 p_dir)
{
	m_posB = p_dir;
}



void RigidLerpGO::Update()
{
	m_tVal += m_flip ? -LERP_SPEED : LERP_SPEED;

	if (!(m_tVal <= 1 && m_tVal >= 0))
		m_flip = !m_flip;

	//LibMath::Vector3 lerp = (m_posA + (m_posB - m_posA) * m_tVal);

	m_localTransform.translate(m_flip? -m_posB * LERP_SPEED : m_posB * LERP_SPEED);
	m_rigidBody->UpdateCollidables(m_localTransform);

	this->UpdateGlobalMat();

	for (auto& child : m_children)
		child.second->Update();
}
