#include <LuaGlue/LuaGlue.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "display.h"
#include "timer.h"
#include "event_queue.h"
#include "event.h"
#include "bitmap.h"
#include "color.h"
#include "keyboard.h"

int main(int, char **)
{
	if(!al_init()) {
		printf("failed to initialize Allegro\n");
		return 0;
	}
	if(!al_init_image_addon()) {
		printf("failed to initialize Image addon\n");
		return 0;
	}
	if(!al_install_keyboard()) {
		printf("failed to install keyboard\n");
		return 0;
	}
	
	LuaGlue state;
	
	state.
		Class<Color>("Color").
			ctor("new").
			dtor(&Color::lua_gc).
			method("Map_rgba_f", &Color::Map_rgba_f).
		end().open().glue();

	state.
		Class<Display>("Display").
			ctor("new").
			dtor(&Display::lua_gc).
			method<int>("Create", &Display::Create).
			method("Register_event_source", &Display::Register_event_source).
			method("Flip", &Display::Flip).
			method("Clear_to_color", &Display::Clear_to_color).
		end().open().glue();

	state.
		Class<Event>("Event").
			ctor("new").
			dtor(&Event::lua_gc).
			method("Type", &Event::Type).
			method("Keycode", &Event::Keycode).
			method("Timer_count", &Event::Timer_count).
			constants( 	{ 
							{ "ALLEGRO_EVENT_DISPLAY_CLOSE", ALLEGRO_EVENT_DISPLAY_CLOSE },
							{ "ALLEGRO_EVENT_TIMER", ALLEGRO_EVENT_TIMER },
							{ "ALLEGRO_EVENT_KEY_DOWN", ALLEGRO_EVENT_KEY_DOWN },
							{ "ALLEGRO_EVENT_KEY_UP", ALLEGRO_EVENT_KEY_UP }
							
						} ).
		end().open().glue();

	state.
		Class<Event_queue>("Event_queue").
			ctor("new").
			dtor(&Event_queue::lua_gc).
			method<int>("Create", &Event_queue::Create).
			method("Wait_for_event", &Event_queue::Wait_for_event).
		end().open().glue();

	state.
		Class<Timer>("Timer").
			ctor("new").
			dtor(&Timer::lua_gc).
			method<int>("Create", &Timer::Create).
			method("Register_event_source", &Timer::Register_event_source).
			method("Start", &Timer::Start).
			method<int>("Get_count", &Timer::Get_count).
			method("Set_speed", &Timer::Set_speed).
		end().open().glue();
	
	state.
		Class<Bitmap>("Bitmap").
			ctor("new").
			dtor(&Bitmap::lua_gc).
			method<int>("Create", &Bitmap::Create).
			method<int>("Load", &Bitmap::Load).
			method("Draw_rotated", &Bitmap::Draw_rotated).
			constants( 	{ 
							{ "ALLEGRO_FLIP_HORIZONTAL", ALLEGRO_FLIP_HORIZONTAL },
							{ "ALLEGRO_FLIP_VERTICAL", ALLEGRO_FLIP_VERTICAL },
						} ).
		end().open().glue();

	state.
		Class<Keyboard>("Keyboard").
			ctor("new").
			dtor(&Keyboard::lua_gc).
			method("Register_event_source", &Keyboard::Register_event_source).
			constants( 	{ 
							{ "ALLEGRO_KEY_LEFT", ALLEGRO_KEY_LEFT },
							{ "ALLEGRO_KEY_RIGHT", ALLEGRO_KEY_RIGHT },
							{ "ALLEGRO_KEY_UP", ALLEGRO_KEY_UP },
							{ "ALLEGRO_KEY_DOWN", ALLEGRO_KEY_DOWN }
							
						} ).
		end().open().glue();

	if(luaL_dofile(state.state(), "main.lua"))
	{
		printf("failed to dofile: main.lua\n");
		const char *err = luaL_checkstring(state.state(), -1);
		printf("err: %s\n", err);
	}
		
	return 0;
}
