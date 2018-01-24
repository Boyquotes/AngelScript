void print_line(const String &in val) {
	print(val);
}

void main() {

	Variant int_val = 111 + 111;
	print_line(int_val);

	Variant float_val = 1.1f * 2.1f;
	print(float_val);

	Variant double_val = 1.0;
	print(double_val);

	Variant bool_val = 1 + 1 == 2;
	print(bool_val);

	Variant str_val = "Hello AngelScript";
	print(str_val);
}
