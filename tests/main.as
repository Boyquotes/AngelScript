#include "class.as"
#include "benchmark.as"

void hello_world() {
	print("Hello World! 你好，世界!");
}

void main() {
	// test_resource();
	// benchmark_fibR();
	// benchmark_api_call();
	benchmark_resource_api();
	// benchmark_pure_script_class();
}
