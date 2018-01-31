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
#define CLS_G2AS(m_class) (#m_class "_t")

// Declar object classes
#define DECAL_CLASS(engine, m_class, m_inherits)                                                                   \
{                                                                                                                  \
	const char* class_name = CLS_G2AS(m_class);                                                                    \
	const String class_ref_name = STR_G2C(String(class_name) + "@");                                               \
	const char* base_name  = CLS_G2AS(m_inherits);                                                                 \
	const String base_ref_name = STR_G2C(String(base_name) + "@");                                                 \
	const char* object_name  = CLS_G2AS(Object);                                                                   \
	const String object_ref_name = STR_G2C(String(object_name) + "@");                                             \
	r = engine->RegisterObjectType(class_name, 0, asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r);               \
	r = engine->RegisterObjectMethod(base_name,  STR_G2C(class_ref_name + " opCast()"),	  asFUNCTION((object_convert<m_inherits, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(class_name, STR_G2C(base_ref_name + " opImplCast()"), asFUNCTION((object_convert<m_class, m_inherits>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(base_name,  STR_G2C(String("const ") + class_ref_name + " opCast() const"), asFUNCTION((object_convert<m_inherits, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(class_name, STR_G2C(String("const ") + base_ref_name + " opImplCast() const"), asFUNCTION((object_convert<m_class, m_inherits>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	if (String(object_name) != String(base_name)) {																	\
		r = engine->RegisterObjectMethod(object_name,  STR_G2C(class_ref_name + " opCast()"),	  asFUNCTION((object_convert<Object, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
		r = engine->RegisterObjectMethod(class_name, STR_G2C(object_ref_name + " opImplCast()"), asFUNCTION((object_convert<m_class, Object>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
		r = engine->RegisterObjectMethod(object_name,  STR_G2C(String("const ") + class_ref_name + " opCast() const"), asFUNCTION((object_convert<Object, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
		r = engine->RegisterObjectMethod(class_name, STR_G2C(String("const ") + object_ref_name + " opImplCast() const"), asFUNCTION((object_convert<m_class, Object>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	}																												\
}

#define DEFINE_CLASS(engine, m_class)                                                                               \
{                                                                                                                   \
	r = engine->RegisterObjectBehaviour(CLS_G2AS(m_class), asBEHAVE_FACTORY, STR_G2C(String(CLS_G2AS(m_class)) + "@ f()"), asFUNCTION((object_factory<m_class>)), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r); \
}

Map<uint32_t, ClassDB::ClassInfo*> class_cache;
Map<uint32_t, Map<uint32_t, MethodBind*> > method_cache;
Map<uint32_t, const StringName* > uid_string_name_map;

int setup_api_cache(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;

	uint32_t class_id = 0U;
	uint32_t method_id = 10000U;
	const StringName *class_key = NULL;
	while (class_key = ClassDB::classes.next(class_key)) {

		ClassDB::ClassInfo * class_info = ClassDB::classes.getptr(*class_key);
		Map<uint32_t, ClassDB::ClassInfo*>::Element * E = class_cache.insert(class_id, class_info);
		String class_name_declare = String("const uint sn_") + (String)(*class_key);
		r = engine->RegisterGlobalProperty(STR_G2C(class_name_declare), const_cast<uint32_t*>(&(E->key()))); ERR_FAIL_COND_V(r<0, r);

		const StringName *method_key = NULL;
		while (method_key = class_info->method_map.next(method_key)) {
			if (!method_cache.has(class_id)) {
				method_cache[class_id] = Map<uint32_t, MethodBind*>();
			}

			Map<uint32_t, MethodBind*>::Element *E = method_cache[class_id].insert(method_id, class_info->method_map[*method_key]);
			String method_name_declear = String(class_name_declare) + "_" + (String)(*method_key);
			r = engine->RegisterGlobalProperty(STR_G2C(method_name_declear), const_cast<uint32_t*>(&(E->key()))); ERR_FAIL_COND_V(r<0, r);

			uid_string_name_map[method_id] = method_key;
			method_id++;
		}
		uid_string_name_map[class_id] = class_key;
		class_id++;
	}
	return r;
}

int declare_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = setup_api_cache(engine);  ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType(CLS_G2AS(Object), 0, asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r);

	return r;
}

void instance_class(asIScriptGeneric * gen);
void object_call(asIScriptGeneric * gen);
REF& reference_from(Object* p_obj, REF *p_this);
Object* get_reference_ptr(REF * p_this);

int define_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	const char * OBJECT_CLS_CNAME = CLS_G2AS(Object);
	const String OBJECT_CLS_REF_NAME = String(OBJECT_CLS_CNAME) + "@";

	r = engine->RegisterGlobalFunction(STR_G2C(OBJECT_CLS_REF_NAME + " instance_class(const uint &in)"), asFUNCTION(instance_class), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	// Object methods
	r = engine->RegisterObjectBehaviour(OBJECT_CLS_CNAME, asBEHAVE_FACTORY, STR_G2C(OBJECT_CLS_REF_NAME + " f()"), asFUNCTION((object_factory<Object>)), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "void free()", asFUNCTION((object_free<Object>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r <0, r);
	// Object::call
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const uint &in, const uint &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	// FIXME: We don't need that right?
	// Object <==> Variant
	//	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME,  "Variant opImplConv() const", asFUNCTION((as_value_convert<Object*, Variant>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	//	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME,  "Variant opConv() const", asFUNCTION((as_value_convert<Object*, Variant>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	//	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const _Object@)", asFUNCTION((as_value_op_assign_raw<Variant, Object*>)),	asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	//	r = engine->RegisterObjectMethod("Variant", "_Object@ opImplConv() const",  asFUNCTION((as_value_convert<Variant, Object*>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	//	r = engine->RegisterObjectMethod("Variant", "_Object@ opConv() const",		 asFUNCTION((as_value_convert<Variant, Object*>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);

	// Object* to REF
	r = engine->RegisterObjectMethod("REF", STR_G2C(String("REF &opAssign(") + OBJECT_CLS_REF_NAME + ")"), asFUNCTION(reference_from), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", STR_G2C(OBJECT_CLS_REF_NAME + " ptr()"), asFUNCTION(get_reference_ptr), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// TODO: Define classes here
//	DEFINE_CLASS(engine, Reference);
//	DEFINE_CLASS(engine, Node);
//	r = engine->RegisterObjectMethod(CLS_G2AS(Node), "void set_name(const String &in)", asMETHOD(Node, set_name), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
//	DEFINE_CLASS(engine, Node2D);
//	r = engine->RegisterObjectMethod(CLS_G2AS(Node2D), "void set_position(const Vector2 &in)", asMETHOD(Node2D, set_position), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
//	DEFINE_CLASS(engine, Sprite);
	return r;
}


void object_call(asIScriptGeneric * gen) {

	int arg_count = gen->GetArgCount();
	const int MIN_ARG_COUNT = 2;
	ERR_FAIL_COND(arg_count < MIN_ARG_COUNT);

	Variant ret;

	Object *self = static_cast<Object*>(gen->GetObject());
	const uint32_t * class_id  =	static_cast<const uint32_t*>(gen->GetArgAddress(0));
	const uint32_t * method_id =	static_cast<const uint32_t*>(gen->GetArgAddress(1));


	MethodBind * method = method_cache[*class_id][*method_id];
	Variant::CallError err;

	if (arg_count == MIN_ARG_COUNT) {
		ret = method->call(self, NULL, 0, err);
	} else if (arg_count <= VARIANT_ARG_MAX + MIN_ARG_COUNT) {
		if (arg_count == MIN_ARG_COUNT + 1) {
			const Variant* args [] = {
				static_cast<Variant*>(gen->GetArgObject(MIN_ARG_COUNT))
			};
			ret = method->call(self, args, arg_count - MIN_ARG_COUNT, err);
		}
//			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))));
//		else if (arg_count == MIN_ARG_COUNT + 2)
//			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))));
//		else if (arg_count == MIN_ARG_COUNT + 3)
//			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))));
//		else if (arg_count == MIN_ARG_COUNT + 4)
//			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))), *(static_cast<Variant*>(gen->GetArgObject(4))));
//		else if (arg_count == MIN_ARG_COUNT + 5)
//			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))), *(static_cast<Variant*>(gen->GetArgObject(4))), *(static_cast<Variant*>(gen->GetArgObject(5))));
	} else if (arg_count > VARIANT_ARG_MAX + MIN_ARG_COUNT) {
//		Array arr;
//		arr.resize(arg_count - 1);
//		for (int i=1; i<arg_count; i++) {
//			arr[i-1] = *(static_cast<Variant*>(gen->GetArgObject(i)));
//		}
//		ret = self->callv(*method, arr);
	}
	gen->SetReturnObject(&ret);
}

void instance_class(asIScriptGeneric * gen) {

	ERR_FAIL_COND(gen->GetArgCount() != 1);
	const uint32_t* class_id = static_cast<const uint32_t*>(gen->GetArgAddress(0));
	if (Map<uint32_t, ClassDB::ClassInfo*>::Element *E = class_cache.find(*class_id)) {


		Object * obj = class_cache[*class_id]->creation_func();
//		Object * obj = ClassDB::instance(*uid_string_name_map[*class_id]);
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


