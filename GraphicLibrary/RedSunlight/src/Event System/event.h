#pragma once

namespace RedSunlight
{
	enum class RED_API EventType {
		eNone,
		eMouseButtonPressed,
		eMouseButtonReleased,
		eKeyPressed,
		eKeyReleased,
		eWindowClose
	};

	struct RED_API Event {
		Event();
		explicit Event(EventType type);

		EventType type;
	};
}