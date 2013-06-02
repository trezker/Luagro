#include "keyboard.h"
#include "event_queue.h"
#include <allegro5/allegro.h>

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard() {
}

void Keyboard::lua_gc() {
	delete this;
}

void Keyboard::Register_event_source(Event_queue* event_queue) {
	al_register_event_source(event_queue->event_queue, al_get_keyboard_event_source());
}
