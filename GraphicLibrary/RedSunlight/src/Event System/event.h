#pragma once

namespace RedSunlight
{
	enum class EventType {
		eNone,
		eMouseButtonPressed,
		eMouseButtonReleased,
		eKeyPressed,
		eKeyReleased,
		eWindowClose
	};

	struct Event {
		Event();
		explicit Event(EventType type);

		EventType type;
	};
}