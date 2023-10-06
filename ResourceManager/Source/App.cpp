#include "App.h"
#include "Renderer.h"
#include "PFAGM.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include <iostream>


const int Multi::App::WINDOW_WIDTH = 1920;
const int Multi::App::WINDOW_HEIGHT = 1080;
const char* Multi::App::WINDOW_NAME = "App\0";


#pragma region OpenGl Initializing Funcs
void OnWindowResize(GLFWwindow* m_window, int width, int height)
{
	glViewport(0, 0, width, height);
}
#pragma endregion

Multi::App::App() : App(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME)
{

}

Multi::App::App(int p_screenWidth, int p_screenHeight, const char* p_title) :
	m_gameManager(Multi::OpenGLGM::GetInstance()),
	m_collisionManager(OpenGl::CollisionManager::GetInstance())
	
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(p_screenWidth, p_screenHeight, p_title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, OnWindowResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

void Multi::App::Init()
{
	m_gameManager->Init();
	m_inputScanner.Init(m_window);
}

void Multi::App::Run()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_inputScanner.Update();
		m_gameManager->Update();
		m_collisionManager->Update();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}



