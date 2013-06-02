#include "display.h"
#include "event_queue.h"
#include "color.h"
#include <allegro5/allegro.h>

Display::Display()
:display(NULL) {
}

Display::~Display() {
	al_destroy_display(display);
}

void Display::lua_gc() {
	delete this;
}

int Display::Create(int width, int height) {
	display = al_create_display(width, height);
	return display != NULL;
}

void Display::Register_event_source(Event_queue* event_queue) {
	al_register_event_source(event_queue->event_queue, al_get_display_event_source(display));
}

void Display::Flip() {
	al_flip_display();
}

void Display::Clear_to_color(Color* color) {
	al_clear_to_color(color->color);
}
