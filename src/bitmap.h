#ifndef luagro_bitmap_h
#define luagro_bitmap_h

struct ALLEGRO_BITMAP;

class Bitmap {
public:
	ALLEGRO_BITMAP* bitmap;
	Bitmap();
	~Bitmap();
	void lua_gc();
	int Create(int width, int height);
	int Load(const char *filename);
	void Draw_rotated(float cx, float cy, float dx, float dy, float angle, int flags);
	void Draw_scaled_rotated(float cx, float cy, float dx, float dy, float xscale, float yscale, float angle, int flags);
};

#endif
