#include <core/error_macros.h>
#include <core/print_string.h>
#include "bindings.h"
#include <angelscript.h>

int bind_angelscript_language(asIScriptEngine *engine) {
	int r = as_register_string(engine); ERR_FAIL_COND_V( r <0, r);
	r = as_register_vector2(engine);    ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void print(const String &in)", asFUNCTION(print_line), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	return r;
}
