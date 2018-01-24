#include <core/variant.h>
#include <angelscript.h>
#include <core/ustring.h>
#include <core/map.h>
#include <cassert>
#include "core.h"
#include <core/print_string.h>

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
	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>());   ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterStringFactory("String", &asb_string_factory);                               ERR_FAIL_COND_V( r <0, r);
	// Behaviours
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                  asFUNCTION(as_value_constructor<String>), asCALL_CDECL_OBJLAST);           ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String &in)",  asFUNCTION(as_value_copy_constructor<String>), asCALL_CDECL_OBJLAST);      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,   "void f()",                  asFUNCTION(as_value_desctructor<String>),  asCALL_CDECL_OBJLAST);          ERR_FAIL_COND_V( r <0, r);
	// Operators
	r = engine->RegisterObjectMethod("String", "String &opAssign(const String &in)", asMETHODPR(String, operator=, (const String&), String&), asCALL_THISCALL);         ERR_FAIL_COND_V( r <0, r);
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

	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asGetTypeTraits<Vector2>());   ERR_FAIL_COND_V( r <0, r); ERR_FAIL_COND_V( r <0, r);
	// Behaviours
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT,  "void f(float x=0, float y=0)", asFUNCTION(as_construct_vector2), asCALL_CDECL_OBJLAST);				ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT,  "void f(const Vector2 &in)",    asFUNCTION(as_value_copy_constructor<Vector2>), asCALL_CDECL_OBJLAST);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT,   "void f()",                     asFUNCTION(as_value_desctructor<Vector2>),  asCALL_CDECL_OBJLAST);      ERR_FAIL_COND_V( r <0, r);
	// Properties
	r = engine->RegisterObjectProperty("Vector2", "float x",     asOFFSET(Vector2, x));      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float width", asOFFSET(Vector2, width));  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float y",     asOFFSET(Vector2, y));      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectProperty("Vector2", "float height",asOFFSET(Vector2, height)); ERR_FAIL_COND_V( r <0, r);
	// Operators
	r = engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)",   asMETHODPR(Vector2, operator=, (const Vector2&), Vector2&), asCALL_THISCALL);     ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void opAddAssign(const Vector2 &in)",    asMETHODPR(Vector2, operator+=, (const Vector2&), void), asCALL_THISCALL);        ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2 &in) const", asMETHODPR(Vector2, operator==, (const Vector2&) const, bool), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "int opCmp(const Vector2 &in) const",     asFUNCTION(as_vector2_compare), asCALL_CDECL_OBJFIRST);                           ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2 &in) const", asMETHODPR(Vector2, operator+, (const Vector2&) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	// Methods
	r = engine->RegisterObjectMethod("Vector2", "float length() const",asMETHODPR(Vector2, length, (void) const, float), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Vector2", "void normalize()", asMETHODPR(Vector2, normalize, (void), void), asCALL_THISCALL);        ERR_FAIL_COND_V( r <0, r);

	// Variant to String
	r = engine->RegisterObjectMethod("String", "String &opAssign(const Vector2 &in)", asFUNCTION((as_value_op_assign<String, Vector2>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);

	return r;
}

int as_register_variant(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE | asGetTypeTraits<Variant>());   ERR_FAIL_COND_V( r <0, r);
	// Behaviours
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(as_value_constructor<Variant>), asCALL_CDECL_OBJLAST);								 ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT,  "void f(const Variant &in)",    asFUNCTION(as_value_copy_constructor<Variant>), asCALL_CDECL_OBJLAST);		 ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT,   "void f()",                     asFUNCTION(as_value_desctructor<Variant>),  asCALL_CDECL_OBJLAST);			 ERR_FAIL_COND_V( r <0, r);
	// Variant <==> String
	r = engine->RegisterObjectMethod("String",  "Variant opImplConv() const",  asFUNCTION((as_value_convert<String, Variant>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String",  "Variant opConv() const",  asFUNCTION((as_value_convert<String, Variant>)),				  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const String &in)", asFUNCTION((as_value_op_assign<Variant, String>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "String opImplConv() const",  asFUNCTION((as_value_convert<Variant, String>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "String opConv() const",  asFUNCTION((as_value_convert<Variant, String>)),				  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	// Variant <==> int
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const int &in)", asFUNCTION((as_value_op_assign<Variant, int32_t>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "int opImplConv() const",  asFUNCTION((as_value_convert<Variant, int32_t>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "int opConv() const",	   asFUNCTION((as_value_convert<Variant, int32_t>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	// Variant <==> float
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const float &in)", asFUNCTION((as_value_op_assign<Variant, float>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "float opImplConv() const",  asFUNCTION((as_value_convert<Variant, float>)),			asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "float opConv() const",	   asFUNCTION((as_value_convert<Variant, float>)),				asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	// Variant <==> double
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const double &in)", asFUNCTION((as_value_op_assign<Variant, double>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "double opImplConv() const",  asFUNCTION((as_value_convert<Variant, double>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "double opConv() const",	   asFUNCTION((as_value_convert<Variant, double>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	// Variant <==> bool
	r = engine->RegisterObjectMethod("Variant", "Variant &opAssign(const bool &in)", asFUNCTION((as_value_op_assign<Variant, bool>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opImplConv() const",  asFUNCTION((as_value_convert<Variant, bool>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("Variant", "bool opConv() const",	   asFUNCTION((as_value_convert<Variant, bool>)),			  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	return r;
}
