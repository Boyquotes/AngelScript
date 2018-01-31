namespace godot {
	class Object {

		Object() {
			_make_instance();
		}

		protected void _make_instance() {
			@ptr = Object_t();
		}

		// bool has_meta(const String &in p_name) const {
		// 	return ptr.has_meta(p_name);
		// }

		// void set_meta(const String &in p_name, const Variant &in val) {
		// 	ptr.set_meta(p_name, val);
		// }

		// String get_class() const {
		// 	return ptr.get_class();
		// }

		// Variant get_meta(const String &in p_name) const {
		// 	return ptr.get_meta(p_name);
		// }

		void free() {
			ptr.free();
			@ptr = null;
		}

		protected Object_t@ ptr;
	};

	class Node : Object {

		void set_name(const String &in name) {
			// cast<Node_t>(ptr).set_name(name);
			// ptr.call(StringName("set_name"), name);
			ptr.call(sn_Node, sn_Node_set_name, name);
		}

		String get_name() const {
			return ptr.call(sn_Node, sn_Node_get_name);
		}

		protected void _make_instance() {
			// @ptr = Node_t();
			@ptr = instance_class(sn_Node);
		}
	}

	class Node2D : Node {


		void set_position(const Vector2 &in pos) {
			ptr.call(sn_Node2D, sn_Node2D_set_position, pos);
			// cast<Node2D_t>(ptr).set_position(pos);
			// ptr.call(StringName("set_position"), pos);
		}

		protected void _make_instance() {
			@ptr = instance_class(sn_Node2D);
		}
	}

	class Sprite : Node2D {

		protected void _make_instance() {
			@ptr = instance_class(sn_Sprite);
		}
	}

	// class Reference : Object {

	// 	protected void _make_instance() {
	// 		@ptr = (ref = Reference_t()).ptr();
	// 	}
	// 	protected REF ref;
	// }

	// class Resource : Reference {

	// 	String get_name() const {
	// 		return ptr.call("get_name");
	// 	}

	// 	void set_name(const String &in p_name) const {
	// 		ptr.call("set_name", p_name);
	// 	}

	// 	Variant opImplConv() const {
	// 		return ref;
	// 	}

	// 	protected void _make_instance() {
	// 		@ptr = (ref = Reference).ptr();
	// 	}
	// }

	// class Theme : Resource {
	// 	void set_color(const String &in name, const String &in type, const Color &in color) {
	// 		ptr.call("set_color", name, type, color);
	// 	}

	// 	Color get_color(const String &in name, const String &in type) const {
	// 		return ptr.call("get_color", name, type);
	// 	}

	// 	protected void _make_instance() {
	// 		@ptr=(ref=ClassDB.instance("Theme")).ptr();
	// 	}
	// }

	// class ImageTexture : Resource {
	// 	protected void _make_instance() {
	// 		@ptr=(ref=ClassDB.instance("ImageTexture")).ptr();
	// 	}
	// }
}

// void test_object() {
// 	godot::Sprite obj;
// 	print(obj.get_class());
// 	obj.set_meta("data", "测试META数据");
// 	if (obj.has_meta("data")) {
// 		print(obj.get_meta("data"));
// 	}
// 	obj.free();
// }

// void test_reference() {
// 	godot::ImageTexture obj;
// 	obj.set_meta("data", "测试META数据");
// 	obj.set_name("巴拉巴拉小魔仙");
// 	if (obj.has_meta("data")) {
// 		print(obj.get_meta("data"));
// 	}
// 	print(obj.get_class());
// 	test_ref_pass(obj);
// 	test_ref_assign_var(obj);
// }

// void test_ref_pass(const godot::Resource &in r) {
// 	print(r.get_name());
// 	print(r.get_meta("data"));
// }

// void test_ref_assign_var(const Variant &in var) {
// 	print(var);
// }

// void test_object_call() {
// 	godot::Theme theme;
// 	theme.set_color("MyColor", "Label", Color());
// 	Variant color = theme.get_color("MyColor", "Label");
// 	print(color);
// }

// void test_variant() {
// 	Variant int_val = 111 + 111;
// 	print(int_val);

// 	Variant float_val = 1.1f * 2.1f;
// 	print(float_val);

// 	Variant double_val = 1.0;
// 	print(double_val);

// 	Variant bool_val = 1 + 1 == 2;
// 	print(bool_val);

// 	Variant str_val = "Hello AngelScript";
// 	print(str_val);

// 	Vector2 vec2;
// 	Variant vec2_val = vec2;
// 	print(vec2_val);

// 	Vector3 vec3;
// 	Variant vec3_val = vec3;
// 	print(vec3_val);

// 	Color c;
// 	Variant color_val = c;
// 	print(color_val);

// 	Rect2 rect;
// 	Variant rect_val = rect;
// 	print(rect_val);

// 	Array arr;
// 	Variant arr_val = arr;
// 	print(arr_val);

// 	Dictionary dict;
// 	Variant dict_val = dict;
// 	print(dict_val);
// }
