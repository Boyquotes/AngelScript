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
	context = NULL;
}

AngelScriptLanguage::~AngelScriptLanguage() {

}

void AngelScriptLanguage::init() {
	engine = asCreateScriptEngine();
	engine->SetMessageCallback(asFUNCTION(message_callback), this, asCALL_CDECL);
	context = engine->CreateContext();
	ERR_FAIL_COND(!context);
	ERR_FAIL_COND(asb::bind_angelscript_language(engine) < 0);
}

void AngelScriptLanguage::finish() {
	engine->ShutDownAndRelease();
	engine = NULL;
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

Script *AngelScriptLanguage::create_script() const {
	return memnew(AngelScript);
}

String AngelScriptLanguage::make_function(const String &p_class, const String &p_name, const PoolStringArray &p_args) const {
	return "";
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

String AngelScriptLanguage::debug_get_stack_level_source(int p_level) const {
	return "";
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

void AngelScript::_bind_methods() {

}

bool AngelScript::can_instance() const {
	return false;
}

Ref<Script> AngelScript::get_base_script() const {
	return NULL;
}

StringName AngelScript::get_instance_base_type() const {
	return StringName("");
}

ScriptInstance *AngelScript::instance_create(Object *p_this) {

	AngelScriptInstance * instance = memnew(AngelScriptInstance);
	instance->owner = p_this;
	instance->script = Ref<AngelScript>(this);
	p_this->set_script_instance(instance);
	instances.insert(instance->owner);

	return instance;
}

bool AngelScript::instance_has(const Object *p_this) const {

	bool ret = false;
	{
#ifndef NO_THREADS
	GLOBAL_LOCK_FUNCTION
#endif
		instances.has((Object *)p_this);
	}
	return ret;
}

String AngelScript::get_source_code() const {
	return "";
}

void AngelScript::set_source_code(const String &p_code) {

}

bool AngelScript::has_method(const StringName &p_method) {
	return false;
}

bool AngelScript::is_tool() const {
	return false;
}

ScriptLanguage *AngelScript::get_language() const {
	return AngelScriptLanguage::get_singletion();
}

bool AngelScript::has_script_signal(const StringName &p_signal) const {
	return false;
}

void AngelScript::get_script_signal_list(List<MethodInfo> *r_signals) const {

}

bool AngelScript::get_property_default_value(const StringName &p_property, Variant &r_value) const {
	return false;
}

AngelScript::AngelScript() {

}

AngelScript::~AngelScript() {

}

bool AngelScriptInstance::set(const StringName &p_name, const Variant &p_value) {
	return false;
}

bool AngelScriptInstance::get(const StringName &p_name, Variant &r_ret) const {
	return false;
}

void AngelScriptInstance::get_property_list(List<PropertyInfo> *p_properties) const {

}

Variant::Type AngelScriptInstance::get_property_type(const StringName &p_name, bool *r_is_valid) const {
	return Variant::NIL;
}

bool AngelScriptInstance::has_method(const StringName &p_method) const {
	return false;
}

Variant AngelScriptInstance::call(const StringName &p_method, const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4, const Variant &p_arg5) {
	return NULL;
}

Variant AngelScriptInstance::call(const StringName &p_method, const Variant **p_args, int p_argcount, Variant::CallError &r_error) {
	return NULL;
}

void AngelScriptInstance::call_multilevel(const StringName &p_method, const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4, const Variant &p_arg5) {

}

void AngelScriptInstance::call_multilevel(const StringName &p_method, const Variant **p_args, int p_argcount) {

}

void AngelScriptInstance::call_multilevel_reversed(const StringName &p_method, const Variant **p_args, int p_argcount) {

}

void AngelScriptInstance::notification(int p_notification) {

}

void AngelScriptInstance::refcount_incremented() {
	as_script_instance->AddRef();
}

bool AngelScriptInstance::refcount_decremented() {
	return as_script_instance->Release() == 0;
}

ScriptInstance::RPCMode AngelScriptInstance::get_rpc_mode(const StringName &p_method) const {
	return RPC_MODE_DISABLED;
}

ScriptInstance::RPCMode AngelScriptInstance::get_rset_mode(const StringName &p_variable) const {
	return RPC_MODE_DISABLED;
}

ScriptLanguage *AngelScriptInstance::get_language() {
	return AngelScriptLanguage::get_singletion();
}

AngelScriptInstance::AngelScriptInstance() {
	owner = NULL;
	as_script_instance = NULL;
}

AngelScriptInstance::~AngelScriptInstance() {
	if (script.is_valid() && owner) {
#ifndef NO_THREADS
	GLOBAL_LOCK_FUNCTION
#endif
#ifdef DEBUG_ENABLED
		Set<Object *>::Element *match = script->instances.find(owner);
		CRASH_COND(!match);
		script->instances.erase(match);
#else
		script->instances.erase(owner);
#endif
	}
}
