#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "RessourceManagerTester.h"
#include "EntityManager.h"
#include "PlayerGO.h"
#include "CameraG0.h"
#include "Light.h"
#include "Timer.h"


constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;

void onWindowResize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render();

using namespace LibMath::Literal;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, onWindowResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Camera	cam;
	Light	lig(LibMath::Vector3(0, 0, 0));

	RessourceManagerTester	rm;
	EntityManager			em;
	PlayerGO*				player = nullptr;
	CameraG0*				camGO = nullptr;

	My::Stopwatch stopWatch;

	while (true)
	{
		std::cout << "Press (s) for single thread, (m) for multi thread, (g) to start scene or (q) to quit." << std::endl;
		char c;
		std::cin >> c;

		if (c == 's' || c == 'm')
		{
			rm.setManager(c == 's'? RessourceManagerTester::SINGLE: RessourceManagerTester::MULTI);
			stopWatch.Start();
			rm.loadRessources();
			std::cout << "Resources loaded in: " << stopWatch.Stop() << "ms" << std::endl;
		}
		else if (c == 'q')
		{
			rm.destroy();
			glfwTerminate();
			return 0;
		}
		else if (c == 'g')
		{
			rm.loadScene(&em, &player, &camGO);
			break;
		}
		else
			std::cout << "Enter valid input" << std::endl;
	}

	Shader shader;
	shader.Initialize("shaderBuffer.txt");
	shader.Link();

	while (!glfwWindowShouldClose(window))
	{
		camGO->Update();

		processInput(window);
		player->Inputs(window);
		player->Update();

		render();

		em.DrawAllEntities(shader, camGO->GetCamera());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	rm.destroy();
	glfwTerminate();
	return 0;
}

void onWindowResize(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void render()
{
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}




