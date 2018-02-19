#ifndef AS_BIND_ANGELSCRIPT_H
#define AS_BIND_ANGELSCRIPT_H

#include <core/script_language.h>

class asIScriptEngine;
class asIScriptModule;
class asIScriptContext;

class AngelScriptLanguage : public ScriptLanguage {
	static AngelScriptLanguage *singleton;
	asIScriptEngine *engine;
	asIScriptModule *module;
	asIScriptContext *context;

public:
	AngelScriptLanguage();
	~AngelScriptLanguage();

	static AngelScriptLanguage *get_singleton() { return singleton; }
	asIScriptEngine *get_script_engine() const { return engine; }
	asIScriptContext *get_context() const { return context; }
	asIScriptModule *get_module() const { return module; }

	virtual String get_name() const { return "AngelScript"; }

	/* LANGUAGE FUNCTIONS */
	virtual void init();
	virtual void finish();
	virtual String get_type() const { return "AngelScript"; }
	virtual String get_extension() const { return "as"; }
	virtual Error execute_file(const String &p_path) { return ERR_UNAVAILABLE; }

	/* EDITOR FUNCTIONS */
	virtual void get_reserved_words(List<String> *p_words) const;
	virtual void get_comment_delimiters(List<String> *p_delimiters) const;
	virtual void get_string_delimiters(List<String> *p_delimiters) const;
	virtual Ref<Script> get_template(const String &p_class_name, const String &p_base_class_name) const { return NULL; }
	virtual void make_template(const String &p_class_name, const String &p_base_class_name, Ref<Script> &p_script) {}
	virtual bool is_using_templates() { return false; }
	virtual bool validate(const String &p_script, int &r_line_error, int &r_col_error, String &r_test_error, const String &p_path = "", List<String> *r_functions = NULL) const { return false; }
	virtual Script *create_script() const;
	virtual bool has_named_classes() const { return true; }
	virtual bool supports_builtin_mode() const { return false; }
	virtual bool can_inherit_from_file() { return false; }
	virtual int find_function(const String &p_function, const String &p_code) const { return 0; }
	virtual String make_function(const String &p_class, const String &p_name, const PoolStringArray &p_args) const;
	virtual Error open_in_external_editor(const Ref<Script> &p_script, int p_line, int p_col) { return ERR_UNAVAILABLE; }
	virtual bool overrides_external_editor() { return false; }

	virtual Error complete_code(const String &p_code, const String &p_base_path, Object *p_owner, List<String> *r_options, bool &r_force, String &r_call_hint) { return ERR_UNAVAILABLE; }
	virtual Error lookup_code(const String &p_code, const String &p_symbol, const String &p_base_path, Object *p_owner, LookupResult &r_result) { return ERR_UNAVAILABLE; }

	virtual void auto_indent_code(String &p_code, int p_from_line, int p_to_line) const {}
	virtual void add_global_constant(const StringName &p_variable, const Variant &p_value) {}

	/* MULTITHREAD FUNCTIONS */

	//some VMs need to be notified of thread creation/exiting to allocate a stack
	virtual void thread_enter() {}
	virtual void thread_exit() {}

	/* DEBUGGER FUNCTIONS */

	virtual String debug_get_error() const;
	virtual int debug_get_stack_level_count() const;
	virtual int debug_get_stack_level_line(int p_level) const;
	virtual String debug_get_stack_level_function(int p_level) const { return ""; }
	virtual String debug_get_stack_level_source(int p_level) const;
	virtual void debug_get_stack_level_locals(int p_level, List<String> *p_locals, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1) {}
	virtual void debug_get_stack_level_members(int p_level, List<String> *p_members, List<Variant> *p_values, int p_max_subitems = -1, int p_max_depth = -1) {}
	virtual ScriptInstance *debug_get_stack_level_instance(int p_level) { return NULL; }
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

class AngelScript : public Script {
	GDCLASS(AngelScript, Script);

	friend class AngelScriptInstance;
	friend class AngelScriptLanguage;
	Set<Object *> instances;
	asIScriptModule *module;
protected:
	String class_name;
	String class_namespace;

	virtual bool editor_can_reload_from_file() { return false; }
	static void _bind_methods(); // this is handled by editor better
public:
	virtual bool can_instance() const;

	void set_class_name(String p_class_name) { class_name = p_class_name; }
	String get_class_name() const { return class_name; }
	String get_full_class_name() const { return class_namespace + "::" + class_name; }
	virtual Ref<Script> get_base_script() const;

	virtual StringName get_instance_base_type() const;
	virtual ScriptInstance *instance_create(Object *p_this);
	virtual bool instance_has(const Object *p_this) const;

	virtual bool has_source_code() const { return true; }
	virtual String get_source_code() const;
	virtual void set_source_code(const String &p_code);
	virtual Error reload(bool p_keep_state = false) { return ERR_UNAVAILABLE; }

	virtual bool has_method(const StringName &p_method);
	virtual MethodInfo get_method_info(const StringName &p_method) const { return MethodInfo(); }

	virtual bool is_tool() const;

	virtual ScriptLanguage *get_language() const;

	virtual bool has_method(const StringName &p_method) const { return false; }
	virtual bool has_script_signal(const StringName &p_signal) const;
	virtual void get_script_signal_list(List<MethodInfo> *r_signals) const;

	virtual bool get_property_default_value(const StringName &p_property, Variant &r_value) const;

	virtual void update_exports() {} //editor tool
	virtual void get_script_method_list(List<MethodInfo> *p_list) const {}
	virtual void get_script_property_list(List<PropertyInfo> *p_list) const {}

	virtual int get_member_line(const StringName &p_member) const { return -1; }

	virtual void get_constants(Map<StringName, Variant> *p_constants) {}
	virtual void get_members(Set<StringName> *p_constants) {}

	AngelScript();
	~AngelScript();
};

class asIScriptObject;
class AngelScriptInstance : public ScriptInstance {
	friend class AngelScript;
	friend class AngelScriptLanguage;
	asIScriptObject *as_script_instance;
	Ref<AngelScript> script;
	Object *owner;

public:
	virtual bool set(const StringName &p_name, const Variant &p_value);
	virtual bool get(const StringName &p_name, Variant &r_ret) const;
	virtual void get_property_list(List<PropertyInfo> *p_properties) const;
	virtual Variant::Type get_property_type(const StringName &p_name, bool *r_is_valid = NULL) const;

	virtual Object *get_owner() { return owner; }
	virtual void get_method_list(List<MethodInfo> *p_list) const {}
	virtual bool has_method(const StringName &p_method) const;
	virtual Variant call(const StringName &p_method, VARIANT_ARG_LIST);
	virtual Variant call(const StringName &p_method, const Variant **p_args, int p_argcount, Variant::CallError &r_error);
	virtual void call_multilevel(const StringName &p_method, VARIANT_ARG_LIST);
	virtual void call_multilevel(const StringName &p_method, const Variant **p_args, int p_argcount);
	virtual void call_multilevel_reversed(const StringName &p_method, const Variant **p_args, int p_argcount);
	virtual void notification(int p_notification);

	//this is used by script languages that keep a reference counter of their own
	//you can make make Ref<> not die when it reaches zero, so deleting the reference
	//depends entirely from the script

	virtual void refcount_incremented();
	virtual bool refcount_decremented(); //return true if it can die

	virtual Ref<Script> get_script() const { return script; }

	virtual bool is_placeholder() const { return false; }

	virtual RPCMode get_rpc_mode(const StringName &p_method) const;
	virtual RPCMode get_rset_mode(const StringName &p_variable) const;

	virtual ScriptLanguage *get_language();
	AngelScriptInstance();
	virtual ~AngelScriptInstance();
};

#endif // AS_BIND_ANGELSCRIPT_H
