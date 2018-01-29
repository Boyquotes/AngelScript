#include "value_types.h"
#include "utils.h"
#include <core/variant.h>
#include <core/reference.h>
#include <core/math/math_2d.h>
#include <core/math/vector3.h>
#include <angelscript.h>


namespace asb {
int _declare_value_types_gen(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE|asGetTypeTraits<String>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("StringName", sizeof(StringName), asOBJ_VALUE|asGetTypeTraits<StringName>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE|asGetTypeTraits<Vector2>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Rect2", sizeof(Rect2), asOBJ_VALUE|asGetTypeTraits<Rect2>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE|asGetTypeTraits<Vector3>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE|asGetTypeTraits<Color>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Array", sizeof(Array), asOBJ_VALUE|asGetTypeTraits<Array>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Dictionary", sizeof(Dictionary), asOBJ_VALUE|asGetTypeTraits<Dictionary>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE|asGetTypeTraits<Variant>()); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectType("REF", sizeof(REF), asOBJ_VALUE|asGetTypeTraits<REF>()); ERR_FAIL_COND_V(r<0, r);
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
	// String ==> Variant
	r = engine->RegisterObjectMethod("String", "String &opAssign(const Variant &in)", asFUNCTION((value_op_assign<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "Variant opImplConv() const", asFUNCTION((value_convert<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// StringName
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const StringName &in)", asFUNCTION(value_copy_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<StringName>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "StringName &opAssign(const StringName &in)", asFUNCTION((value_op_assign<StringName, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION((value_copy_constructor<StringName, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in)", asFUNCTION(value_copy_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Vector2, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2 ==> Variant
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Variant opImplConv() const", asFUNCTION((value_convert<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(const Rect2 &in)", asFUNCTION(value_copy_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Rect2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Rect2 &in)", asFUNCTION((value_op_assign<Rect2, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2 ==> Variant
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Variant opImplConv() const", asFUNCTION((value_convert<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector3
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION(value_copy_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector3>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Vector3, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector3 ==> Variant
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Variant opImplConv() const", asFUNCTION((value_convert<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Color
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Color>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color &in)", asFUNCTION(value_copy_constructor<Color>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Color>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color &opAssign(const Color &in)", asFUNCTION((value_op_assign<Color, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Color ==> Variant
	r = engine->RegisterObjectMethod("Color", "Color &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Color, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Variant opImplConv() const", asFUNCTION((value_convert<Color, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Array
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f(const Array &in)", asFUNCTION(value_copy_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Array &in)", asFUNCTION((value_op_assign<Array, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Array ==> Variant
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant opImplConv() const", asFUNCTION((value_convert<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f(const Dictionary &in)", asFUNCTION(value_copy_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Dictionary>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Dictionary &in)", asFUNCTION((value_op_assign<Dictionary, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary ==> Variant
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Variant opImplConv() const", asFUNCTION((value_convert<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Variant>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant &in)", asFUNCTION(value_copy_constructor<Variant>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Variant>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Variant, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> bool
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const bool &in)", asFUNCTION((value_op_assign<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opImplConv() const", asFUNCTION((value_convert<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> int
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const int &in)", asFUNCTION((value_op_assign<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "int opImplConv() const", asFUNCTION((value_convert<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> float
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const float &in)", asFUNCTION((value_op_assign<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "float opImplConv() const", asFUNCTION((value_convert<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> double
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const double &in)", asFUNCTION((value_op_assign<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "double opImplConv() const", asFUNCTION((value_convert<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> String
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const String &in)", asFUNCTION((value_op_assign<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "String opImplConv() const", asFUNCTION((value_convert<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Color
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Color &in)", asFUNCTION((value_op_assign<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Color opImplConv() const", asFUNCTION((value_convert<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector2
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector2 opImplConv() const", asFUNCTION((value_convert<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector3
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector3 opImplConv() const", asFUNCTION((value_convert<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// REF
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f(const REF &in)", asFUNCTION(value_copy_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<REF>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const REF &in)", asFUNCTION((value_op_assign<REF, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// REF ==> Variant
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const Variant &in)", asFUNCTION((value_op_assign<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "Variant opImplConv() const", asFUNCTION((value_convert<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	return r;
}
}
