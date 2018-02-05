class Base {
	Base() { print("构造Base"); }
	~Base() { print("析构Base"); }

	void method() { print("调用Base::method()"); }
}

class SubClass : Base {
	SubClass() { print("构造SubClass"); }
	~SubClass() { print("析构SubClass"); }
	void method() { print("调用SubClass::method()"); }
}

// 测试对象生命周期函数
void test_object_life_cycle() {
	Base@ obj = SubClass();
	{
		@obj = Base();
	}
	obj.method();
}

class PureClass {
	PureClass() {
		num = 0;
	}

	PureClass(int n) {
		num = n;
	}

	private int num;
}

void benchmark_pure_script_class() {
	uint start = get_tick_msec();

	for (int i=0; i<100000; i++) {
		PureClass o(i);
	}
	Variant duration = get_tick_msec() - start;
	String sd = duration;
	print("AngelScript:    " + sd);
}
