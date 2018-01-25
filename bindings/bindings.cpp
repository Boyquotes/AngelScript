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
	int r = gen_as_declare_core_types(engine);			ERR_FAIL_COND_V( r <0, r);
	r = as_declare_core_types(engine);					ERR_FAIL_COND_V( r <0, r);
	r = gen_as_bind_core_value_type_behavoirs(engine);  ERR_FAIL_COND_V( r <0, r);
	r = as_core_binding_manual(engine);					ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void print(const String &in)", asFUNCTION(angelscript_print), asCALL_CDECL); ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void check(const String &in, bool)", asFUNCTION(angelscript_debug_check), asCALL_CDECL);  ERR_FAIL_COND_V( r <0, r);
	return r;
}
