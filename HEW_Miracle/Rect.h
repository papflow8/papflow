#pragma once

struct Rect {
	int x, y, width, height;
	Rect() { Rect(0, 0, 0, 0); }
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h) {}
};
