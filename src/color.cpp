#include "color.h"

Color::Color()
{
}

Color::~Color() {
}

void Color::lua_gc() {
	delete this;
}

void Color::Map_rgba_f(float r, float g, float b, float a) {
	color = al_map_rgba_f(r, g, b, a);
}
