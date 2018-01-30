#ifndef AS_BIND_ANGELSCRIPT_H
#define AS_BIND_ANGELSCRIPT_H

#include <core/script_language.h>

class asIScriptEngine;

class AngelScriptLanguage : public ScriptLanguage
{
	static AngelScriptLanguage * singletion;
	asIScriptEngine * engine;
public:
	AngelScriptLanguage();
	~AngelScriptLanguage();

	static AngelScriptLanguage *get_singletion() { return singletion; }
	asIScriptEngine* get_script_engine() { return engine; }

	virtual String get_name() const { return "AngelScript"; }

	/* LANGUAGE FUNCTIONS */
	virtual void init();
	virtual void finish();
	virtual String get_type() const { return "AngelScript"; }
	virtual String get_extension() const { return "as"; }
	virtual Error execute_file(const String &p_path);

	/* EDITOR FUNCTIONS */
	virtual void get_reserved_words(List<String> *p_words) const;
	virtual void get_comment_delimiters(List<String> *p_delimiters) const;
	virtual void get_string_delimiters(List<String> *p_delimiters) const;
	virtual Ref<Script> get_template(const String &p_class_name, const String &p_base_class_name) const;
	virtual void make_template(const String &p_class_name, const String &p_base_class_name, Ref<Script> &p_script);
	virtual bool is_using_templates() { return false; }
	virtual bool validate(const String &p_script, int &r_line_error, int &r_col_error, String &r_test_error, const String &p_path = "", List<String> *r_functions = NULL) const;
	virtual Script *create_script() const;
	virtual bool has_named_classes() const { return true; }
	virtual bool supports_builtin_mode() const { return false; }
	virtual bool can_inherit_from_file() { return false; }
	virtual int find_function(const String &p_function, const String &p_code) const;
	virtual String make_function(const String &p_class, const String &p_name, const PoolStringArray &p_args) const;
	virtual Error open_in_external_editor(const Ref<Script> &p_script, int p_line, int p_col) { return ERR_UNAVAILABLE; }
	virtual bool overrides_external_editor() { return false; }

	virtual Error complete_code(const String &p_code, const String &p_base_path, Object *p_owner, List<String> *r_options, bool &r_force, String &r_call_hint) { return ERR_UNAVAILABLE; }
	virtual Error lookup_code(const String &p_code, const String &p_symbol, const String &p_base_path, Object *p_owner, LookupResult &r_result) { return ERR_UNAVAILABLE; }

	virtual void auto_indent_code(String &p_code, int p_from_line, int p_to_line) const;
	virtual void add_global_constant(const StringName &p_variable, const Variant &p_value);

	/* MULTITHREAD FUNCTIONS */

	//some VMs need to be notified of thread creation/exiting to allocate a stack
	virtual void thread_enter() {}
	virtual void thread_exit() {}

	/* DEBUGGER FUNCTIONS */

	virtual String debug_get_error() const;
	virtual int debug_get_stack_level_count() const;
	virtual int debug_get_stack_level_line(int p_level) const;
	virtual String debug_get_stack_level_function(int p_level) const;
	virtual String debug_get_stack_level_source(int p_level) const;
	virtual void debug_get_stack_level_locals(int p_level, List<String> *p_locals, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1);
	virtual void debug_get_stack_level_members(int p_level, List<String> *p_members, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1);
	virtual ScriptInstance *debug_get_stack_level_instance(int p_level);
	virtual void debug_get_globals(List<String> *p_globals, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1);
	virtual String debug_parse_stack_level_expression(int p_level, const String &p_expression, int p_max_subitems = -1, int p_max_depth = -1);
	virtual Vector<StackInfo> debug_get_current_stack_info() { return Vector<StackInfo>(); }

	virtual void reload_all_scripts();
	virtual void reload_tool_script(const Ref<Script> &p_script, bool p_soft_reload);
	/* LOADER FUNCTIONS */

	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual void get_public_functions(List<MethodInfo> *p_functions) const;
	virtual void get_public_constants(List<Pair<String, Variant> > *p_constants) const;

	virtual void profiling_start();
	virtual void profiling_stop();

	virtual int profiling_get_accumulated_data(ProfilingInfo *p_info_arr, int p_info_max);
	virtual int profiling_get_frame_data(ProfilingInfo *p_info_arr, int p_info_max);

	virtual void *alloc_instance_binding_data(Object *p_object) { return NULL; } //optional, not used by all languages
	virtual void free_instance_binding_data(void *p_data) {} //optional, not used by all languages

	virtual void frame();
};

#endif // AS_BIND_ANGELSCRIPT_H
