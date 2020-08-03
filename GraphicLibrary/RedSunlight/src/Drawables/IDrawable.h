#pragma once

enum class DrawableType {
	ELEMENT_2D,
	ELEMENT_3D
};

class IDrawable {
public:
	virtual DrawableType getDrawableType() const = 0;
	virtual void draw() = 0;
protected:
};