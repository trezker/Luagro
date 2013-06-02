#ifndef luagro_display_h
#define luagro_display_h

struct ALLEGRO_DISPLAY;
class Event_queue;
class Color;

class Display {
	ALLEGRO_DISPLAY* display;
public:
	Display();
	~Display();
	void lua_gc();
	int Create(int width, int height);
	void Register_event_source(Event_queue* event_queue);
	void Flip();
	void Clear_to_color(Color* color);
};

#endif
