#include <core/os/memory.h>
#include <core/error_macros.h>
#include <core/print_string.h>
#include "bindings.h"
#include <angelscript.h>
#include <core/os/os.h>

#include "utils.h"
#include "value_types.h"
#include "objects.h"

namespace asb {

static void angelscript_print(const String& text) {
	OS::get_singleton()->print("%s\n", text.utf8().get_data());
}

static void angelscript_debug_check(String text, bool passed) {
	const char * status = passed ? "PASS" : "FAIL";
	if (passed)
		OS::get_singleton()->print("%s : %s\n", status, text.utf8().get_data());
	else
		OS::get_singleton()->printerr("%s : %s\n", status, text.utf8().get_data());
}

static uint32_t angelscript_get_tick_msec() {
	return OS::get_singleton()->get_ticks_msec();
}

int bind_angelscript_language(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = asb::declare_value_types(engine);		ERR_FAIL_COND_V( r <0, r);
	r = asb::declare_object_types(engine);			ERR_FAIL_COND_V( r <0, r);
	r = asb::define_value_types(engine);			ERR_FAIL_COND_V( r <0, r);
	r = asb::define_object_types(engine);			ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void print(const String &in)", asFUNCTION(angelscript_print), asCALL_CDECL);			  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("uint get_tick_msec()", asFUNCTION(angelscript_get_tick_msec), asCALL_CDECL);			  ERR_FAIL_COND_V( r <0, r);
	r = engine->RegisterGlobalFunction("void check(const String &in, bool)", asFUNCTION(angelscript_debug_check), asCALL_CDECL);  ERR_FAIL_COND_V( r <0, r);

	// FIXME: MOVE THIS to tools
	if (FileAccessRef f = FileAccess::open("godot.gen.as", FileAccess::WRITE)) {
		f->store_string(asb::get_binding_script_content());
		f->flush();
		f->close();
	}

	return r;
}

}


