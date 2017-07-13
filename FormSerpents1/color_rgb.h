#pragma once

class ColorRgb
{
private:
	float red;
	float green;
	float blue;

public:
	ColorRgb();
	ColorRgb(float red, float green, float blue);

	float getRed() const { return red; }
	float getBlue() const { return blue; }
	float getGreen() const { return green; }
};