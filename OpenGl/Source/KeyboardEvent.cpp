#include "KeyboardEvent.h"

OpenGl::KeyboardEvent::KeyboardEvent(KeyButton p_keycode, EventType p_event)
{
	this->Keycode = p_keycode;
	this->Event = p_event;
}

bool OpenGl::KeyboardEvent::operator<(const KeyboardEvent& p_other)const
{
	return this->Keycode < p_other.Keycode || this->Event < p_other.Event;
}
