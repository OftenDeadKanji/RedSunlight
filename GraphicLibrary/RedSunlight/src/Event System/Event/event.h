#pragma once
#include "eventType.h"

namespace RedSunlight
{
	struct Event
	{
		Event();
		explicit Event(EventType type);

		EventType type;
	};
}
