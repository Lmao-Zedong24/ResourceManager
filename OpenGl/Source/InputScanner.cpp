#include "InputScanner.h"
#include "Vector.h"
#include "PlayerGO.h"

#include <glad.h>
#include <GLFW/glfw3.h>

using namespace LibMath;

OpenGl::InputScanner::InputScanner()
{
}

OpenGl::InputScanner::~InputScanner()
{
}

bool OpenGl::InputScanner::Init(GLFWwindow* p_window)
{
	m_window = p_window;
	PlayerGO::window = m_window;

	return true;
}

bool OpenGl::InputScanner::Update()
{

	for (auto& pair : this->m_keyboardActions)
	{
		if (this->isKeyboardEvent(pair.first))
			pair.second();
	}

	Vector2 mousePos(0);// = {GetMouseX(), GetMouseY()}; //TODO : mose pos

	for (auto& pair : this->m_mouseClickActions)
	{
		if (this->isMouseClickEvent(pair.first))
			pair.second(mousePos);
	}

	for (auto& action : this->m_moveActions)
	{
		action(mousePos);
	}

	return true;
}

void OpenGl::InputScanner::AddKeyboardAction(KeyboardEvent p_event, KeyboardAction p_action)
{
	this->m_keyboardActions.insert(std::make_pair(p_event, p_action));
}

void OpenGl::InputScanner::AddMouseClickAction(MouseClickEvent p_event, MouseAction p_action)
{
	this->m_mouseClickActions.insert(std::make_pair(p_event, p_action));
}

void OpenGl::InputScanner::AddMouseMoveAction(MouseAction p_action)
{
	this->m_moveActions.push_back(p_action);
}

void OpenGl::InputScanner::ClearInputActions()
{
}

bool OpenGl::InputScanner::isMouseClickEvent(MouseClickEvent p_event)
{
	int event = -1;

	switch (p_event.Event)
	{
	case OpenGl::MouseClickEvent::EventType::ON_CLICK:
		event = GLFW_PRESS;
		break;

	//case OpenGl::MouseClickEvent::EventType::ON_HOLD:
	//	event = GLFW_RELEASE;
	//	break;

	case OpenGl::MouseClickEvent::EventType::ON_RELEASE:
		event = GLFW_RELEASE;
		break;

	default:
		event = -1;
		break;
	}

	return glfwGetMouseButton(m_window, p_event.Button) == event;
}

bool OpenGl::InputScanner::isKeyboardEvent(KeyboardEvent p_event)
{
	int event = -1;

	switch (p_event.Event)
	{
	case OpenGl::KeyboardEvent::EventType::ON_CLICK:
		event = GLFW_PRESS;
		break;

		//case OpenGl::MouseClickEvent::EventType::ON_HOLD:
		//	event = GLFW_RELEASE;
		//	break;

	case OpenGl::KeyboardEvent::EventType::ON_RELEASE:
		event = GLFW_RELEASE;
		break;

	default:
		event = -1;
		break;
	}

	return glfwGetKey(m_window, p_event.Keycode) == event;
}
