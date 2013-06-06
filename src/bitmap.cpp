#include "bitmap.h"
#include <allegro5/allegro.h>

Bitmap::Bitmap()
:bitmap(NULL) {
}

Bitmap::~Bitmap() {
	al_destroy_bitmap(bitmap);
}

void Bitmap::lua_gc() {
	delete this;
}

int Bitmap::Create(int width, int height) {
	bitmap = al_create_bitmap(width, height);
	return bitmap != NULL;
}

int Bitmap::Load(const char *filename) {
	bitmap = al_load_bitmap(filename);
	return bitmap != NULL;
}

void Bitmap::Draw_rotated(float cx, float cy, float dx, float dy, float angle, int flags) {
	al_draw_rotated_bitmap(bitmap, cx, cy, dx, dy, angle, flags);
}

void Bitmap::Draw_scaled_rotated(float cx, float cy, float dx, float dy, float xscale, float yscale, float angle, int flags) {
	al_draw_scaled_rotated_bitmap(bitmap, cx, cy, dx, dy, xscale, yscale, angle, flags);
}
