#include "value_types.h"
#include "utils.h"
#include <angelscript.h>
#include <core/ustring.h>
#include <core/map.h>
#include <core/os/copymem.h>
#include <core/math/math_2d.h>
#include <core/math/matrix3.h>
#include <core/math/transform.h>

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
	// Overloads Methods
	r = engine->RegisterObjectMethod("Vector2", "Vector2 linear_interpolate(const Vector2 &in, float)", asMETHODPR(Vector2, linear_interpolate, (const Vector2 &, real_t) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis rotated(const Vector3 &in, float)", asMETHODPR(Basis, rotated, (const Vector3 &, real_t p_phi) const, Basis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Basis", "Basis rotated(const Vector3 &in)", asMETHODPR(Basis, rotated, (const Vector3 &) const, Basis), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Vector3 xform(const Vector3 &in)", asMETHODPR(Transform, xform, (const Vector3 &) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Plane xform(const Plane &in)", asMETHODPR(Transform, xform, (const Plane &) const, Plane), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "AABB xform(const AABB &in)", asMETHODPR(Transform, xform, (const AABB &) const, AABB), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Vector3 xform_inv(const Vector3 &in)", asMETHODPR(Transform, xform_inv, (const Vector3 &) const, Vector3), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "Plane xform_inv(const Plane &in)", asMETHODPR(Transform, xform_inv, (const Plane &) const, Plane), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform", "AABB xform_inv(const AABB &in)", asMETHODPR(Transform, xform_inv, (const AABB &) const, AABB), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 xform(const Vector2 &in)", asMETHODPR(Transform2D, xform, (const Vector2 &) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Rect2 xform(const Rect2 &in)", asMETHODPR(Transform2D, xform, (const Rect2 &) const, Rect2), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Vector2 xform_inv(const Vector2 &in)", asMETHODPR(Transform2D, xform_inv, (const Vector2 &) const, Vector2), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("Transform2D", "Rect2 xform_inv(const Rect2 &in)", asMETHODPR(Transform2D, xform_inv, (const Rect2 &) const, Rect2), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);

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
	// Overloads Methods
	r = engine->RegisterObjectMethod("String", "bool begins_with() const",asMETHODPR(String, begins_with, (const String &) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "int find(const String &in, int) const", asMETHODPR(String, find, (const String &, int) const, int), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "uint hash() const", asMETHODPR(String, hash, () const, uint32_t), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "String replace(const String &in, const String &in) const", asMETHODPR(String, replace, (const String &, const String&) const, String), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterObjectMethod("String", "int to_int() const", asMETHODPR(String, to_int, () const, int), asCALL_THISCALL);   ERR_FAIL_COND_V( r <0, r);
	return r;
}

}
