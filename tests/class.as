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
