void hello_world() {
	print("Hello World!");
}

void test_variant() {
	Variant int_val = 111 + 111;
	print(int_val);

	Variant float_val = 1.1f * 2.1f;
	print(float_val);

	Variant double_val = 1.0;
	print(double_val);

	Variant bool_val = 1 + 1 == 2;
	print(bool_val);

	Variant str_val = "Hello AngelScript";
	print(str_val);

	Vector2 vec2;
	Variant vec2_val = vec2;
	print(vec2_val);

	Vector3 vec3;
	Variant vec3_val = vec3;
	print(vec3_val);

	Color c;
	Variant color_val = c;
	print(color_val);

	Rect2 rect;
	Variant rect_val = rect;
	print(rect_val);

	Array arr;
	Variant arr_val = arr;
	print(arr_val);

	Dictionary dict;
	Variant dict_val = dict;
	print(dict_val);
}


namespace godot {
	class Object {

		Object() {
			_make_instance();
		}

		protected void _make_instance() {
			@ptr = ClassDB.instance("Object");
		}

		bool has_meta(const String &in p_name) const {
			return ptr.has_meta(p_name);
		}

		void set_meta(const String &in p_name, const Variant &in val) {
			ptr.set_meta(p_name, val);
		}

		String get_class() const {
			return ptr.get_class();
		}

		Variant get_meta(const String &in p_name) const {
			return ptr.get_meta(p_name);
		}

		void free() {
			ptr.free();
			@ptr = null;
		}

		protected _Object@ ptr;
	};

	class Sprite : Object {
		protected void _make_instance() {
			@ptr = ClassDB.instance("Sprite");
		}
	}

	class Reference : Object {

		protected void _make_instance() {
			@ptr = (ref = ClassDB.instance("Reference")).ptr();
		}
		protected REF ref;
	}

	class Resource : Reference {

		String get_name() const {
			StringName method = "get_name";
			return ptr.call(method);
		}

		void set_name(const String &in p_name) const {
			StringName method = "set_name";
			ptr.call(method, p_name);
		}

		protected void _make_instance() {
			@ptr = (ref = ClassDB.instance("Resource")).ptr();
		}
	}

	class ImageTexture : Resource {
		protected void _make_instance() {
			@ptr = (ref = ClassDB.instance("ImageTexture")).ptr();
		}
	}

}

void test_object() {
	godot::Sprite obj;
	print(obj.get_class());
	obj.set_meta("data", "Hello Object");
	if (obj.has_meta("data")) {
		print(obj.get_meta("data"));
	}
	obj.free();
}

void test_reference() {
	godot::ImageTexture obj;
	obj.set_meta("data", "Hello Object");
	obj.set_name("XXXX");
	if (obj.has_meta("data")) {
		print(obj.get_meta("data"));
	}
	print(obj.get_class());
	test_ref2(obj);
}

void test_ref2(const godot::Resource &in r) {
	print(r.get_name());
	print(r.get_meta("data"));
}

void main() {
	test_reference();
}
