#include "timer.h"
#include "event_queue.h"
#include <allegro5/allegro.h>

Timer::Timer()
:timer(NULL) {
}

Timer::~Timer() {
	al_destroy_timer(timer);
}

void Timer::lua_gc() {
	delete this;
}

int Timer::Create(double speed_secs) {
	timer = al_create_timer(speed_secs);
	return timer != NULL;
}

void Timer::Register_event_source(Event_queue* event_queue) {
	al_register_event_source(event_queue->event_queue, al_get_timer_event_source(timer));
}

void Timer::Start() {
	al_start_timer(timer);
}

int Timer::Get_count() {
	return al_get_timer_count(timer);
}

void Timer::Set_speed(double new_speed_secs) {
	al_set_timer_speed(timer, new_speed_secs);
}
