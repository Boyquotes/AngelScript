#include "objects.h"
#include "utils.h"
#include <core/map.h>
#include <core/string_db.h>
#include <core/method_bind.h>
#include <angelscript.h>
#include <core/object.h>
#include <core/reference.h>
#include <scene/main/node.h>
#include <scene/2d/sprite.h>
#include <core/os/os.h>
#include "../angelscript.h"

#include <editor/doc/doc_data.h>

namespace asb {

// Convert String to const char *
#define STR_G2C(str) (str).utf8().get_data()
// Godot classe to AngelScript binding class name
#define CLS_G2AS(m_class) (#m_class)

Map<uint32_t, MethodBind*> method_cache;
Map<uint32_t, ClassDB::ClassInfo*> class_cache;
Map<uint32_t, const StringName* > stringname_cache;

int setup_api_cache(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;

	uint32_t class_id  = 1U;
	uint32_t method_id = 100000U;

	const StringName *class_key = NULL;
	while (class_key = ClassDB::classes.next(class_key)) {

		ClassDB::ClassInfo * class_info = ClassDB::classes.getptr(*class_key);
		Map<uint32_t, ClassDB::ClassInfo*>::Element * E = class_cache.insert(class_id, class_info);
		String class_name_declare = String("const uint id_") + (String)(*class_key);
		r = engine->RegisterGlobalProperty(STR_G2C(class_name_declare), const_cast<uint32_t*>(&(E->key()))); ERR_FAIL_COND_V(r<0, r);

		const StringName *method_key = NULL;
		while (method_key = class_info->method_map.next(method_key)) {
			Map<uint32_t, MethodBind*>::Element *E = method_cache.insert(method_id, class_info->method_map[*method_key]);
			String method_name_declear = String(class_name_declare) + "_" + (String)(*method_key);
			r = engine->RegisterGlobalProperty(STR_G2C(method_name_declear), const_cast<uint32_t*>(&(E->key()))); ERR_FAIL_COND_V(r<0, r);

			stringname_cache[method_id] = method_key;
			method_id++;
		}
		stringname_cache[class_id] = class_key;
		class_id++;
	}
	return r;
}

int declare_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = engine->SetDefaultNamespace("bindings"); ERR_FAIL_COND_V(r<0, r);
	r = setup_api_cache(engine);  ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType(CLS_G2AS(Object), 0, asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r);
	r = engine->SetDefaultNamespace(""); ERR_FAIL_COND_V(r<0, r);
	return r;
}

void godot_instance_class(asIScriptGeneric * gen);
void godot_icall(asIScriptGeneric * gen);
REF& reference_from(Object* p_obj, REF *p_this);
Object* get_reference_ptr(REF * p_this);

int define_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = engine->SetDefaultNamespace("bindings"); ERR_FAIL_COND_V(r<0, r);
	const char * OBJECT_CLS_CNAME = "bindings::Object";
	const String OBJECT_CLS_REF_NAME = "bindings::Object@";

	// Object class as the base class of everything in Godot
	r = engine->RegisterObjectBehaviour(OBJECT_CLS_CNAME, asBEHAVE_FACTORY, STR_G2C(OBJECT_CLS_REF_NAME + " f()"), asFUNCTION((object_factory<Object>)), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "void free()", asFUNCTION((object_free<Object>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r <0, r);
	// Object <==> Variant
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant opImplConv() const", asFUNCTION((object_convert<Object, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", STR_G2C(OBJECT_CLS_REF_NAME + " opImplConv() const"), asFUNCTION((value_convert<Variant, Object*>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Reference* ==> REF
	r = engine->RegisterObjectMethod("REF", STR_G2C(String("REF &opAssign(") + OBJECT_CLS_REF_NAME + ")"), asFUNCTION(reference_from), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", STR_G2C(OBJECT_CLS_REF_NAME + " ptr()"), asFUNCTION(get_reference_ptr), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Instance classes	by class uid
	r = engine->RegisterGlobalFunction(STR_G2C(OBJECT_CLS_REF_NAME + " instance_class(const uint &in)"), asFUNCTION(godot_instance_class), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	// godot_icall
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant godot_icall(const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(godot_icall), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	// exit godot namespace
	r = engine->SetDefaultNamespace(""); ERR_FAIL_COND_V(r<0, r);

	// FIXME: MOVE THIS to tools
//	if (FileAccessRef f = FileAccess::open("godot.gen.as", FileAccess::WRITE)) {
//		f->store_string(get_binding_script_content());
//		f->flush();
//		f->close();
//	}

	return r;
}


void godot_icall(asIScriptGeneric * gen) {

	static const int MIN_ARG_COUNT = 1;
	static const int MAX_ARG_COUNT = 11;

	int arg_count = gen->GetArgCount();
	ERR_FAIL_COND(arg_count < MIN_ARG_COUNT);

	Object *self = static_cast<Object*>(gen->GetObject());
	const uint32_t * method_id =	static_cast<const uint32_t*>(gen->GetArgAddress(0));
	ERR_FAIL_COND(!self|| !method_id);

	Variant ret;
	Variant::CallError err;
	if (Map<uint32_t, MethodBind*>::Element * E = method_cache.find(*method_id)) {
		MethodBind * method = E->get();

		if (arg_count == MIN_ARG_COUNT) {
			ret = method->call(self, NULL, 0, err);
		} else if (arg_count <= MAX_ARG_COUNT) {
			if (arg_count == MIN_ARG_COUNT + 1) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT))
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 2) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1))
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 3) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 4) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 5) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 6) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 7) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 8) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 7)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 9) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 7)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 8)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 10) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 7)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 8)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 9)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 11) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 7)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 8)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 9)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 10)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			} else if (arg_count == MIN_ARG_COUNT + 12) {
				const Variant* args [] = {
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 1)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 2)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 3)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 4)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 5)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 6)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 7)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 8)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 9)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 10)),
					static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT + 11)),
				};
				ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
			}
		} else {
			err.error = Variant::CallError::CALL_ERROR_TOO_MANY_ARGUMENTS;
			err.argument = -1;
		}
	} else {
		err.error = Variant::CallError::CALL_ERROR_INVALID_METHOD;
		err.argument = -1;
	}
	ERR_FAIL_COND(err.error != Variant::CallError::CALL_OK);
	gen->SetReturnObject(&ret);
}

void godot_instance_class(asIScriptGeneric * gen) {

	ERR_FAIL_COND(gen->GetArgCount() != 1);
	const uint32_t* class_id = static_cast<const uint32_t*>(gen->GetArgAddress(0));
	if (Map<uint32_t, ClassDB::ClassInfo*>::Element *E = class_cache.find(*class_id)) {
		Object * obj = NULL;
		if (E->get() && E->get()->creation_func) {
			obj = E->get()->creation_func();
		}
		gen->SetReturnObject(obj);
	} else {
		gen->SetReturnObject(NULL);
		ERR_FAIL();
	}
}

REF& reference_from(Object* p_obj, REF *p_this) {
	*p_this = REF(Object::cast_to<Reference>(p_obj));
	return *p_this;
}

Object* get_reference_ptr(REF * p_this) {
	return p_this->ptr();
}

String get_binding_script_content() {
	static String script_bindings;
	if (!script_bindings.empty()) {
		return script_bindings;
	}

	static const String FILE_TEMPLATE = "// THIS FILE IS GENERATED BY TOO DO NOT MODIFY\n"
										"namespace godot {\n"
										"{classes}\n"
										"}";
	static const String OBJECT_TEMPLATE = R"(
	{class_doc}
	class {class}{inherits} {
		{methods}

		protected void _make_instance() {
			@ptr = bindings::instance_class(bindings::id_{class});
		}
		{extention}
	})";

	static const String REFERENCE_TEMPLATE = R"(
	{class_doc}
	class {class}{inherits} {
		{methods}
		protected void _make_instance() {
			@ptr = (ref = bindings::instance_class(bindings::id_{class})).ptr();
		}
		{extention}
	})";

	static const String METHOD_TEMPLATE = R"(
		{method_doc}
		{permission}{return_type} {method_name}({params_list}) {qualifier}{
			{return}ptr.godot_icall(bindings::id_{class}_{method_name_raw}{params});
		})";
	static const String METHOD_RO_TEMPLATE = R"(
		{method_doc}
		{permission}{return_type} {method_name}({params_list}) {qualifier}{
			{tmp_type} ret = ptr.godot_icall(bindings::id_{class}_{method_name_raw}{params});
			{return} ret;
		})";
	static const String VMETHOD_TEMPLATE = R"(
		{method_doc}
		{permission}{return_type} {method_name}({params_list}) {qualifier}{
			{return}
		})";
	static const String OBJECT_EXT_TEMPLATE = R"(
		void free() {
			ptr.free();
		}

		Variant opImplConv() const {
			return @ptr;
		}

		void opAssign(const Variant &in ptr) {
			@this.ptr = ptr;
		}

		Object() {
			_make_instance();
		}

		protected bindings::Object@ ptr;
	)";
	static const String REFERENCE_EXT_TEMPLATE = R"(
		Variant opImplConv() const {
			return ref;
		}

		void opAssign(const Variant &in ref) {
			@ptr = (this.ref = ref).ptr();
		}

		protected REF ref;
	)";

	static Map<String, String> vmethod_return_exp;
	vmethod_return_exp["int"] = "return 0;";
	vmethod_return_exp["void"] = "";
	vmethod_return_exp["float"] = "return 0;";
	vmethod_return_exp["bool"] = "return false;";

	List<String> keywords;
	AngelScriptLanguage::get_singletion()->get_reserved_words(&keywords);

	String classes = "";
	const StringName ReferenceName = StringName("Reference");

	const StringName *class_key = NULL;
	while (class_key = ClassDB::classes.next(class_key)) {

		ClassDB::ClassInfo * cls = ClassDB::classes.getptr(*class_key);
		// FIXME: How about this class ?
		if (*class_key == "WeakRef") {
			continue;
		}


		Dictionary class_info;
		class_info["class"] = (String)(*class_key);
		String inherits = cls->inherits;
		class_info["inherits"] = inherits.empty() ? "" : String(" : ") + inherits;
		class_info["class_doc"] = "";
		class_info["extention"] = "";
		if ((*class_key) == "Object") {
			class_info["extention"] = OBJECT_EXT_TEMPLATE;
		} else if ((*class_key) == "Reference") {
			class_info["extention"] = REFERENCE_EXT_TEMPLATE;
		}

		String methods = "";
		List<MethodInfo> method_list;
		ClassDB::get_method_list(*class_key, &method_list, true, false);
		for (List<MethodInfo>::Element * E = method_list.front(); E; E = E->next()) {

			const MethodInfo& mi = E->get();

			if (*(class_key) == "Object" && mi.name == "free") {
				continue;
			}

			bool has_ret_val = false;
			MethodBind **mb = cls->method_map.getptr(StringName(mi.name));
			has_ret_val = (mb && *mb) && (*mb)->has_return();

			Dictionary method_info;
			method_info["class"] = (String)(*class_key);
			method_info["method_name_raw"] = mi.name;

			String method_name = mi.name;
			if (keywords.find(method_name) != NULL) {
				method_name = method_name.capitalize();
			}
			method_info["method_name"] = method_name;

			String ret_type = Variant::get_type_name(mi.return_val.type);
			ret_type = (ret_type == "Object") ? (String)mi.return_val.class_name : ret_type;
			if (ret_type == Variant::get_type_name(Variant::NIL)) {
				ret_type = has_ret_val ? "Variant" : "void";
			}
			ret_type = ClassDB::class_exists(ret_type) ? ret_type + "@" : ret_type;
			ret_type = ret_type.empty() ? "Variant" : ret_type;
			method_info["return_type"] = ret_type;
			method_info["tmp_type"] = ret_type.replace("@", "");
			method_info["return"] = ret_type == "void" ? "" : "return ";
			method_info["qualifier"] = mi.flags & MethodFlags::METHOD_FLAG_CONST ? "const " : "";
			method_info["permission"] = mi.name.begins_with("_") ? "protected " : "";
			method_info["method_doc"] = "";

			// Vector<StringName> arg_names = mb->get_argument_names();
			String params_list = "";
			String params = "";
			for (int i = 0; i < mi.arguments.size(); i++) {

				const PropertyInfo& pi = mi.arguments[i];

				String arg_type = Variant::get_type_name(pi.type);
				arg_type = (arg_type == Variant::get_type_name(Variant::NIL)) ? "Variant" : arg_type;
				if (arg_type == "Object") {
					String type = pi.class_name;
					arg_type = type.empty() ? "Object@" : (String)pi.class_name + "@";
				} else {
					if (arg_type == "bool" || arg_type == "int" || arg_type == "float") {
						arg_type = arg_type;
					} else {
						arg_type = String("const ") + arg_type + " &in";
					}
				}

				String arg_name = pi.name;
				if (keywords.find(arg_name) != NULL) {
					arg_name = arg_name.capitalize();
				}

				params_list += arg_type;
				params_list += " ";
				params_list += arg_name;
				params += arg_name;
				if (i < mi.arguments.size() -1) {
					params += ", ";
					params_list += ", ";
				}
			}
			method_info["params_list"] = params_list;
			method_info["params"] = params.empty() ? params : String(", ") + params;

			if (mi.flags & MethodFlags::METHOD_FLAG_VIRTUAL) {
				if (vmethod_return_exp.has(ret_type)) {
					method_info["return"] = vmethod_return_exp[ret_type];
				} else if (ret_type.ends_with("@")) {
					method_info["return"] = "return null;";
				} else {
					method_info["return"] = String("return ") + ret_type + "();";
				}
				methods += VMETHOD_TEMPLATE.format(method_info);
			} else {
				methods += ret_type.ends_with("@") ? METHOD_RO_TEMPLATE.format(method_info) : METHOD_TEMPLATE.format(method_info);
			}
		}

		class_info["methods"] = methods;
		if (ClassDB::is_parent_class(*class_key, ReferenceName))
			classes += REFERENCE_TEMPLATE.format(class_info);
		else if (*class_key == "Object")
			classes += OBJECT_TEMPLATE.format(class_info).replace("bindings::instance_class(bindings::id_Object)", "bindings::Object();");
		else
			classes += OBJECT_TEMPLATE.format(class_info);
	}
	Dictionary file_info;
	file_info["classes"] = classes;
	script_bindings = FILE_TEMPLATE.format(file_info);
	return script_bindings;
}

}


