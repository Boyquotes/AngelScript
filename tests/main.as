void print_line(const String &in p_line) {
	print(p_line);
}

void main() {
	print_line("Hello" + ":" + "你好");
	check("1+1=2",  1 + 1 == 2);
}
