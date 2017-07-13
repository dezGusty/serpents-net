#pragma once

#include <string>
#include "color_rgb.h"

class IDrawableArea
{
public:
	virtual void drawText(std::string text, ColorRgb color, float fromX, float fromY) = 0;
};