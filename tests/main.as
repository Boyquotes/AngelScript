#include "class.as"
#include "benchmark.as"

void hello_world() {
	print("Hello World! 你好，世界!");
}

void main() {
	// test_resource();
	// benchmark_loop();
	// benchmark_fibR();
	// benchmark_api_call();
	// benchmark_resource_api();
	// benchmark_native_func_call();
	// benchmark_pure_script_class();
	// print("--------------------------------");
	godot::Control@ control = godot::Control::new();
	godot::Node2D@ node2d = godot::Node2D::new();
	control.add_child(node2d);
	godot::Node2D n = control.get_child(0);
	if (n !is null) {
		Variant v = n == node2d;
		print(v);
	}
	control.free();
}
