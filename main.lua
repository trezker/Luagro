local display = Display.new();
display:Create(800, 600);

local clear_color = Color.new();
clear_color:Map_rgba_f(0, 0, 0, 0);

local timer_speed = .018;
local timer = Timer.new();
timer:Create(timer_speed);

local event_queue = Event_queue.new();
event_queue:Create();
display:Register_event_source(event_queue);
timer:Register_event_source(event_queue);

local keyboard = Keyboard.new();
keyboard:Register_event_source(event_queue);

local bitmap = Bitmap.new();
if bitmap:Load("data/62px-Bulldog-GTA1.png") == 0 then
	print("Failed to load image");
end

local cx = 31;
local cy = 16;
local dx = 100;
local dy = 100;
local angle = 0;

local left = false;
local right = false;
local up = false;
local down = false;

timer:Start();
local event = Event.new();
local quit = false;
while not quit do
	event_queue:Wait_for_event(event);
	if event:Type() == Event.ALLEGRO_EVENT_DISPLAY_CLOSE then
		quit = true;
	end
	if event:Type() == Event.ALLEGRO_EVENT_KEY_DOWN then
		if event:Keycode() == Keyboard.ALLEGRO_KEY_LEFT then
			left = true;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_RIGHT then
			right = true;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_UP then
			up = true;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_DOWN then
			down = true;
		end
	end
	if event:Type() == Event.ALLEGRO_EVENT_KEY_UP then
		if event:Keycode() == Keyboard.ALLEGRO_KEY_LEFT then
			left = false;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_RIGHT then
			right = false;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_UP then
			up = false;
		end
		if event:Keycode() == Keyboard.ALLEGRO_KEY_DOWN then
			down = false;
		end
	end

	if event:Type() == Event.ALLEGRO_EVENT_TIMER then
		--Check saved time against current time
		--If greater than interval time, change timer speed
		--print("tick");
		--Save current time here
		if event:Timer_count() == timer:Get_count() then
			if left then
				angle = angle - .01;
			end
			if right then
				angle = angle + .01;
			end
			display:Clear_to_color(clear_color);
			bitmap:Draw_rotated(cx, cy, dx, dy, angle, 0);
			display:Flip();		
		end
		if event:Timer_count() < timer:Get_count() then
			timer_speed = timer_speed * 1.1;
			timer:Set_speed(timer_speed);
			print("Tick too fast, setting speed to " .. timer_speed);
		end
	end
end

display = nil;
collectgarbage();
