#pragma once

struct Rect
{
	Rect(int left, int bottom, int width, int height)
	: left(left)
	, bottom(bottom)
	, width(width)
	, height(height) {}

	int left{};
	int bottom{};
	int width{};
	int height{};
};