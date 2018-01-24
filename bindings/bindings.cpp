#include <core/os/memory.h>
#include <core/error_macros.h>
#include <core/print_string.h>
#include "bindings.h"
#include <angelscript.h>
#include <cstdio>


void angelscript_print(const String& text) {
	printf("%s\n", text.utf8().get_data());
}

void angelscript_debug_check(String text, bool passed) {
	const char * status = passed ? "PASS" : "FAIL";
	printf("%s : %s\n", status, text.utf8().get_data());
}

int bind_angelscript_language(asIScriptEngine *engine) {
	int r = as_register_string(engine); ERR_FAIL_COND_V( r <0, r);
	r = as_register_vector2(engine);    ERR_FAIL_COND_V( r <0, r);
	r = as_register_variant(engine);    ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void print(const String &in)", asFUNCTION(angelscript_print), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void check(const String &in, bool)", asFUNCTION(angelscript_debug_check), asCALL_CDECL);  ERR_FAIL_COND_V( r <0, r);
	return r;
}
