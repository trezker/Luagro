#ifndef luagro_event_h
#define luagro_event_h

#include <allegro5/allegro.h>

class Event {
public:
	ALLEGRO_EVENT event;
	Event();
	~Event();
	void lua_gc();
	int Type();
	int Keycode();
	int Timer_count();
};

#endif
