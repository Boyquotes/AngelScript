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
			*length = utf8str.length();
		}

		if (data) {
			copymem(data, utf8str.get_data(), utf8str.length());
		}

		return asSUCCESS;
	}

	static void as_construct_string(String *p_this) {
		memnew_placement(p_this, String);
	}

	static void as_copy_construct_string(const String &other, String *p_this) {
		memnew_placement(p_this, String(other));
	}

	static void as_destruct_string(String *p_this) {
		p_this->~String();
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
	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);   ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterStringFactory("String", &asb_string_factory);                              ERR_FAIL_COND_V( r <0, r);
	// Behaviours
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                  asFUNCTION(ASB_StringFactory::as_construct_string), asCALL_CDECL_OBJLAST);           ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String &in)",  asFUNCTION(ASB_StringFactory::as_copy_construct_string), asCALL_CDECL_OBJLAST);      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,   "void f()",                  asFUNCTION(ASB_StringFactory::as_destruct_string),  asCALL_CDECL_OBJLAST);           ERR_FAIL_COND_V( r <0, r);
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

static void as_copy_construct_vector2(const Vector2 &other, Vector2 *p_this) {
	memnew_placement(p_this, Vector2(other));
}

static void as_destruct_vector2(Vector2 *p_this) {
	if(p_this)
		p_this->~Vector2();
}

static int as_vector2_compare(const Vector2 &a, const Vector2 &b){
	int cmp = 1;
	if( a < b )
		cmp = -1;
	else if( a == b )
		cmp = 0;
	return cmp;
}

static String &as_vector2string(const Vector2& v, String &dest) {
	dest = v;
	return dest;
}

int as_register_vector2(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;

	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);   ERR_FAIL_COND_V( r <0, r); ERR_FAIL_COND_V( r <0, r);
	// Behaviours
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT,  "void f(float x=0, float y=0)", asFUNCTION(as_construct_vector2), asCALL_CDECL_OBJLAST);      ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT,  "void f(const Vector2 &in)",    asFUNCTION(as_copy_construct_vector2), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT,   "void f()",                     asFUNCTION(as_destruct_vector2),  asCALL_CDECL_OBJLAST);      ERR_FAIL_COND_V( r <0, r);
	// properties
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

	// Vector2 to String
	r = engine->RegisterObjectMethod("String", "String &opAssign(const Vector2 &in)", asFUNCTION(as_vector2string), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V( r <0, r);

	return r;
}
