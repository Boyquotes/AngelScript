#include "godot.as"
void benchmark_api_call() {
	uint start = get_tick_msec();

	for (int i=0; i<100000; i++) {
		godot::Sprite s;
		s.set_position(Vector2(100, 100));
		s.set_name("Hello");
		s.free();
	}

	Variant duration = get_tick_msec() - start;

	print("AngelScript:    " + String(duration));
}

void benchmark_api_call2() {
	uint start = get_tick_msec();

	for (int i=0; i<100000; i++) {
		godot::Node o;
		o.set_meta("name", "value");
		o.get_meta("name");
		o.free();
	}

	Variant duration = get_tick_msec() - start;
	print("AngelScript:    " + String(duration));
}


int fibR(int n) {
    if (n < 2) return n;
    return (fibR(n-2) + fibR(n-1));
}

void benchmark_fibR() {
	uint start = get_tick_msec();
	fibR(34);
	Variant duration = get_tick_msec() - start;
	print("AngelScript:    " + String(duration));
}
