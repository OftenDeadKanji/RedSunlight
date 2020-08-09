#pragma once

enum class DrawableType {
	eElement2D,
	eElement2DText,
	eElement3D
};

class IDrawable {
public:
	virtual ~IDrawable() = default;
	[[nodiscard]] virtual DrawableType getDrawableType() const = 0;
	virtual void draw() = 0;
};