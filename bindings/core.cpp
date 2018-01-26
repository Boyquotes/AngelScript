#include <core/variant.h>
#include <angelscript.h>
#include <core/ustring.h>
#include <core/map.h>
#include <cassert>
#include "core.h"
#include <core/print_string.h>
#include <core/object.h>
#include <core/class_db.h>
#include <core/reference.h>

int as_declare_core_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType("_Object", sizeof(Object), asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r);
	return r;
}

class ASB_StringFactory : public asIStringFactory {
public:
	ASB_StringFactory() {}
	~ASB_StringFactory() {
		// The script engine must release each string
		// constant that it has requested
		// assert(string_const_cache.size() == 0);
	}

	const void *GetStringConstant(const char *data, asUINT length) {
		String str;
		str.parse_utf8(data, length);
		Map<String, int32_t>::Element *it = string_const_cache.find(str);
		if (it) {
			it->get() += 1;
		}
		else {
			it = string_const_cache.insert(str, 1);
		}
		return reinterpret_cast<const void*>(&(it->key()));
	}

	int ReleaseStringConstant(const void *str) {
		ERR_FAIL_COND_V(!str, asERROR);

		Map<String, int32_t>::Element *it = string_const_cache.find(*reinterpret_cast<const String*>(str));
		ERR_FAIL_COND_V(!it, asERROR);

		it->get() -= 1;
		if (it->get() == 0)
			string_const_cache.erase(it);
		return asSUCCESS;
	}

	int GetRawStringData(const void *str, char *data, asUINT *length) const {
		ERR_FAIL_COND_V(!str, asERROR);

		CharString utf8str = reinterpret_cast<const String*>(str)->utf8();
		if (length) {
			*length = utf8str.size();
		}

		if (data) {
			copymem(data, utf8str.get_data(), utf8str.size());
		}

		return asSUCCESS;
	}

	// TODO: Make sure the access to the string cache is thread safe
	Map<String, int32_t> string_const_cache;
};
static ASB_StringFactory asb_string_factory;

static int as_string_compare(const String &a, const String &b){
	int cmp = 1;
	if( a < b )
		cmp = -1;
	else if( a == b )
		cmp = 0;
	return cmp;
}

int as_register_string(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);

	int r = 0;
	// Factory
	r = engine->RegisterStringFactory("String", &asb_string_factory);                               ERR_FAIL_COND_V( r <0, r);
	// Operators
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL);     ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const", asMETHODPR(String, operator==, (const String&) const, bool), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const", asFUNCTION(as_string_compare), asCALL_CDECL_OBJFIRST);                              ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const", asMETHODPR(String, operator+, (const String&) const, String), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	// Methods
	r = engine->RegisterObjectMethod("String", "int length() const",asMETHODPR(String, length, (void) const, int), asCALL_THISCALL);    ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "bool empty() const", asMETHODPR(String, empty, (void) const, bool), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	return r;
}

#include <core/math/math_2d.h>
static void as_construct_vector2(float x, float y, Vector2 *p_this) {
	memnew_placement(p_this, Vector2(x, y));
}

static int as_vector2_compare(const Vector2 &a, const Vector2 &b){
	int cmp = 1;
	if( a < b )
		cmp = -1;
	else if( a == b )
		cmp = 0;
	return cmp;
}

int as_register_vector2(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;

	// Behaviours
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT,  "void f(float x=0, float y=0)", asFUNCTION(as_construct_vector2), asCALL_CDECL_OBJLAST);				ERR_FAIL_COND_V( r <0, r);
	// Properties
	r = engine->RegisterObjectProperty("Vector2", "float x",     asOFFSET(Vector2, x));      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float width", asOFFSET(Vector2, width));  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float y",     asOFFSET(Vector2, y));      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float height",asOFFSET(Vector2, height)); ERR_FAIL_COND_V( r <0, r);
	// Operators
	r = engine->RegisterObjectMethod("Vector2", "void opAddAssign(const Vector2 &in)",    asMETHODPR(Vector2, operator+=, (const Vector2&), void), asCALL_THISCALL);        ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2 &in) const", asMETHODPR(Vector2, operator==, (const Vector2&) const, bool), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "int opCmp(const Vector2 &in) const",     asFUNCTION(as_vector2_compare), asCALL_CDECL_OBJFIRST);                           ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2 &in) const", asMETHODPR(Vector2, operator+, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Methods
	r = engine->RegisterObjectMethod("Vector2", "float length() const",asMETHODPR(Vector2, length, (void) const, float), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void normalize()", asMETHODPR(Vector2, normalize, (void), void), asCALL_THISCALL);        ERR_FAIL_COND_V( r <0, r);

	return r;
}

void as_free_object(Object* p_this) {
	if (p_this) {
		memdelete(p_this);
	}
}

REF& as_reference_from(Object* p_obj, REF *p_this) {
	*p_this = Ref<Reference>(Object::cast_to<Reference>(p_obj));
	return *p_this;
}

Object* as_get_reference_ptr(REF * p_this) {
	return p_this->ptr();
}

static void as_object_call(asIScriptGeneric * gen) {
	Variant ret;
	int arg_count = gen->GetArgCount();


	Object *self = static_cast<Object*>(gen->GetObject());
	StringName * method = static_cast<StringName*>(gen->GetArgObject(0));

	if (arg_count > 1) {
		Array params;
		params.resize(arg_count - 1);
		for(int i = 1; i < arg_count; i++) {
			Variant * arg = static_cast<Variant*>(gen->GetArgObject(i));
			params[i-1] = *arg;
		}
		ret = self->callv(*method, params);

	} else {
		ret = self->call(*method);
	}
	gen->SetReturnObject(&ret);
}

int as_register_object(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectBehaviour("_Object", asBEHAVE_FACTORY, "_Object@ f()", asFUNCTION((as_object_factory<Object>)), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "String get_class() const", asMETHOD(Object,	get_class), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "String get_save_class() const", asMETHOD(Object,	get_save_class), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "bool is_class() const", asMETHOD(Object,	is_class), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "bool has_meta(const String &in) const", asMETHOD(Object,	has_meta), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "void set_meta(const String &in, const Variant &in)", asMETHOD(Object,	set_meta), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "Variant get_meta(const String &in) const", asMETHOD(Object,	get_meta), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object", "void free()", asFUNCTION(as_free_object), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);

	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	r = engine->RegisterObjectMethod("_Object", "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(as_object_call), asCALL_GENERIC);
	return r;
}

int as_register_reference(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(_Object@)", asFUNCTION(as_reference_from), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "_Object@ ptr()", asFUNCTION(as_get_reference_ptr), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	return r;
}

int as_register_variant(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	// Object <==> Variant
	r = engine->RegisterObjectMethod("_Object",  "Variant opImplConv() const",  asFUNCTION((as_value_convert<Object*, Variant>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_Object",  "Variant opConv() const",	  asFUNCTION((as_value_convert<Object*, Variant>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const _Object@)", asFUNCTION((as_value_op_assign_raw<Variant, Object*>)),	asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "_Object@ opImplConv() const",  asFUNCTION((as_value_convert<Variant, Object*>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "_Object@ opConv() const",		 asFUNCTION((as_value_convert<Variant, Object*>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	return r;
}


#include <core/bind/core_bind.h>
Object* as_instance_object(const StringName& class_name, _ClassDB* p_this) {
	return ClassDB::instance(class_name);
}

int as_register_class_db(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType("_ClassDB", 0, asOBJ_REF | asOBJ_NOCOUNT); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("_ClassDB", "_Object@ instance(const StringName &in)", asFUNCTION(as_instance_object), asCALL_CDECL_OBJLAST);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalProperty("_ClassDB@ ClassDB", Engine::get_singleton()->get_singleton_object("ClassDB"));  ERR_FAIL_COND_V( r <0, r);
	return r;
}

int as_core_binding_manual(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = as_register_string(engine);		ERR_FAIL_COND_V(r<0, r);
	r = as_register_vector2(engine);	ERR_FAIL_COND_V(r<0, r);
	r = as_register_variant(engine);	ERR_FAIL_COND_V(r<0, r);
	r = as_register_object(engine);		ERR_FAIL_COND_V(r<0, r);
	r = as_register_reference(engine);  ERR_FAIL_COND_V(r<0, r);
	r = as_register_class_db(engine);	ERR_FAIL_COND_V(r<0, r);
	return r;
}
