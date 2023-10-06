#pragma once
#include "GameObject.h"
#include "RigidBody.h"
#include "Vector.h"


class RigidGO : public GameObject
{
public:
	RigidGO(GameObject* p_parent) : 
		GameObject(p_parent), m_rigidBody(nullptr){};
	RigidGO(GameObject* p_parent, Model* p_model, Texture* p_texture) : 
		GameObject(p_parent, p_model, p_texture), m_rigidBody(nullptr) {};
	~RigidGO() = default;

	void				SetRigidBodyCollider(Collider* p_rigidBody);
	const Collider&		GetRigidBody();

protected:
	Collider*			m_rigidBody;	//dont need to update bcs static wall
};

class RigidLerpGO : public RigidGO
{
public:
	RigidLerpGO(GameObject* p_parent) :
		RigidGO(p_parent) {};
	RigidLerpGO(GameObject* p_parent, Model* p_model, Texture* p_texture) :
		RigidGO(p_parent, p_model, p_texture) {};
	~RigidLerpGO() = default;

	void SetupLerpPos(LibMath::Vector3 p_posA, LibMath::Vector3 p_posB);
	void SetupLerpDir(LibMath::Vector3 p_dir);
	void Update()override;

private:
	LibMath::Vector3	m_posA;	//dont need to update bcs static wall
	LibMath::Vector3	m_posB;	//dont need to update bcs static wall
	bool				m_flip = false;
	float				m_tVal = 0.0f;

	const float			LERP_SPEED = 0.005f;
};


