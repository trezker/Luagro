#ifndef luagro_event_queue_h
#define luagro_event_queue_h

class Event;
struct ALLEGRO_EVENT_QUEUE;

class Event_queue {
public:
	ALLEGRO_EVENT_QUEUE* event_queue;
	Event_queue();
	~Event_queue();
	void lua_gc();
	int Create();
	void Wait_for_event(Event* event);
};

#endif
