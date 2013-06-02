#ifndef luagro_timer_h
#define luagro_timer_h

struct ALLEGRO_TIMER;
class Event_queue;

class Timer {
	ALLEGRO_TIMER* timer;
public:
	Timer();
	~Timer();
	void lua_gc();
	int Create(double speed_secs);
	void Register_event_source(Event_queue* event_queue);
	void Start();
	int Get_count();
	void Set_speed(double new_speed_secs);
};

#endif
