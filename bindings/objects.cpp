#include "objects.h"
#include "utils.h"
#include <angelscript.h>
#include <core/object.h>

#include <core/reference.h>
#include <scene/main/node.h>
#include <scene/2d/sprite.h>

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
	r = engine->RegisterObjectType(class_name, sizeof(m_class), asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(base_name,  STR_G2C(class_ref_name + " opCast()"),	  asFUNCTION((object_convert<m_inherits, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(class_name, STR_G2C(base_ref_name + " opImplCast()"), asFUNCTION((object_convert<m_class, m_inherits>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(base_name,  STR_G2C(String("const ") + class_ref_name + " opCast() const"), asFUNCTION((object_convert<m_inherits, m_class>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	r = engine->RegisterObjectMethod(class_name, STR_G2C(String("const ") + base_ref_name + " opImplCast() const"), asFUNCTION((object_convert<m_class, m_inherits>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r); \
	if (String(object_name) != String(base_name)) {																\
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

int declare_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType(CLS_G2AS(Object), sizeof(Object), asOBJ_REF|asOBJ_NOCOUNT); ERR_FAIL_COND_V(r<0, r);
	// TODO: generate classes here
	DECAL_CLASS(engine, Reference, Object);
	DECAL_CLASS(engine, Node, Object);
	DECAL_CLASS(engine, Node2D, Node);
	DECAL_CLASS(engine, Sprite, Node2D);
	return r;
}

void object_call(asIScriptGeneric * gen);
REF& reference_from(Object* p_obj, REF *p_this);
Object* get_reference_ptr(REF * p_this);

int asb::define_object_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;

	const char * OBJECT_CLS_CNAME = CLS_G2AS(Object);
	const char * OBJECT_CLS_REF_CNAME = STR_G2C(String(OBJECT_CLS_CNAME) + "@");
	const String OBJECT_CLS_REF_NAME = OBJECT_CLS_REF_CNAME;
	// Object methods
	r = engine->RegisterObjectBehaviour(OBJECT_CLS_CNAME, asBEHAVE_FACTORY, STR_G2C(OBJECT_CLS_REF_NAME + " f()"), asFUNCTION((object_factory<Object>)), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "void free()", asFUNCTION((object_free<Object>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r <0, r);
	// Object::call
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod(OBJECT_CLS_CNAME, "Variant call(const StringName &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in, const Variant &in)", asFUNCTION(object_call), asCALL_GENERIC); ERR_FAIL_COND_V( r <0, r);
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
	DEFINE_CLASS(engine, Reference);
	DEFINE_CLASS(engine, Node);
	r = engine->RegisterObjectMethod(CLS_G2AS(Node), "void set_name(const String &in)", asMETHODPR(Node, set_name, (const String&), void), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	DEFINE_CLASS(engine, Node2D);	
	r = engine->RegisterObjectMethod(CLS_G2AS(Node2D), "void set_position(const Vector2 &in)", asMETHODPR(Node2D, set_position, (const Vector2&), void), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	DEFINE_CLASS(engine, Sprite);
	return r;
}


static void object_call(asIScriptGeneric * gen) {
	Variant ret;

	int arg_count = gen->GetArgCount();
	Object *self = static_cast<Object*>(gen->GetObject());
	StringName * method = static_cast<StringName*>(gen->GetArgObject(0));

	if (arg_count == 1) {
		ret = self->call(*method);
	} else if (arg_count <= VARIANT_ARG_MAX + 1) {
		if (arg_count == 2)
			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))));
		else if (arg_count == 3)
			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))));
		else if (arg_count == 4)
			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))));
		else if (arg_count == 5)
			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))), *(static_cast<Variant*>(gen->GetArgObject(4))));
		else if (arg_count == 6)
			ret = self->call(*method, *(static_cast<Variant*>(gen->GetArgObject(1))), *(static_cast<Variant*>(gen->GetArgObject(2))), *(static_cast<Variant*>(gen->GetArgObject(3))), *(static_cast<Variant*>(gen->GetArgObject(4))), *(static_cast<Variant*>(gen->GetArgObject(5))));
	} else if (arg_count > VARIANT_ARG_MAX + 1) {
		Array arr;
		arr.resize(arg_count - 1);
		for (int i=1; i<arg_count; i++) {
			arr[i-1] = *(static_cast<Variant*>(gen->GetArgObject(i)));
		}
		ret = self->callv(*method, arr);
	}
	gen->SetReturnObject(&ret);
}

REF& reference_from(Object* p_obj, REF *p_this) {
	*p_this = Ref<Reference>(Object::cast_to<Reference>(p_obj));
	return *p_this;
}

Object* get_reference_ptr(REF * p_this) {
	return p_this->ptr();
}

}


