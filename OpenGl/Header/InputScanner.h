#pragma once
#include "KeyboardEvent.h"
#include "MouseClickEvent.h"
#include "Vector.h"

#include <glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <functional>


namespace OpenGl
{
	typedef std::function<void()> KeyboardAction;
	typedef std::function<void(LibMath::Vector2)> MouseAction;

	class InputScanner
	{
	public:
		InputScanner();
		~InputScanner();

		bool Init(GLFWwindow* p_window);
		bool Update();

		void AddKeyboardAction(KeyboardEvent, KeyboardAction);
		void AddMouseClickAction(MouseClickEvent, MouseAction);
		void AddMouseMoveAction(MouseAction);
		void ClearInputActions();

	private:
		std::map<KeyboardEvent, KeyboardAction> m_keyboardActions;
		std::map<MouseClickEvent, MouseAction> m_mouseClickActions;
		std::vector<MouseAction> m_moveActions;

		GLFWwindow* m_window;
		

		bool isMouseClickEvent(MouseClickEvent);
		bool isKeyboardEvent(KeyboardEvent);
	};
}

