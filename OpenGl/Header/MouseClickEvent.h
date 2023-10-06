#pragma once
#include <functional>

namespace OpenGl
{
	class MouseClickEvent
	{
	public:
		enum class EventType
		{
			ON_CLICK,
			//ON_HOLD,
			ON_RELEASE
		};

		MouseClickEvent() = default;
		MouseClickEvent(int p_button, EventType p_event);
		~MouseClickEvent() = default;

		int Button;
		EventType Event;

		bool operator<(const MouseClickEvent&)const;
	};
}

