#include "value_types.h"
#include <angelscript.h>
#include <core/ustring.h>
#include <core/map.h>
#include <core/os/copymem.h>

namespace asb {

class StringFactory : public asIStringFactory {
public:
	StringFactory() {}
	~StringFactory() {
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
static StringFactory string_factory;
int register_string(asIScriptEngine *engine);

int declare_value_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);
	int r = 0;
	r = _declare_value_types_gen(engine); ERR_FAIL_COND_V(r<0, r);
	return r;
}

int define_value_types(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
	r = register_string(engine); ERR_FAIL_COND_V(r<0, r);
	r = _define_value_types_gen(engine);  ERR_FAIL_COND_V(r<0, r);
	return r;
}


int string_compare(const String &a, const String &b) {
	int cmp = 1;
	if( a < b )
		cmp = -1;
	else if( a == b )
		cmp = 0;
	return cmp;
}

int register_string(asIScriptEngine *engine) {
	ERR_FAIL_COND_V( engine == NULL, -1);

	int r = 0;
	// Factory
	r = engine->RegisterStringFactory("String", &string_factory); ERR_FAIL_COND_V( r <0, r);
	// Operators
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL);     ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const", asMETHODPR(String, operator==, (const String&) const, bool), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const", asFUNCTION(string_compare), asCALL_CDECL_OBJFIRST);                              ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const", asMETHODPR(String, operator+, (const String&) const, String), asCALL_THISCALL);  ERR_FAIL_COND_V( r <0, r);
	// Methods
	r = engine->RegisterObjectMethod("String", "int length() const",asMETHODPR(String, length, (void) const, int), asCALL_THISCALL);    ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "bool empty() const", asMETHODPR(String, empty, (void) const, bool), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	return r;
}

}
