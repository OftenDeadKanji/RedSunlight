#pragma once
namespace RedSunlight
{
	enum class MouseButtonCodes
	{
		eNone = -1,

		eLeft,
		eMiddle,
		eRight,

		eLast
	};

	constexpr int getMouseButtonsCount()
	{
		return static_cast<int>(MouseButtonCodes::eLast);
	}
}