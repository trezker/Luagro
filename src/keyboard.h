#ifndef luagro_keyboard_h
#define luagro_keyboard_h

class Event_queue;

class Keyboard {
public:
	Keyboard();
	~Keyboard();
	void lua_gc();
	void Register_event_source(Event_queue* event_queue);
};

#endif
