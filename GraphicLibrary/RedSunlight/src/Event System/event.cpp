#include "pch.h"
#include "event.h"

namespace RedSunlight
{

Event::Event() : type(EventType::eNone)
{}

Event::Event(const EventType type) : type(type)
{}
	
}