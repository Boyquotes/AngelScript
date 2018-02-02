#include "value_types.h"
#include "utils.h"
#include <core/variant.h>
#include <core/reference.h>
#include <core/math/math_2d.h>
#include <core/math/vector3.h>
#include <core/math/aabb.h>
#include <core/math/plane.h>
#include <core/math/transform.h>
#include <angelscript.h>


namespace asb {
int _declare_value_types_gen(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE|asGetTypeTraits<String>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("StringName", sizeof(StringName), asOBJ_VALUE|asGetTypeTraits<StringName>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Vector2>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Rect2", sizeof(Rect2), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Rect2>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Vector3>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Plane", sizeof(Plane), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Plane>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("AABB", sizeof(AABB), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<AABB>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Quat", sizeof(Quat), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Quat>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Basis", sizeof(Basis), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Basis>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Transform", sizeof(Transform), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Transform>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Transform2D", sizeof(Transform2D), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Transform2D>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_APP_CLASS_ALLFLOATS|asOBJ_VALUE|asGetTypeTraits<Color>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("NodePath", sizeof(NodePath), asOBJ_VALUE|asGetTypeTraits<NodePath>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("REF", sizeof(REF), asOBJ_VALUE|asGetTypeTraits<REF>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("RID", sizeof(RID), asOBJ_APP_CLASS_ALLINTS|asOBJ_VALUE|asGetTypeTraits<RID>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Dictionary", sizeof(Dictionary), asOBJ_VALUE|asGetTypeTraits<Dictionary>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Array", sizeof(Array), asOBJ_VALUE|asGetTypeTraits<Array>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolByteArray", sizeof(PoolByteArray), asOBJ_VALUE|asGetTypeTraits<PoolByteArray>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolIntArray", sizeof(PoolIntArray), asOBJ_VALUE|asGetTypeTraits<PoolIntArray>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolRealArray", sizeof(PoolRealArray), asOBJ_VALUE|asGetTypeTraits<PoolRealArray>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolStringArray", sizeof(PoolStringArray), asOBJ_VALUE|asGetTypeTraits<PoolStringArray>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolVector2Array", sizeof(PoolVector2Array), asOBJ_VALUE|asGetTypeTraits<PoolVector2Array>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolVector3Array", sizeof(PoolVector3Array), asOBJ_VALUE|asGetTypeTraits<PoolVector3Array>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("PoolColorArray", sizeof(PoolColorArray), asOBJ_VALUE|asGetTypeTraits<PoolColorArray>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE|asGetTypeTraits<Variant>()); ERR_FAIL_COND_V(r<0, r);
	return r;
}

int _define_value_types_gen(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	// String
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<String>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION(value_copy_constructor<String>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<String>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String &opAssign(const String &in)", asFUNCTION((value_op_assign<String, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// String ==> StringName
	r = engine->RegisterObjectMethod("String", "String &opAssign(const StringName &in)", asFUNCTION((value_op_assign<String, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "StringName opImplConv() const", asFUNCTION((value_convert<String, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "StringName opConv() const", asFUNCTION((value_convert<String, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// String ==> Variant
	r = engine->RegisterObjectMethod("String", "String &opAssign(const Variant &in)", asFUNCTION((value_op_assign<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "Variant opImplConv() const", asFUNCTION((value_convert<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "Variant opConv() const", asFUNCTION((value_convert<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// StringName
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const StringName &in)", asFUNCTION(value_copy_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<StringName>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "StringName &opAssign(const StringName &in)", asFUNCTION((value_op_assign<StringName, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION((value_copy_constructor<StringName, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// StringName ==> Variant
	r = engine->RegisterObjectMethod("StringName", "StringName &opAssign(const Variant &in)", asFUNCTION((value_op_assign<StringName, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "Variant opImplConv() const", asFUNCTION((value_convert<StringName, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "Variant opConv() const", asFUNCTION((value_convert<StringName, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in)", asFUNCTION(value_copy_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Vector2, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION((value_constructor<Vector2, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2 ==> Variant
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Variant opImplConv() const", asFUNCTION((value_convert<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Variant opConv() const", asFUNCTION((value_convert<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(const Rect2 &in)", asFUNCTION(value_copy_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Rect2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Rect2 &in)", asFUNCTION((value_op_assign<Rect2, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((value_constructor<Rect2, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2 ==> Variant
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Variant opImplConv() const", asFUNCTION((value_convert<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Variant opConv() const", asFUNCTION((value_convert<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector3
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION(value_copy_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector3>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Vector3, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION((value_constructor<Vector3, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector3 ==> Variant
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Variant opImplConv() const", asFUNCTION((value_convert<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Variant opConv() const", asFUNCTION((value_convert<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Plane
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Plane>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane &in)", asFUNCTION(value_copy_constructor<Plane>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Plane>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Plane &opAssign(const Plane &in)", asFUNCTION((value_op_assign<Plane, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Plane ==> Variant
	r = engine->RegisterObjectMethod("Plane", "Plane &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Plane, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Variant opImplConv() const", asFUNCTION((value_convert<Plane, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Variant opConv() const", asFUNCTION((value_convert<Plane, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// AABB
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<AABB>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_CONSTRUCT, "void f(const AABB &in)", asFUNCTION(value_copy_constructor<AABB>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<AABB>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB &opAssign(const AABB &in)", asFUNCTION((value_op_assign<AABB, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// AABB ==> Variant
	r = engine->RegisterObjectMethod("AABB", "AABB &opAssign(const Variant &in)", asFUNCTION((value_op_assign<AABB, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Variant opImplConv() const", asFUNCTION((value_convert<AABB, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Variant opConv() const", asFUNCTION((value_convert<AABB, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Quat
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Quat>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f(const Quat &in)", asFUNCTION(value_copy_constructor<Quat>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Quat>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat &opAssign(const Quat &in)", asFUNCTION((value_op_assign<Quat, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Quat ==> Variant
	r = engine->RegisterObjectMethod("Quat", "Quat &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Quat, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Variant opImplConv() const", asFUNCTION((value_convert<Quat, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Variant opConv() const", asFUNCTION((value_convert<Quat, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Basis
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Basis>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(const Basis &in)", asFUNCTION(value_copy_constructor<Basis>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Basis>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis &opAssign(const Basis &in)", asFUNCTION((value_op_assign<Basis, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Basis ==> Variant
	r = engine->RegisterObjectMethod("Basis", "Basis &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Basis, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Variant opImplConv() const", asFUNCTION((value_convert<Basis, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Variant opConv() const", asFUNCTION((value_convert<Basis, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Transform>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_CONSTRUCT, "void f(const Transform &in)", asFUNCTION(value_copy_constructor<Transform>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Transform>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)", asFUNCTION((value_op_assign<Transform, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform ==> Variant
	r = engine->RegisterObjectMethod("Transform", "Transform &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Transform, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Variant opImplConv() const", asFUNCTION((value_convert<Transform, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Variant opConv() const", asFUNCTION((value_convert<Transform, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform2D
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Transform2D>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f(const Transform2D &in)", asFUNCTION(value_copy_constructor<Transform2D>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Transform2D>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D &opAssign(const Transform2D &in)", asFUNCTION((value_op_assign<Transform2D, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform2D ==> Variant
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Transform2D, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Variant opImplConv() const", asFUNCTION((value_convert<Transform2D, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Variant opConv() const", asFUNCTION((value_convert<Transform2D, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Color
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Color>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color &in)", asFUNCTION(value_copy_constructor<Color>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Color>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color &opAssign(const Color &in)", asFUNCTION((value_op_assign<Color, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION((value_constructor<Color, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((value_constructor<Color, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Color ==> Variant
	r = engine->RegisterObjectMethod("Color", "Color &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Color, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Variant opImplConv() const", asFUNCTION((value_convert<Color, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Variant opConv() const", asFUNCTION((value_convert<Color, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// NodePath
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<NodePath>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_CONSTRUCT, "void f(const NodePath &in)", asFUNCTION(value_copy_constructor<NodePath>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<NodePath>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "NodePath &opAssign(const NodePath &in)", asFUNCTION((value_op_assign<NodePath, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// NodePath ==> Variant
	r = engine->RegisterObjectMethod("NodePath", "NodePath &opAssign(const Variant &in)", asFUNCTION((value_op_assign<NodePath, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "Variant opImplConv() const", asFUNCTION((value_convert<NodePath, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "Variant opConv() const", asFUNCTION((value_convert<NodePath, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// REF
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f(const REF &in)", asFUNCTION(value_copy_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<REF>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const REF &in)", asFUNCTION((value_op_assign<REF, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// REF ==> Variant
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const Variant &in)", asFUNCTION((value_op_assign<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "Variant opImplConv() const", asFUNCTION((value_convert<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "Variant opConv() const", asFUNCTION((value_convert<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// RID
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<RID>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_CONSTRUCT, "void f(const RID &in)", asFUNCTION(value_copy_constructor<RID>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<RID>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("RID", "RID &opAssign(const RID &in)", asFUNCTION((value_op_assign<RID, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// RID ==> Variant
	r = engine->RegisterObjectMethod("RID", "RID &opAssign(const Variant &in)", asFUNCTION((value_op_assign<RID, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("RID", "Variant opImplConv() const", asFUNCTION((value_convert<RID, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("RID", "Variant opConv() const", asFUNCTION((value_convert<RID, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f(const Dictionary &in)", asFUNCTION(value_copy_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Dictionary>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Dictionary &in)", asFUNCTION((value_op_assign<Dictionary, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary ==> Variant
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Variant opImplConv() const", asFUNCTION((value_convert<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Variant opConv() const", asFUNCTION((value_convert<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Array
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f(const Array &in)", asFUNCTION(value_copy_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Array &in)", asFUNCTION((value_op_assign<Array, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Array ==> Variant
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant opImplConv() const", asFUNCTION((value_convert<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant opConv() const", asFUNCTION((value_convert<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolByteArray
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolByteArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_CONSTRUCT, "void f(const PoolByteArray &in)", asFUNCTION(value_copy_constructor<PoolByteArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolByteArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "PoolByteArray &opAssign(const PoolByteArray &in)", asFUNCTION((value_op_assign<PoolByteArray, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolByteArray ==> Variant
	r = engine->RegisterObjectMethod("PoolByteArray", "PoolByteArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolByteArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolByteArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "Variant opConv() const", asFUNCTION((value_convert<PoolByteArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolIntArray
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolIntArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_CONSTRUCT, "void f(const PoolIntArray &in)", asFUNCTION(value_copy_constructor<PoolIntArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolIntArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "PoolIntArray &opAssign(const PoolIntArray &in)", asFUNCTION((value_op_assign<PoolIntArray, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolIntArray ==> Variant
	r = engine->RegisterObjectMethod("PoolIntArray", "PoolIntArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolIntArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolIntArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "Variant opConv() const", asFUNCTION((value_convert<PoolIntArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolRealArray
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolRealArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_CONSTRUCT, "void f(const PoolRealArray &in)", asFUNCTION(value_copy_constructor<PoolRealArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolRealArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "PoolRealArray &opAssign(const PoolRealArray &in)", asFUNCTION((value_op_assign<PoolRealArray, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolRealArray ==> Variant
	r = engine->RegisterObjectMethod("PoolRealArray", "PoolRealArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolRealArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolRealArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "Variant opConv() const", asFUNCTION((value_convert<PoolRealArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolStringArray
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolStringArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_CONSTRUCT, "void f(const PoolStringArray &in)", asFUNCTION(value_copy_constructor<PoolStringArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolStringArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "PoolStringArray &opAssign(const PoolStringArray &in)", asFUNCTION((value_op_assign<PoolStringArray, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolStringArray ==> Variant
	r = engine->RegisterObjectMethod("PoolStringArray", "PoolStringArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolStringArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolStringArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "Variant opConv() const", asFUNCTION((value_convert<PoolStringArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector2Array
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolVector2Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_CONSTRUCT, "void f(const PoolVector2Array &in)", asFUNCTION(value_copy_constructor<PoolVector2Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolVector2Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "PoolVector2Array &opAssign(const PoolVector2Array &in)", asFUNCTION((value_op_assign<PoolVector2Array, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector2Array ==> Variant
	r = engine->RegisterObjectMethod("PoolVector2Array", "PoolVector2Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolVector2Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "Variant opImplConv() const", asFUNCTION((value_convert<PoolVector2Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "Variant opConv() const", asFUNCTION((value_convert<PoolVector2Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector3Array
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolVector3Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_CONSTRUCT, "void f(const PoolVector3Array &in)", asFUNCTION(value_copy_constructor<PoolVector3Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolVector3Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "PoolVector3Array &opAssign(const PoolVector3Array &in)", asFUNCTION((value_op_assign<PoolVector3Array, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector3Array ==> Variant
	r = engine->RegisterObjectMethod("PoolVector3Array", "PoolVector3Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolVector3Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "Variant opImplConv() const", asFUNCTION((value_convert<PoolVector3Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "Variant opConv() const", asFUNCTION((value_convert<PoolVector3Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolColorArray
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolColorArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_CONSTRUCT, "void f(const PoolColorArray &in)", asFUNCTION(value_copy_constructor<PoolColorArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolColorArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "PoolColorArray &opAssign(const PoolColorArray &in)", asFUNCTION((value_op_assign<PoolColorArray, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolColorArray ==> Variant
	r = engine->RegisterObjectMethod("PoolColorArray", "PoolColorArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolColorArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolColorArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "Variant opConv() const", asFUNCTION((value_convert<PoolColorArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Variant>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant &in)", asFUNCTION(value_copy_constructor<Variant>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Variant>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Variant, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION((value_constructor<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION((value_constructor<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION((value_constructor<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION((value_constructor<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION((value_constructor<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(String)", asFUNCTION((value_constructor<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> bool
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const bool &in)", asFUNCTION((value_op_assign<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opImplConv() const", asFUNCTION((value_convert<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opConv() const", asFUNCTION((value_convert<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> int
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const int &in)", asFUNCTION((value_op_assign<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "int opImplConv() const", asFUNCTION((value_convert<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "int opConv() const", asFUNCTION((value_convert<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> uint
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const uint &in)", asFUNCTION((value_op_assign<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "uint opImplConv() const", asFUNCTION((value_convert<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "uint opConv() const", asFUNCTION((value_convert<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> float
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const float &in)", asFUNCTION((value_op_assign<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "float opImplConv() const", asFUNCTION((value_convert<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "float opConv() const", asFUNCTION((value_convert<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> double
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const double &in)", asFUNCTION((value_op_assign<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "double opImplConv() const", asFUNCTION((value_convert<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "double opConv() const", asFUNCTION((value_convert<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> String
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const String &in)", asFUNCTION((value_op_assign<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "String opImplConv() const", asFUNCTION((value_convert<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "String opConv() const", asFUNCTION((value_convert<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> StringName
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const StringName &in)", asFUNCTION((value_op_assign<Variant, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "StringName opImplConv() const", asFUNCTION((value_convert<Variant, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "StringName opConv() const", asFUNCTION((value_convert<Variant, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector2
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector2 opImplConv() const", asFUNCTION((value_convert<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector2 opConv() const", asFUNCTION((value_convert<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Rect2
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Rect2 &in)", asFUNCTION((value_op_assign<Variant, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Rect2 opImplConv() const", asFUNCTION((value_convert<Variant, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Rect2 opConv() const", asFUNCTION((value_convert<Variant, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector3
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector3 opImplConv() const", asFUNCTION((value_convert<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector3 opConv() const", asFUNCTION((value_convert<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Plane
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Plane &in)", asFUNCTION((value_op_assign<Variant, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Plane opImplConv() const", asFUNCTION((value_convert<Variant, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Plane opConv() const", asFUNCTION((value_convert<Variant, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> AABB
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const AABB &in)", asFUNCTION((value_op_assign<Variant, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "AABB opImplConv() const", asFUNCTION((value_convert<Variant, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "AABB opConv() const", asFUNCTION((value_convert<Variant, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Quat
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Quat &in)", asFUNCTION((value_op_assign<Variant, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Quat opImplConv() const", asFUNCTION((value_convert<Variant, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Quat opConv() const", asFUNCTION((value_convert<Variant, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Basis
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Basis &in)", asFUNCTION((value_op_assign<Variant, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Basis opImplConv() const", asFUNCTION((value_convert<Variant, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Basis opConv() const", asFUNCTION((value_convert<Variant, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Transform
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Transform &in)", asFUNCTION((value_op_assign<Variant, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform opImplConv() const", asFUNCTION((value_convert<Variant, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform opConv() const", asFUNCTION((value_convert<Variant, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Transform2D
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Transform2D &in)", asFUNCTION((value_op_assign<Variant, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform2D opImplConv() const", asFUNCTION((value_convert<Variant, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform2D opConv() const", asFUNCTION((value_convert<Variant, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Color
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Color &in)", asFUNCTION((value_op_assign<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Color opImplConv() const", asFUNCTION((value_convert<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Color opConv() const", asFUNCTION((value_convert<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> NodePath
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const NodePath &in)", asFUNCTION((value_op_assign<Variant, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "NodePath opImplConv() const", asFUNCTION((value_convert<Variant, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "NodePath opConv() const", asFUNCTION((value_convert<Variant, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> REF
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const REF &in)", asFUNCTION((value_op_assign<Variant, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "REF opImplConv() const", asFUNCTION((value_convert<Variant, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "REF opConv() const", asFUNCTION((value_convert<Variant, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> RID
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const RID &in)", asFUNCTION((value_op_assign<Variant, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "RID opImplConv() const", asFUNCTION((value_convert<Variant, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "RID opConv() const", asFUNCTION((value_convert<Variant, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Dictionary
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Dictionary &in)", asFUNCTION((value_op_assign<Variant, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Dictionary opImplConv() const", asFUNCTION((value_convert<Variant, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Dictionary opConv() const", asFUNCTION((value_convert<Variant, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Array &in)", asFUNCTION((value_op_assign<Variant, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Array opImplConv() const", asFUNCTION((value_convert<Variant, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Array opConv() const", asFUNCTION((value_convert<Variant, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolByteArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolByteArray &in)", asFUNCTION((value_op_assign<Variant, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolByteArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolByteArray opConv() const", asFUNCTION((value_convert<Variant, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolIntArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolIntArray &in)", asFUNCTION((value_op_assign<Variant, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolIntArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolIntArray opConv() const", asFUNCTION((value_convert<Variant, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolRealArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolRealArray &in)", asFUNCTION((value_op_assign<Variant, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolRealArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolRealArray opConv() const", asFUNCTION((value_convert<Variant, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolStringArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolStringArray &in)", asFUNCTION((value_op_assign<Variant, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolStringArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolStringArray opConv() const", asFUNCTION((value_convert<Variant, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolVector2Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolVector2Array &in)", asFUNCTION((value_op_assign<Variant, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector2Array opImplConv() const", asFUNCTION((value_convert<Variant, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector2Array opConv() const", asFUNCTION((value_convert<Variant, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolVector3Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolVector3Array &in)", asFUNCTION((value_op_assign<Variant, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector3Array opImplConv() const", asFUNCTION((value_convert<Variant, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector3Array opConv() const", asFUNCTION((value_convert<Variant, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolColorArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolColorArray &in)", asFUNCTION((value_op_assign<Variant, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolColorArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolColorArray opConv() const", asFUNCTION((value_convert<Variant, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	return r;
}
}
