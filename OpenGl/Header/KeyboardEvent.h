#pragma once
#include <functional>

namespace OpenGl
{
	class KeyboardEvent
	{
	public:
		typedef int KeyButton;
		//typedef KeyButton = int;

		enum class EventType
		{
			ON_CLICK,
			ON_HOLD,
			ON_RELEASE
		};

		KeyboardEvent() = default;
		KeyboardEvent(KeyButton p_keycode, EventType p_event);
		~KeyboardEvent() = default;

		KeyButton Keycode;
		EventType Event;

		bool operator<(const KeyboardEvent&)const;
	};
}

