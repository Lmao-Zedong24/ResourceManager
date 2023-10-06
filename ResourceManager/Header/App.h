#pragma once
#include "IGameManager.h"
#include "InputScanner.h"
#include "Renderer.h"
#include "Camera.h"
#include "CollisionManager.h"

#include <glad.h>
#include <GLFW/glfw3.h>


using namespace OpenGl;

namespace Multi
{
	class App
	{

	public:
		App();
		App(int p_screenWidth, int p_screenHeight, const char* p_title);
		~App() = default;

		void Init();
		void Run();

		static const int WINDOW_WIDTH;
		static const int WINDOW_HEIGHT;
		static const char* WINDOW_NAME;

	private:
		GLFWwindow*				m_window;
		IGameManager*			m_gameManager;
		CollisionManager*		m_collisionManager;
		InputScanner			m_inputScanner;

		//GLFWwindow* OnWindowResize(GLFWwindow* m_window, int width, int height);
	};
}




