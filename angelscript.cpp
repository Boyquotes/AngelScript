#include "angelscript.h"
#include <angelscript.h>
#include "bindings/utils.h"
#include "bindings/bindings.h"
#include <core/os/os.h>

AngelScriptLanguage* AngelScriptLanguage::singletion = NULL;

static void message_callback(const asSMessageInfo *msg, void *param) {
	const char *type = "ERR ";
	if(msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if(msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	OS::get_singleton()->print("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

AngelScriptLanguage::AngelScriptLanguage() {
	singletion = this;
	engine = NULL;
}

AngelScriptLanguage::~AngelScriptLanguage() {

}

void AngelScriptLanguage::init() {
	engine = asCreateScriptEngine();
	engine->SetMessageCallback(asFUNCTION(message_callback), this, asCALL_CDECL);
	ERR_FAIL_COND(asb::bind_angelscript_language(engine) < 0);
}

void AngelScriptLanguage::finish() {
	engine->ShutDownAndRelease();
	engine = NULL;
}

Error AngelScriptLanguage::execute_file(const String &p_path) {
	return OK;
}

void AngelScriptLanguage::get_reserved_words(List<String> *p_words) const {
	static const char *_reserved_words[] = {
		"and",
		"abstract",
		"auto",
		"bool",
		"break",
		"case",
		"cast",
		"class",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"enum",
		"external",
		"false",
		"final",
		"float",
		"for",
		"from",
		"funcdef",
		"function",
		"get",
		"if",
		"import",
		"in",
		"inout",
		"int",
		"interface",
		"int8",
		"int16",
		"int32",
		"int64",
		"is",
		"mixin",
		"namespace",
		"not",
		"null",
		"or",
		"out",
		"override",
		"private",
		"protected",
		"return",
		"set",
		"shared",
		"super",
		"switch",
		"this",
		"true",
		"typedef",
		"uint",
		"uint8",
		"uint16",
		"uint32",
		"uint64",
		"void",
		"while",
		"xor",
		0
	};

	const char **w = _reserved_words;
	while (*w) {
		p_words->push_back(*w);
		w++;
	}
}

void AngelScriptLanguage::get_comment_delimiters(List<String> *p_delimiters) const {
	p_delimiters->push_back("//"); // single-line comment
	p_delimiters->push_back("/* */"); // delimited comment
}

void AngelScriptLanguage::get_string_delimiters(List<String> *p_delimiters) const {
	p_delimiters->push_back("' '"); // character literal
	p_delimiters->push_back("\" \""); // regular string literal
}

Ref<Script> AngelScriptLanguage::get_template(const String &p_class_name, const String &p_base_class_name) const {
	return NULL;
}

void AngelScriptLanguage::make_template(const String &p_class_name, const String &p_base_class_name, Ref<Script> &p_script) {

}

bool AngelScriptLanguage::validate(const String &p_script, int &r_line_error, int &r_col_error, String &r_test_error, const String &p_path, List<String> *r_functions) const {
	return false;
}

Script *AngelScriptLanguage::create_script() const {
	return NULL;
}

int AngelScriptLanguage::find_function(const String &p_function, const String &p_code) const {
	return 0;
}

String AngelScriptLanguage::make_function(const String &p_class, const String &p_name, const PoolStringArray &p_args) const {
	return "";
}

void AngelScriptLanguage::auto_indent_code(String &p_code, int p_from_line, int p_to_line) const {

}

void AngelScriptLanguage::add_global_constant(const StringName &p_variable, const Variant &p_value) {

}

String AngelScriptLanguage::debug_get_error() const {
	return "";
}

int AngelScriptLanguage::debug_get_stack_level_count() const {
	return 0;
}

int AngelScriptLanguage::debug_get_stack_level_line(int p_level) const {
	return 0;
}

String AngelScriptLanguage::debug_get_stack_level_function(int p_level) const {
	return "";
}

String AngelScriptLanguage::debug_get_stack_level_source(int p_level) const {
	return "";
}

void AngelScriptLanguage::debug_get_stack_level_locals(int p_level, List<String> *p_locals, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {

}

void AngelScriptLanguage::debug_get_stack_level_members(int p_level, List<String> *p_members, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {

}

ScriptInstance *AngelScriptLanguage::debug_get_stack_level_instance(int p_level) {
	return NULL;
}

void AngelScriptLanguage::debug_get_globals(List<String> *p_globals, List<Variant> *p_values, int p_max_subitems, int p_max_depth) {

}

String AngelScriptLanguage::debug_parse_stack_level_expression(int p_level, const String &p_expression, int p_max_subitems, int p_max_depth) {
	return "";
}

void AngelScriptLanguage::reload_all_scripts() {

}

void AngelScriptLanguage::reload_tool_script(const Ref<Script> &p_script, bool p_soft_reload) {

}

void AngelScriptLanguage::get_recognized_extensions(List<String> *p_extensions) const {

}

void AngelScriptLanguage::get_public_functions(List<MethodInfo> *p_functions) const {

}

void AngelScriptLanguage::get_public_constants(List<Pair<String, Variant> > *p_constants) const {

}

void AngelScriptLanguage::profiling_start() {

}

void AngelScriptLanguage::profiling_stop() {

}

int AngelScriptLanguage::profiling_get_accumulated_data(ScriptLanguage::ProfilingInfo *p_info_arr, int p_info_max) {
		return 0;
}

int AngelScriptLanguage::profiling_get_frame_data(ScriptLanguage::ProfilingInfo *p_info_arr, int p_info_max) {
	return 0;
}

void AngelScriptLanguage::frame() {

}
