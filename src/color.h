#ifndef luagro_color_h
#define luagro_color_h

#include <allegro5/allegro.h>

class Color {
public:
	ALLEGRO_COLOR color;
	Color();
	~Color();
	void lua_gc();
	void Map_rgba_f(float r, float g, float b, float a);
};

#endif
