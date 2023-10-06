#pragma once
#include "IGameManager.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "ResourceManagerMulti.h"
#include "Camera.h"
#include <memory>

namespace Multi
{
	class OpenGLGM : public OpenGl::IGameManager
	{
	public:
		OpenGLGM() = default;
		~OpenGLGM() = default;

		void Init() override;
		void Update() override;
		void PlayerInputs(GLFWwindow* p_window);

		static OpenGLGM* GetInstance();

	private:
		void BackGorund();
		void createScene(bool isMulti);

		Camera*								m_currentCam;
		std::unique_ptr<IResourceManager>	m_resourceManager;
		EntityManager						m_entityManager;
		OpenGl::CollisionManager*			m_collisionManager;
		
		Shader m_shader;

		static inline std::unique_ptr<OpenGLGM> m_PFAGM;
	};
}