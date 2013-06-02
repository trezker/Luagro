#include "event_queue.h"
#include "event.h"
#include <allegro5/allegro.h>

Event_queue::Event_queue()
:event_queue(NULL) {
}

Event_queue::~Event_queue() {
	al_destroy_event_queue(event_queue);
}

void Event_queue::lua_gc() {
	delete this;
}

int Event_queue::Create() {
	event_queue = al_create_event_queue();
	return event_queue != NULL;
}

void Event_queue::Wait_for_event(Event* event) {
	al_wait_for_event(event_queue, &(event->event));
}
