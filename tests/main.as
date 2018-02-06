#include "class.as"
#include "benchmark.as"

void hello_world() {
	print("Hello World! 你好，世界!");
}

void main() {
	// test_resource();
	benchmark_fibR();
	benchmark_api_call();
	benchmark_resource_api();
	// benchmark_pure_script_class();
	print("--------------------------------");
	godot::Control@ control = godot::Control::new();
	godot::Node2D@ node2d = godot::Node2D::new();
	control.add_child(node2d);
	godot::Node2D@ n = cast<godot::Node2D@>(control.get_child(0));
	Variant v = n;
	print(v);
	control.free();
}
