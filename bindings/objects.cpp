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
	// Object* --> Variant
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant opImplConv() const", asFUNCTION((object_convert<Object, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
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
	// exit godot namespace
	r = engine->SetDefaultNamespace(""); ERR_FAIL_COND_V(r<0, r);
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


		Object * obj = class_cache[*class_id]->creation_func();
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

}


