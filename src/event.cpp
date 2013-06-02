#include "event.h"
#include "event_queue.h"

Event::Event() {
}

Event::~Event() {
}

void Event::lua_gc() {
	delete this;
}

int Event::Type() {
	return event.type;
}

int Event::Keycode() {
	return event.keyboard.keycode;
}

int Event::Timer_count() {
	return event.timer.count;
}
