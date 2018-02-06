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
	// String ==> Variant
	r = engine->RegisterObjectMethod("String", "String &opAssign(const Variant &in)", asFUNCTION((value_op_assign<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "Variant opImplConv() const", asFUNCTION((value_convert<String, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const", asMETHODPR(String, operator==, (const String&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const", asFUNCTION((value_compare<String, String>)), asCALL_CDECL_OBJFIRST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const", asMETHODPR(String, operator+, (const String&) const, String), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "String& opAddAssign(const String &in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// String methods
	r = engine->RegisterObjectMethod("String", "PoolStringArray bigrams()", asMETHOD(String, bigrams), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String c_escape()", asMETHOD(String, c_escape), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String c_unescape()", asMETHOD(String, c_unescape), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String capitalize()", asMETHOD(String, capitalize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int casecmp_to(const String &in)", asMETHOD(String, casecmp_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String dedent()", asMETHOD(String, dedent), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool empty()", asMETHOD(String, empty), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool ends_with(const String &in)", asMETHOD(String, ends_with), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "void erase(int, int)", asMETHOD(String, erase), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int find_last(const String &in)", asMETHOD(String, find_last), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int findn(const String &in, int arg1=0)", asMETHOD(String, findn), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String format(const Variant &in, const String &in arg1=\"{_}\")", asMETHOD(String, format), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String get_base_dir()", asMETHOD(String, get_base_dir), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String get_basename()", asMETHOD(String, get_basename), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String get_extension()", asMETHOD(String, get_extension), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String get_file()", asMETHOD(String, get_file), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int hex_to_int()", asMETHOD(String, hex_to_int), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String insert(int, const String &in)", asMETHOD(String, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_abs_path()", asMETHOD(String, is_abs_path), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_rel_path()", asMETHOD(String, is_rel_path), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_subsequence_of(const String &in)", asMETHOD(String, is_subsequence_of), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_subsequence_ofi(const String &in)", asMETHOD(String, is_subsequence_ofi), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_valid_float()", asMETHOD(String, is_valid_float), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_valid_html_color()", asMETHOD(String, is_valid_html_color), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_valid_identifier()", asMETHOD(String, is_valid_identifier), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_valid_integer()", asMETHOD(String, is_valid_integer), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool is_valid_ip_address()", asMETHOD(String, is_valid_ip_address), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String json_escape()", asMETHOD(String, json_escape), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String left(int)", asMETHOD(String, left), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int length()", asMETHOD(String, length), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool match(const String &in)", asMETHOD(String, match), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "bool matchn(const String &in)", asMETHOD(String, matchn), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "PoolByteArray md5_buffer()", asMETHOD(String, md5_buffer), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String md5_text()", asMETHOD(String, md5_text), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int nocasecmp_to(const String &in)", asMETHOD(String, nocasecmp_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int ord_at(int)", asMETHOD(String, ord_at), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String pad_decimals(int)", asMETHOD(String, pad_decimals), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String pad_zeros(int)", asMETHOD(String, pad_zeros), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String percent_decode()", asMETHOD(String, percent_decode), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String percent_encode()", asMETHOD(String, percent_encode), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String plus_file(const String &in)", asMETHOD(String, plus_file), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String replacen(const String &in, const String &in)", asMETHOD(String, replacen), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int rfind(const String &in, int arg1=-1)", asMETHOD(String, rfind), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "int rfindn(const String &in, int arg1=-1)", asMETHOD(String, rfindn), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String right(int)", asMETHOD(String, right), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "PoolByteArray sha256_buffer()", asMETHOD(String, sha256_buffer), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String sha256_text()", asMETHOD(String, sha256_text), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "float similarity(const String &in)", asMETHOD(String, similarity), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "PoolStringArray split(const String &in, bool arg1=true, int arg2=0)", asMETHOD(String, split), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "PoolRealArray split_floats(const String &in, bool arg1=true)", asMETHOD(String, split_floats), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String strip_edges(bool arg0=true, bool arg1=true)", asMETHOD(String, strip_edges), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String substr(int, int)", asMETHOD(String, substr), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "float to_float()", asMETHOD(String, to_float), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String to_lower()", asMETHOD(String, to_lower), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String to_upper()", asMETHOD(String, to_upper), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String xml_escape()", asMETHOD(String, xml_escape), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("String", "String xml_unescape()", asMETHOD(String, xml_unescape), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// StringName
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const StringName &in)", asFUNCTION(value_copy_constructor<StringName>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<StringName>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "StringName &opAssign(const StringName &in)", asFUNCTION((value_op_assign<StringName, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("StringName", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION((value_copy_constructor<StringName, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// StringName ==> Variant
	r = engine->RegisterObjectMethod("StringName", "StringName &opAssign(const Variant &in)", asFUNCTION((value_op_assign<StringName, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("StringName", "Variant opImplConv() const", asFUNCTION((value_convert<StringName, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in)", asFUNCTION(value_copy_constructor<Vector2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Vector2, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION((value_constructor<Vector2, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector2 ==> Variant
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Variant opImplConv() const", asFUNCTION((value_convert<Vector2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2 &in) const", asMETHODPR(Vector2, operator==, (const Vector2&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "int opCmp(const Vector2 &in) const", asFUNCTION((value_compare<Vector2, Vector2>)), asCALL_CDECL_OBJFIRST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2 &in) const", asMETHODPR(Vector2, operator+, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void opAddAssign(const Vector2 &in)", asMETHODPR(Vector2, operator+=, (const Vector2&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2 &in) const", asMETHODPR(Vector2, operator-, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void opSubAssign(const Vector2 &in)", asMETHODPR(Vector2, operator-=, (const Vector2&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2 &in) const", asMETHODPR(Vector2, operator*, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void opMulAssign(const Vector2 &in)", asMETHODPR(Vector2, operator*=, (const Vector2&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2 &in) const", asMETHODPR(Vector2, operator/, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Vector2 methods
	r = engine->RegisterObjectMethod("Vector2", "Vector2 abs()", asMETHOD(Vector2, abs), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float angle()", asMETHOD(Vector2, angle), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float angle_to(const Vector2 &in)", asMETHOD(Vector2, angle_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float angle_to_point(const Vector2 &in)", asMETHOD(Vector2, angle_to_point), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float aspect()", asMETHOD(Vector2, aspect), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 bounce(const Vector2 &in)", asMETHOD(Vector2, bounce), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 clamped(float)", asMETHOD(Vector2, clamped), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 cubic_interpolate(const Vector2 &in, const Vector2 &in, const Vector2 &in, float)", asMETHOD(Vector2, cubic_interpolate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float distance_squared_to(const Vector2 &in)", asMETHOD(Vector2, distance_squared_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float distance_to(const Vector2 &in)", asMETHOD(Vector2, distance_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float dot(const Vector2 &in)", asMETHOD(Vector2, dot), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 floor()", asMETHOD(Vector2, floor), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "bool is_normalized()", asMETHOD(Vector2, is_normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float length()", asMETHOD(Vector2, length), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "float length_squared()", asMETHOD(Vector2, length_squared), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 normalized()", asMETHOD(Vector2, normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 reflect(const Vector2 &in)", asMETHOD(Vector2, reflect), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 rotated(float)", asMETHOD(Vector2, rotated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 slide(const Vector2 &in)", asMETHOD(Vector2, slide), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 snapped(const Vector2 &in)", asMETHOD(Vector2, snapped), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 tangent()", asMETHOD(Vector2, tangent), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Rect2
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(const Rect2 &in)", asFUNCTION(value_copy_constructor<Rect2>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Rect2>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Rect2 &in)", asFUNCTION((value_op_assign<Rect2, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((value_constructor<Rect2, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Rect2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in, const Vector2 &in)", asFUNCTION((value_constructor<Rect2, const Vector2&, const Vector2&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2 ==> Variant
	r = engine->RegisterObjectMethod("Rect2", "Rect2 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Variant opImplConv() const", asFUNCTION((value_convert<Rect2, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Rect2 methods
	r = engine->RegisterObjectMethod("Rect2", "Rect2 abs()", asMETHOD(Rect2, abs), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 clip(const Rect2 &in)", asMETHOD(Rect2, clip), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "bool encloses(const Rect2 &in)", asMETHOD(Rect2, encloses), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 expand(const Vector2 &in)", asMETHOD(Rect2, expand), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "float get_area()", asMETHOD(Rect2, get_area), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 grow(float)", asMETHOD(Rect2, grow), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 grow_individual(float, float, float, float)", asMETHOD(Rect2, grow_individual), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 grow_margin(int, float)", asMETHOD(Rect2, grow_margin), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "bool has_no_area()", asMETHOD(Rect2, has_no_area), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "bool has_point(const Vector2 &in)", asMETHOD(Rect2, has_point), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "bool intersects(const Rect2 &in)", asMETHOD(Rect2, intersects), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Rect2", "Rect2 merge(const Rect2 &in)", asMETHOD(Rect2, merge), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Vector3
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION(value_copy_constructor<Vector3>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Vector3>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Vector3, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION((value_constructor<Vector3, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Vector3 ==> Variant
	r = engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Variant opImplConv() const", asFUNCTION((value_convert<Vector3, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3 &in) const", asMETHODPR(Vector3, operator==, (const Vector3&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "int opCmp(const Vector3 &in) const", asFUNCTION((value_compare<Vector3, Vector3>)), asCALL_CDECL_OBJFIRST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3 &in) const", asMETHODPR(Vector3, operator+, (const Vector3&) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3 &in)", asMETHODPR(Vector3, operator+=, (const Vector3&), Vector3&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3 &in) const", asMETHODPR(Vector3, operator-, (const Vector3&) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3 &in)", asMETHODPR(Vector3, operator-=, (const Vector3&), Vector3&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3 &in) const", asMETHODPR(Vector3, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3 &in)", asMETHODPR(Vector3, operator*=, (const Vector3&), Vector3&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3 &in) const", asMETHODPR(Vector3, operator/, (const Vector3&) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3 &in)", asMETHODPR(Vector3, operator/=, (const Vector3&), Vector3&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Vector3 methods
	r = engine->RegisterObjectMethod("Vector3", "Vector3 abs()", asMETHOD(Vector3, abs), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float angle_to(const Vector3 &in)", asMETHOD(Vector3, angle_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 bounce(const Vector3 &in)", asMETHOD(Vector3, bounce), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 ceil()", asMETHOD(Vector3, ceil), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 cross(const Vector3 &in)", asMETHOD(Vector3, cross), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 cubic_interpolate(const Vector3 &in, const Vector3 &in, const Vector3 &in, float)", asMETHOD(Vector3, cubic_interpolate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float distance_squared_to(const Vector3 &in)", asMETHOD(Vector3, distance_squared_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float distance_to(const Vector3 &in)", asMETHOD(Vector3, distance_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float dot(const Vector3 &in)", asMETHOD(Vector3, dot), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 floor()", asMETHOD(Vector3, floor), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 inverse()", asMETHOD(Vector3, inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "bool is_normalized()", asMETHOD(Vector3, is_normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float length()", asMETHOD(Vector3, length), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "float length_squared()", asMETHOD(Vector3, length_squared), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 linear_interpolate(const Vector3 &in, float)", asMETHOD(Vector3, linear_interpolate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "int max_axis()", asMETHOD(Vector3, max_axis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "int min_axis()", asMETHOD(Vector3, min_axis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 normalized()", asMETHOD(Vector3, normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Basis outer(const Vector3 &in)", asMETHOD(Vector3, outer), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 reflect(const Vector3 &in)", asMETHOD(Vector3, reflect), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 rotated(const Vector3 &in, float)", asMETHOD(Vector3, rotated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 slide(const Vector3 &in)", asMETHOD(Vector3, slide), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Vector3 snapped(float)", asMETHOD(Vector3, snapped), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Vector3", "Basis to_diagonal_matrix()", asMETHOD(Vector3, to_diagonal_matrix), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Plane
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Plane>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane &in)", asFUNCTION(value_copy_constructor<Plane>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Plane>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Plane &opAssign(const Plane &in)", asFUNCTION((value_op_assign<Plane, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((value_constructor<Plane, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, float)", asFUNCTION((value_constructor<Plane, const Vector3&, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, const Vector3 &in)", asFUNCTION((value_constructor<Plane, const Vector3&, const Vector3&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Plane ==> Variant
	r = engine->RegisterObjectMethod("Plane", "Plane &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Plane, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Variant opImplConv() const", asFUNCTION((value_convert<Plane, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Plane", "bool opEquals(const Plane &in) const", asMETHODPR(Plane, operator==, (const Plane&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Plane", "bool opNeg() const", asMETHODPR(Plane, operator-, () const, Plane), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Plane methods
	r = engine->RegisterObjectMethod("Plane", "Vector3 center()", asMETHOD(Plane, center), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "float distance_to(const Vector3 &in)", asMETHOD(Plane, distance_to), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Vector3 get_any_point()", asMETHOD(Plane, get_any_point), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "bool has_point(const Vector3 &in, float arg1=0.00001)", asMETHOD(Plane, has_point), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Vector3 intersect_3(const Plane &in, const Plane &in)", asMETHOD(Plane, intersect_3), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Vector3 intersects_ray(const Vector3 &in, const Vector3 &in)", asMETHOD(Plane, intersects_ray), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Vector3 intersects_segment(const Vector3 &in, const Vector3 &in)", asMETHOD(Plane, intersects_segment), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "bool is_point_over(const Vector3 &in)", asMETHOD(Plane, is_point_over), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Plane normalized()", asMETHOD(Plane, normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Plane", "Vector3 project(const Vector3 &in)", asMETHOD(Plane, project), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// AABB
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<AABB>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_CONSTRUCT, "void f(const AABB &in)", asFUNCTION(value_copy_constructor<AABB>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<AABB>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB &opAssign(const AABB &in)", asFUNCTION((value_op_assign<AABB, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("AABB", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, const Vector3 &in)", asFUNCTION((value_constructor<AABB, const Vector3&, const Vector3&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// AABB ==> Variant
	r = engine->RegisterObjectMethod("AABB", "AABB &opAssign(const Variant &in)", asFUNCTION((value_op_assign<AABB, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Variant opImplConv() const", asFUNCTION((value_convert<AABB, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("AABB", "bool opEquals(const AABB &in) const", asMETHODPR(AABB, operator==, (const AABB&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// AABB methods
	r = engine->RegisterObjectMethod("AABB", "bool encloses(const AABB &in)", asMETHOD(AABB, encloses), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB expand(const Vector3 &in)", asMETHOD(AABB, expand), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "float get_area()", asMETHOD(AABB, get_area), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Vector3 get_endpoint(int)", asMETHOD(AABB, get_endpoint), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Vector3 get_longest_axis()", asMETHOD(AABB, get_longest_axis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "int get_longest_axis_index()", asMETHOD(AABB, get_longest_axis_index), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "float get_longest_axis_size()", asMETHOD(AABB, get_longest_axis_size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Vector3 get_shortest_axis()", asMETHOD(AABB, get_shortest_axis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "int get_shortest_axis_index()", asMETHOD(AABB, get_shortest_axis_index), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "float get_shortest_axis_size()", asMETHOD(AABB, get_shortest_axis_size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "Vector3 get_support(const Vector3 &in)", asMETHOD(AABB, get_support), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB grow(float)", asMETHOD(AABB, grow), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool has_no_area()", asMETHOD(AABB, has_no_area), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool has_no_surface()", asMETHOD(AABB, has_no_surface), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool has_point(const Vector3 &in)", asMETHOD(AABB, has_point), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB intersection(const AABB &in)", asMETHOD(AABB, intersection), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool intersects(const AABB &in)", asMETHOD(AABB, intersects), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool intersects_plane(const Plane &in)", asMETHOD(AABB, intersects_plane), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "bool intersects_segment(const Vector3 &in, const Vector3 &in)", asMETHOD(AABB, intersects_segment), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("AABB", "AABB merge(const AABB &in)", asMETHOD(AABB, merge), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Quat
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Quat>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f(const Quat &in)", asFUNCTION(value_copy_constructor<Quat>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Quat>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat &opAssign(const Quat &in)", asFUNCTION((value_op_assign<Quat, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION((value_constructor<Quat, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, float)", asFUNCTION((value_constructor<Quat, const Vector3&, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Quat", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, const Vector3 &in)", asFUNCTION((value_constructor<Quat, const Vector3&, const Vector3&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Quat ==> Variant
	r = engine->RegisterObjectMethod("Quat", "Quat &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Quat, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Variant opImplConv() const", asFUNCTION((value_convert<Quat, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Quat", "bool opEquals(const Quat &in) const", asMETHODPR(Quat, operator==, (const Quat&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Quat", "bool opNeg() const", asMETHODPR(Quat, operator-, () const, Quat), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat opAdd(const Quat &in) const", asMETHODPR(Quat, operator+, (const Quat&) const, Quat), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Quat", "void opAddAssign(const Quat &in)", asMETHODPR(Quat, operator+=, (const Quat&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat opSub(const Quat &in) const", asMETHODPR(Quat, operator-, (const Quat&) const, Quat), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Quat", "void opSubAssign(const Quat &in)", asMETHODPR(Quat, operator-=, (const Quat&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Quat methods
	r = engine->RegisterObjectMethod("Quat", "Quat cubic_slerp(const Quat &in, const Quat &in, const Quat &in, float)", asMETHOD(Quat, cubic_slerp), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "float dot(const Quat &in)", asMETHOD(Quat, dot), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat inverse()", asMETHOD(Quat, inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "bool is_normalized()", asMETHOD(Quat, is_normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "float length()", asMETHOD(Quat, length), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "float length_squared()", asMETHOD(Quat, length_squared), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat normalized()", asMETHOD(Quat, normalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat slerp(const Quat &in, float)", asMETHOD(Quat, slerp), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Quat slerpni(const Quat &in, float)", asMETHOD(Quat, slerpni), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Quat", "Vector3 xform(const Vector3 &in)", asMETHOD(Quat, xform), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Basis
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Basis>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(const Basis &in)", asFUNCTION(value_copy_constructor<Basis>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Basis>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis &opAssign(const Basis &in)", asFUNCTION((value_op_assign<Basis, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", asFUNCTION((value_constructor<Basis, float, float, float, float, float, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(const Quat &in)", asFUNCTION((value_constructor<Basis, const Quat&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION((value_constructor<Basis, const Vector3&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Basis", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in, float)", asFUNCTION((value_constructor<Basis, const Vector3&, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Basis ==> Variant
	r = engine->RegisterObjectMethod("Basis", "Basis &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Basis, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Variant opImplConv() const", asFUNCTION((value_convert<Basis, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Basis", "bool opEquals(const Basis &in) const", asMETHODPR(Basis, operator==, (const Basis&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis opAdd(const Basis &in) const", asMETHODPR(Basis, operator+, (const Basis&) const, Basis), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "void opAddAssign(const Basis &in)", asMETHODPR(Basis, operator+=, (const Basis&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis opSub(const Basis &in) const", asMETHODPR(Basis, operator-, (const Basis&) const, Basis), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "void opSubAssign(const Basis &in)", asMETHODPR(Basis, operator-=, (const Basis&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis opMul(const Basis &in) const", asMETHODPR(Basis, operator*, (const Basis&) const, Basis), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Basis", "void opMulAssign(const Basis &in)", asMETHODPR(Basis, operator*=, (const Basis&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Basis methods
	r = engine->RegisterObjectMethod("Basis", "float determinant()", asMETHOD(Basis, determinant), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Vector3 get_euler()", asMETHOD(Basis, get_euler), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "int get_orthogonal_index()", asMETHOD(Basis, get_orthogonal_index), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Vector3 get_scale()", asMETHOD(Basis, get_scale), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis inverse()", asMETHOD(Basis, inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis orthonormalized()", asMETHOD(Basis, orthonormalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis scaled(const Vector3 &in)", asMETHOD(Basis, scaled), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "float tdotx(const Vector3 &in)", asMETHOD(Basis, tdotx), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "float tdoty(const Vector3 &in)", asMETHOD(Basis, tdoty), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "float tdotz(const Vector3 &in)", asMETHOD(Basis, tdotz), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis transposed()", asMETHOD(Basis, transposed), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Vector3 xform(const Vector3 &in)", asMETHOD(Basis, xform), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Vector3 xform_inv(const Vector3 &in)", asMETHOD(Basis, xform_inv), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Transform
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Transform>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_CONSTRUCT, "void f(const Transform &in)", asFUNCTION(value_copy_constructor<Transform>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Transform>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)", asFUNCTION((value_op_assign<Transform, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform", asBEHAVE_CONSTRUCT, "void f(const Basis &in, const Vector3 &in)", asFUNCTION((value_constructor<Transform, const Basis&, const Vector3&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform ==> Variant
	r = engine->RegisterObjectMethod("Transform", "Transform &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Transform, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Variant opImplConv() const", asFUNCTION((value_convert<Transform, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Transform", "bool opEquals(const Transform &in) const", asMETHODPR(Transform, operator==, (const Transform&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform opMul(const Transform &in) const", asMETHODPR(Transform, operator*, (const Transform&) const, Transform), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Transform", "void opMulAssign(const Transform &in)", asMETHODPR(Transform, operator*=, (const Transform&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Transform methods
	r = engine->RegisterObjectMethod("Transform", "Transform affine_inverse()", asMETHOD(Transform, affine_inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform interpolate_with(const Transform &in, float)", asMETHOD(Transform, interpolate_with), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform inverse()", asMETHOD(Transform, inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform looking_at(const Vector3 &in, const Vector3 &in)", asMETHOD(Transform, looking_at), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform orthonormalized()", asMETHOD(Transform, orthonormalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform rotated(const Vector3 &in, float)", asMETHOD(Transform, rotated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform scaled(const Vector3 &in)", asMETHOD(Transform, scaled), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Transform translated(const Vector3 &in)", asMETHOD(Transform, translated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Transform2D
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Transform2D>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f(const Transform2D &in)", asFUNCTION(value_copy_constructor<Transform2D>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Transform2D>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D &opAssign(const Transform2D &in)", asFUNCTION((value_op_assign<Transform2D, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float)", asFUNCTION((value_constructor<Transform2D, float, float, float, float, float, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Transform2D", asBEHAVE_CONSTRUCT, "void f(float, const Vector2 &in)", asFUNCTION((value_constructor<Transform2D, float, const Vector2&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Transform2D ==> Variant
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Transform2D, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Variant opImplConv() const", asFUNCTION((value_convert<Transform2D, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Transform2D", "bool opEquals(const Transform2D &in) const", asMETHODPR(Transform2D, operator==, (const Transform2D&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D opMul(const Transform2D &in) const", asMETHODPR(Transform2D, operator*, (const Transform2D&) const, Transform2D), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Transform2D", "void opMulAssign(const Transform2D &in)", asMETHODPR(Transform2D, operator*=, (const Transform2D&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Transform2D methods
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D affine_inverse()", asMETHOD(Transform2D, affine_inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 basis_xform(const Vector2 &in)", asMETHOD(Transform2D, basis_xform), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 basis_xform_inv(const Vector2 &in)", asMETHOD(Transform2D, basis_xform_inv), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 get_origin()", asMETHOD(Transform2D, get_origin), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "float get_rotation()", asMETHOD(Transform2D, get_rotation), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 get_scale()", asMETHOD(Transform2D, get_scale), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D interpolate_with(const Transform2D &in, float)", asMETHOD(Transform2D, interpolate_with), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D inverse()", asMETHOD(Transform2D, inverse), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D orthonormalized()", asMETHOD(Transform2D, orthonormalized), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D rotated(float)", asMETHOD(Transform2D, rotated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D scaled(const Vector2 &in)", asMETHOD(Transform2D, scaled), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Transform2D translated(const Vector2 &in)", asMETHOD(Transform2D, translated), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
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
	// Operators
	r = engine->RegisterObjectMethod("Color", "bool opEquals(const Color &in) const", asMETHODPR(Color, operator==, (const Color&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "int opCmp(const Color &in) const", asFUNCTION((value_compare<Color, Color>)), asCALL_CDECL_OBJFIRST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "Color opAdd(const Color &in) const", asMETHODPR(Color, operator+, (const Color&) const, Color), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "void opAddAssign(const Color &in)", asMETHODPR(Color, operator+=, (const Color&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "Color opSub(const Color &in) const", asMETHODPR(Color, operator-, (const Color&) const, Color), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "void opSubAssign(const Color &in)", asMETHODPR(Color, operator-=, (const Color&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "Color opMul(const Color &in) const", asMETHODPR(Color, operator*, (const Color&) const, Color), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "void opMulAssign(const Color &in)", asMETHODPR(Color, operator*=, (const Color&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "Color opDiv(const Color &in) const", asMETHODPR(Color, operator/, (const Color&) const, Color), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Color", "void opDivAssign(const Color &in)", asMETHODPR(Color, operator/=, (const Color&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Color methods
	r = engine->RegisterObjectMethod("Color", "Color blend(const Color &in)", asMETHOD(Color, blend), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color contrasted()", asMETHOD(Color, contrasted), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color darkened(float)", asMETHOD(Color, darkened), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "float gray()", asMETHOD(Color, gray), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color inverted()", asMETHOD(Color, inverted), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color lightened(float)", asMETHOD(Color, lightened), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "Color linear_interpolate(const Color &in, float)", asMETHOD(Color, linear_interpolate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "int to_argb32()", asMETHOD(Color, to_argb32), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "String to_html(bool arg0=true)", asMETHOD(Color, to_html), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Color", "int to_rgba32()", asMETHOD(Color, to_rgba32), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// NodePath
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<NodePath>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_CONSTRUCT, "void f(const NodePath &in)", asFUNCTION(value_copy_constructor<NodePath>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<NodePath>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "NodePath &opAssign(const NodePath &in)", asFUNCTION((value_op_assign<NodePath, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("NodePath", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION((value_copy_constructor<NodePath, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// NodePath ==> Variant
	r = engine->RegisterObjectMethod("NodePath", "NodePath &opAssign(const Variant &in)", asFUNCTION((value_op_assign<NodePath, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "Variant opImplConv() const", asFUNCTION((value_convert<NodePath, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// NodePath methods
	r = engine->RegisterObjectMethod("NodePath", "NodePath get_as_property_path()", asMETHOD(NodePath, get_as_property_path), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "String get_concatenated_subnames()", asMETHOD(NodePath, get_concatenated_subnames), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "String get_name(int)", asMETHOD(NodePath, get_name), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "int get_name_count()", asMETHOD(NodePath, get_name_count), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "String get_subname(int)", asMETHOD(NodePath, get_subname), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "int get_subname_count()", asMETHOD(NodePath, get_subname_count), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "bool is_absolute()", asMETHOD(NodePath, is_absolute), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("NodePath", "bool is_empty()", asMETHOD(NodePath, is_empty), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// REF
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_CONSTRUCT, "void f(const REF &in)", asFUNCTION(value_copy_constructor<REF>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("REF", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<REF>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const REF &in)", asFUNCTION((value_op_assign<REF, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// REF ==> Variant
	r = engine->RegisterObjectMethod("REF", "REF &opAssign(const Variant &in)", asFUNCTION((value_op_assign<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("REF", "Variant opImplConv() const", asFUNCTION((value_convert<REF, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// RID
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<RID>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_CONSTRUCT, "void f(const RID &in)", asFUNCTION(value_copy_constructor<RID>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("RID", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<RID>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("RID", "RID &opAssign(const RID &in)", asFUNCTION((value_op_assign<RID, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// RID ==> Variant
	r = engine->RegisterObjectMethod("RID", "RID &opAssign(const Variant &in)", asFUNCTION((value_op_assign<RID, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("RID", "Variant opImplConv() const", asFUNCTION((value_convert<RID, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// RID methods
	r = engine->RegisterObjectMethod("RID", "int get_id()", asMETHOD(RID, get_id), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Dictionary
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_CONSTRUCT, "void f(const Dictionary &in)", asFUNCTION(value_copy_constructor<Dictionary>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Dictionary>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Dictionary &in)", asFUNCTION((value_op_assign<Dictionary, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary ==> Variant
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Variant opImplConv() const", asFUNCTION((value_convert<Dictionary, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Dictionary methods
	r = engine->RegisterObjectMethod("Dictionary", "void clear()", asMETHOD(Dictionary, clear), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Dictionary duplicate()", asMETHOD(Dictionary, duplicate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "bool empty()", asMETHOD(Dictionary, empty), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "void erase(const Variant &in)", asMETHOD(Dictionary, erase), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "bool has(const Variant &in)", asMETHOD(Dictionary, has), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "bool has_all(const Array &in)", asMETHOD(Dictionary, has_all), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "int hash()", asMETHOD(Dictionary, hash), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Array keys()", asMETHOD(Dictionary, keys), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "int size()", asMETHOD(Dictionary, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Dictionary", "Array values()", asMETHOD(Dictionary, values), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// Array
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_CONSTRUCT, "void f(const Array &in)", asFUNCTION(value_copy_constructor<Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Array &in)", asFUNCTION((value_op_assign<Array, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Array ==> Variant
	r = engine->RegisterObjectMethod("Array", "Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant opImplConv() const", asFUNCTION((value_convert<Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Operators
	r = engine->RegisterObjectMethod("Array", "bool opEquals(const Array &in) const", asMETHODPR(Array, operator==, (const Array&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Array methods
	r = engine->RegisterObjectMethod("Array", "void append(const Variant &in)", asMETHOD(Array, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant back()", asMETHOD(Array, back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int bsearch(const Variant &in, bool arg1=true)", asMETHOD(Array, bsearch), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int bsearch_custom(const Variant &in, bindings::Object@, const String &in, bool arg3=true)", asMETHOD(Array, bsearch_custom), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void clear()", asMETHOD(Array, clear), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int count(const Variant &in)", asMETHOD(Array, count), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Array duplicate()", asMETHOD(Array, duplicate), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "bool empty()", asMETHOD(Array, empty), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void erase(const Variant &in)", asMETHOD(Array, erase), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int find(const Variant &in, int arg1=0)", asMETHOD(Array, find), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int find_last(const Variant &in)", asMETHOD(Array, find_last), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant front()", asMETHOD(Array, front), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "bool has(const Variant &in)", asMETHOD(Array, has), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int hash()", asMETHOD(Array, hash), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void insert(int, const Variant &in)", asMETHOD(Array, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void invert()", asMETHOD(Array, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant pop_back()", asMETHOD(Array, pop_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "Variant pop_front()", asMETHOD(Array, pop_front), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void push_back(const Variant &in)", asMETHOD(Array, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void push_front(const Variant &in)", asMETHOD(Array, push_front), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void remove(int)", asMETHOD(Array, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void resize(int)", asMETHOD(Array, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int rfind(const Variant &in, int arg1=-1)", asMETHOD(Array, rfind), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "int size()", asMETHOD(Array, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void sort()", asMETHOD(Array, sort), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Array", "void sort_custom(bindings::Object@, const String &in)", asMETHOD(Array, sort_custom), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolByteArray
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolByteArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_CONSTRUCT, "void f(const PoolByteArray &in)", asFUNCTION(value_copy_constructor<PoolByteArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolByteArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolByteArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "PoolByteArray &opAssign(const PoolByteArray &in)", asFUNCTION((value_op_assign<PoolByteArray, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolByteArray ==> Variant
	r = engine->RegisterObjectMethod("PoolByteArray", "PoolByteArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolByteArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolByteArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolByteArray methods
	r = engine->RegisterObjectMethod("PoolByteArray", "void append(int)", asMETHOD(PoolByteArray, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void append_array(const PoolByteArray &in)", asMETHOD(PoolByteArray, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "int insert(int, int)", asMETHOD(PoolByteArray, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void invert()", asMETHOD(PoolByteArray, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void push_back(int)", asMETHOD(PoolByteArray, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void remove(int)", asMETHOD(PoolByteArray, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void resize(int)", asMETHOD(PoolByteArray, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "void set(int, int)", asMETHOD(PoolByteArray, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "int size()", asMETHOD(PoolByteArray, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolByteArray", "PoolByteArray subarray(int, int)", asMETHOD(PoolByteArray, subarray), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolIntArray
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolIntArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_CONSTRUCT, "void f(const PoolIntArray &in)", asFUNCTION(value_copy_constructor<PoolIntArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolIntArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolIntArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "PoolIntArray &opAssign(const PoolIntArray &in)", asFUNCTION((value_op_assign<PoolIntArray, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolIntArray ==> Variant
	r = engine->RegisterObjectMethod("PoolIntArray", "PoolIntArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolIntArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolIntArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolIntArray methods
	r = engine->RegisterObjectMethod("PoolIntArray", "void append(int)", asMETHOD(PoolIntArray, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void append_array(const PoolIntArray &in)", asMETHOD(PoolIntArray, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "int insert(int, int)", asMETHOD(PoolIntArray, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void invert()", asMETHOD(PoolIntArray, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void push_back(int)", asMETHOD(PoolIntArray, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void remove(int)", asMETHOD(PoolIntArray, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void resize(int)", asMETHOD(PoolIntArray, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "void set(int, int)", asMETHOD(PoolIntArray, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolIntArray", "int size()", asMETHOD(PoolIntArray, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolRealArray
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolRealArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_CONSTRUCT, "void f(const PoolRealArray &in)", asFUNCTION(value_copy_constructor<PoolRealArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolRealArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolRealArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "PoolRealArray &opAssign(const PoolRealArray &in)", asFUNCTION((value_op_assign<PoolRealArray, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolRealArray ==> Variant
	r = engine->RegisterObjectMethod("PoolRealArray", "PoolRealArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolRealArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolRealArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolRealArray methods
	r = engine->RegisterObjectMethod("PoolRealArray", "void append(float)", asMETHOD(PoolRealArray, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void append_array(const PoolRealArray &in)", asMETHOD(PoolRealArray, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "int insert(int, float)", asMETHOD(PoolRealArray, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void invert()", asMETHOD(PoolRealArray, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void push_back(float)", asMETHOD(PoolRealArray, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void remove(int)", asMETHOD(PoolRealArray, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void resize(int)", asMETHOD(PoolRealArray, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "void set(int, float)", asMETHOD(PoolRealArray, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolRealArray", "int size()", asMETHOD(PoolRealArray, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolStringArray
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolStringArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_CONSTRUCT, "void f(const PoolStringArray &in)", asFUNCTION(value_copy_constructor<PoolStringArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolStringArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolStringArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "PoolStringArray &opAssign(const PoolStringArray &in)", asFUNCTION((value_op_assign<PoolStringArray, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolStringArray ==> Variant
	r = engine->RegisterObjectMethod("PoolStringArray", "PoolStringArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolStringArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolStringArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolStringArray methods
	r = engine->RegisterObjectMethod("PoolStringArray", "void append(const String &in)", asMETHOD(PoolStringArray, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void append_array(const PoolStringArray &in)", asMETHOD(PoolStringArray, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "int insert(int, const String &in)", asMETHOD(PoolStringArray, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void invert()", asMETHOD(PoolStringArray, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "String join(const String &in)", asMETHOD(PoolStringArray, join), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void push_back(const String &in)", asMETHOD(PoolStringArray, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void remove(int)", asMETHOD(PoolStringArray, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void resize(int)", asMETHOD(PoolStringArray, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "void set(int, const String &in)", asMETHOD(PoolStringArray, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolStringArray", "int size()", asMETHOD(PoolStringArray, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolVector2Array
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolVector2Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_CONSTRUCT, "void f(const PoolVector2Array &in)", asFUNCTION(value_copy_constructor<PoolVector2Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector2Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolVector2Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "PoolVector2Array &opAssign(const PoolVector2Array &in)", asFUNCTION((value_op_assign<PoolVector2Array, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector2Array ==> Variant
	r = engine->RegisterObjectMethod("PoolVector2Array", "PoolVector2Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolVector2Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "Variant opImplConv() const", asFUNCTION((value_convert<PoolVector2Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector2Array methods
	r = engine->RegisterObjectMethod("PoolVector2Array", "void append(const Vector2 &in)", asMETHOD(PoolVector2Array, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void append_array(const PoolVector2Array &in)", asMETHOD(PoolVector2Array, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "int insert(int, const Vector2 &in)", asMETHOD(PoolVector2Array, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void invert()", asMETHOD(PoolVector2Array, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void push_back(const Vector2 &in)", asMETHOD(PoolVector2Array, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void remove(int)", asMETHOD(PoolVector2Array, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void resize(int)", asMETHOD(PoolVector2Array, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "void set(int, const Vector2 &in)", asMETHOD(PoolVector2Array, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector2Array", "int size()", asMETHOD(PoolVector2Array, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolVector3Array
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolVector3Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_CONSTRUCT, "void f(const PoolVector3Array &in)", asFUNCTION(value_copy_constructor<PoolVector3Array>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolVector3Array", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolVector3Array>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "PoolVector3Array &opAssign(const PoolVector3Array &in)", asFUNCTION((value_op_assign<PoolVector3Array, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector3Array ==> Variant
	r = engine->RegisterObjectMethod("PoolVector3Array", "PoolVector3Array &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolVector3Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "Variant opImplConv() const", asFUNCTION((value_convert<PoolVector3Array, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolVector3Array methods
	r = engine->RegisterObjectMethod("PoolVector3Array", "void append(const Vector3 &in)", asMETHOD(PoolVector3Array, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void append_array(const PoolVector3Array &in)", asMETHOD(PoolVector3Array, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "int insert(int, const Vector3 &in)", asMETHOD(PoolVector3Array, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void invert()", asMETHOD(PoolVector3Array, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void push_back(const Vector3 &in)", asMETHOD(PoolVector3Array, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void remove(int)", asMETHOD(PoolVector3Array, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void resize(int)", asMETHOD(PoolVector3Array, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "void set(int, const Vector3 &in)", asMETHOD(PoolVector3Array, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolVector3Array", "int size()", asMETHOD(PoolVector3Array, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	// PoolColorArray
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<PoolColorArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_CONSTRUCT, "void f(const PoolColorArray &in)", asFUNCTION(value_copy_constructor<PoolColorArray>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("PoolColorArray", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<PoolColorArray>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "PoolColorArray &opAssign(const PoolColorArray &in)", asFUNCTION((value_op_assign<PoolColorArray, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolColorArray ==> Variant
	r = engine->RegisterObjectMethod("PoolColorArray", "PoolColorArray &opAssign(const Variant &in)", asFUNCTION((value_op_assign<PoolColorArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "Variant opImplConv() const", asFUNCTION((value_convert<PoolColorArray, Variant>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// PoolColorArray methods
	r = engine->RegisterObjectMethod("PoolColorArray", "void append(const Color &in)", asMETHOD(PoolColorArray, append), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void append_array(const PoolColorArray &in)", asMETHOD(PoolColorArray, append_array), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "int insert(int, const Color &in)", asMETHOD(PoolColorArray, insert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void invert()", asMETHOD(PoolColorArray, invert), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void push_back(const Color &in)", asMETHOD(PoolColorArray, push_back), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void remove(int)", asMETHOD(PoolColorArray, remove), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void resize(int)", asMETHOD(PoolColorArray, resize), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "void set(int, const Color &in)", asMETHOD(PoolColorArray, set), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("PoolColorArray", "int size()", asMETHOD(PoolColorArray, size), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
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
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String &in)", asFUNCTION((value_constructor<Variant, const String&>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> bool
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const bool &in)", asFUNCTION((value_op_assign<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opImplConv() const", asFUNCTION((value_convert<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> int
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const int &in)", asFUNCTION((value_op_assign<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "int opImplConv() const", asFUNCTION((value_convert<Variant, int>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> uint
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const uint &in)", asFUNCTION((value_op_assign<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "uint opImplConv() const", asFUNCTION((value_convert<Variant, uint>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> float
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const float &in)", asFUNCTION((value_op_assign<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "float opImplConv() const", asFUNCTION((value_convert<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> double
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const double &in)", asFUNCTION((value_op_assign<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "double opImplConv() const", asFUNCTION((value_convert<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> String
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const String &in)", asFUNCTION((value_op_assign<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "String opImplConv() const", asFUNCTION((value_convert<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> StringName
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const StringName &in)", asFUNCTION((value_op_assign<Variant, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "StringName opImplConv() const", asFUNCTION((value_convert<Variant, StringName>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector2
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector2 &in)", asFUNCTION((value_op_assign<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector2 opImplConv() const", asFUNCTION((value_convert<Variant, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Rect2
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Rect2 &in)", asFUNCTION((value_op_assign<Variant, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Rect2 opImplConv() const", asFUNCTION((value_convert<Variant, Rect2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Vector3
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector3 &in)", asFUNCTION((value_op_assign<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Vector3 opImplConv() const", asFUNCTION((value_convert<Variant, Vector3>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Plane
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Plane &in)", asFUNCTION((value_op_assign<Variant, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Plane opImplConv() const", asFUNCTION((value_convert<Variant, Plane>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> AABB
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const AABB &in)", asFUNCTION((value_op_assign<Variant, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "AABB opImplConv() const", asFUNCTION((value_convert<Variant, AABB>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Quat
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Quat &in)", asFUNCTION((value_op_assign<Variant, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Quat opImplConv() const", asFUNCTION((value_convert<Variant, Quat>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Basis
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Basis &in)", asFUNCTION((value_op_assign<Variant, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Basis opImplConv() const", asFUNCTION((value_convert<Variant, Basis>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Transform
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Transform &in)", asFUNCTION((value_op_assign<Variant, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform opImplConv() const", asFUNCTION((value_convert<Variant, Transform>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Transform2D
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Transform2D &in)", asFUNCTION((value_op_assign<Variant, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Transform2D opImplConv() const", asFUNCTION((value_convert<Variant, Transform2D>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Color
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Color &in)", asFUNCTION((value_op_assign<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Color opImplConv() const", asFUNCTION((value_convert<Variant, Color>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> NodePath
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const NodePath &in)", asFUNCTION((value_op_assign<Variant, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "NodePath opImplConv() const", asFUNCTION((value_convert<Variant, NodePath>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> REF
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const REF &in)", asFUNCTION((value_op_assign<Variant, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "REF opImplConv() const", asFUNCTION((value_convert<Variant, REF>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> RID
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const RID &in)", asFUNCTION((value_op_assign<Variant, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "RID opImplConv() const", asFUNCTION((value_convert<Variant, RID>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Dictionary
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Dictionary &in)", asFUNCTION((value_op_assign<Variant, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Dictionary opImplConv() const", asFUNCTION((value_convert<Variant, Dictionary>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Array &in)", asFUNCTION((value_op_assign<Variant, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "Array opImplConv() const", asFUNCTION((value_convert<Variant, Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolByteArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolByteArray &in)", asFUNCTION((value_op_assign<Variant, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolByteArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolByteArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolIntArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolIntArray &in)", asFUNCTION((value_op_assign<Variant, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolIntArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolIntArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolRealArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolRealArray &in)", asFUNCTION((value_op_assign<Variant, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolRealArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolRealArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolStringArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolStringArray &in)", asFUNCTION((value_op_assign<Variant, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolStringArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolStringArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolVector2Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolVector2Array &in)", asFUNCTION((value_op_assign<Variant, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector2Array opImplConv() const", asFUNCTION((value_convert<Variant, PoolVector2Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolVector3Array
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolVector3Array &in)", asFUNCTION((value_op_assign<Variant, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolVector3Array opImplConv() const", asFUNCTION((value_convert<Variant, PoolVector3Array>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	// Variant ==> PoolColorArray
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const PoolColorArray &in)", asFUNCTION((value_op_assign<Variant, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Variant", "PoolColorArray opImplConv() const", asFUNCTION((value_convert<Variant, PoolColorArray>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	return r;
}
}
