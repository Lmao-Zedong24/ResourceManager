#include "MouseClickEvent.h"

OpenGl::MouseClickEvent::MouseClickEvent(int p_button, EventType p_event)
{
    this->Button = p_button;
    this->Event = p_event;
}

bool OpenGl::MouseClickEvent::operator<(const MouseClickEvent& p_other)const
{
    return this->Button < p_other.Button || this->Event < p_other.Event;
}
