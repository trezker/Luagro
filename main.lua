--[[
Accelleration adds force in the facing direction.
Current force vector lags behind when turning.
Drag always applies to current force.
When you turn too hard the current force becomes too much to the side and may overcome friction.
If sideforce is not enough to loose grip, the car only moves towards its heading.
]]

function SquaredLength(x, y)
	return x*x + y*y;
end

function Length(x, y)
	return math.sqrt(x*x + y*y);
end

function Normalize(x, y)
	local length = Length(x, y);
	if length == 0 then
		return 0, 0;
	end
	return x/length, y/length;
end

function Stretch(x, y, m)
	return x*m, y*m;
end

function Dotproduct(x, y, x2, y2)
	return x * x2 + y * y2;
end

local display = Display.new();
display:Create(800, 600);

local clear_color = Color.new();
clear_color:Map_rgba_f(0, 0, 0, 0);

local timer_speed = .01;
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
local forcex = 0;
local forcey = 0;
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
		if event:Timer_count() == timer:Get_count() then
			if up then
				forcex = forcex + math.cos(angle) * .6;
				forcey = forcey + math.sin(angle) * .6;
			end
			if down then
				forcex = forcex - math.cos(angle) * .6;
				forcey = forcey - math.sin(angle) * .6;
			end
			local drag = SquaredLength(forcex, forcey) / 100;
			local newlength = Length(forcex, forcey) - drag;
			if newlength < .5 then
				newlength = 0;
			end
			forcex, forcey = Normalize(forcex, forcey);
			forcex, forcey = Stretch(forcex, forcey, newlength);

			--Dotproduct used to project current force onto current heading. 
			local dirx = math.cos(angle);
			local diry = math.sin(angle);
			local dotproduct = Dotproduct(forcex, forcey, dirx, diry);
			travelx = dirx * dotproduct;
			travely = diry * dotproduct;
			
			turnspeed = .01 * dotproduct;
			turnspeed = turnspeed - ((dotproduct * dotproduct) / 10000);
			if dotproduct > 0.1 then
				if left then
					angle = angle - turnspeed;
				end
				if right then
					angle = angle + turnspeed;
				end
			elseif dotproduct < -.1 then
				if left then
					angle = angle + turnspeed;
				end
				if right then
					angle = angle - turnspeed;
				end
			end

			dx = dx + travelx;
			dy = dy + travely;
			
			display:Clear_to_color(clear_color);
			bitmap:Draw_rotated(cx, cy, dx, dy, angle, Bitmap.ALLEGRO_FLIP_HORIZONTAL);
			display:Flip();		
		end
		if event:Timer_count() < timer:Get_count() - 4 then
			timer_speed = timer_speed * 1.1;
			timer:Set_speed(timer_speed);
			print("Tick too fast, setting speed to " .. timer_speed);
		end
	end
end

display = nil;
collectgarbage();
