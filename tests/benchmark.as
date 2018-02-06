#include "godot.gen.as"

void benchmark_api_call() {
	uint start = get_tick_msec();

	for (int i=0; i<100000; i++) {
		godot::Sprite@ s = godot::Sprite::new();
		s.set_name("Hello");
		s.set_position(Vector2(100, 100));
		s.free();
	}

	Variant duration = get_tick_msec() - start;
	print("AngelScript:    " + duration);
}

void benchmark_resource_api() {
	uint start = get_tick_msec();
	for (int i=0; i<100000; i++) {
		godot::Control@ c = godot::Control::new();
		godot::Theme@ theme = godot::Theme::new();
		theme.set_name("My Beautiful Theme");
		godot::ImageTexture@ tex = godot::ImageTexture::new();
		tex.set_name("xxx.png");
		theme.set_icon("Button", "Normal", tex);
		c.set_theme(theme);
		String name = c.get_theme().get_icon("Button", "Normal").get_name();
		c.free();
	}

	Variant duration = get_tick_msec() - start;
	print("AngelScript:    " + duration);
}

// void benchmark_api_call2() {
// 	uint start = get_tick_msec();

// 	for (int i=0; i<100000; i++) {
// 		godot::Node o;
// 		// o.set_meta("name", "value");
// 		// o.get_meta("name");
// 		o.free();
// 	}

// 	Variant duration = get_tick_msec() - start;
// 	print("AngelScript:    " + String(duration));
// }

int fibR(int n) {
    if (n < 2) return n;
    return (fibR(n-2) + fibR(n-1));
}

void benchmark_fibR() {
	uint start = get_tick_msec();
	fibR(34);
	Variant duration = get_tick_msec() - start;
	print("AngelScript:    " + duration);
}
