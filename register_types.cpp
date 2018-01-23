#include "register_types.h"
#include "bindings/bindings.h"
#include <core/reference.h>
#include <core/class_db.h>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

asIScriptEngine *engine = NULL;

class AngelScriptRunner : public Reference {
	GDCLASS(AngelScriptRunner, Reference);
public:
	void run(const String& p_script) {
		// The CScriptBuilder helper is an add-on that loads the file,
		// performs a pre-processing pass if necessary, and then tells
		// the engine to build a script module.
		CScriptBuilder builder;
		int r = builder.StartNewModule(engine, p_script.utf8().get_data());
		if (r < 0) {
			ERR_PRINTS(String("Unrecoverable error while starting a new module:\n") + p_script);
			return;
		}

		r = builder.AddSectionFromFile(p_script.utf8().get_data());
		if (r < 0) {
			// The builder wasn't able to load the file. Maybe the file
			// has been removed, or the wrong name was given, or some
			// preprocessing commands are incorrectly written.
			ERR_PRINTS(String("Please correct the errors in the script and try again:\n") + p_script);
			return;
		}

		r = builder.BuildModule();
		if (r < 0) {
			// An error occurred. Instruct the script writer to fix the
			// compilation errors that were listed in the output stream.
			// Please correct the errors in the script and try again.
			ERR_PRINTS(String("Please correct the errors in the script and try again:\n") + p_script);
			return;
		}

		// Find the function that is to be called.
		asIScriptModule *mod = engine->GetModule(p_script.utf8().get_data());

		asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
		if (func == NULL) {
			// The function couldn't be found. Instruct the script writer
			// to include the expected function in the script.
			// The script must have the function 'void main()'. Please add it and try again.
			ERR_PRINTS(String("The script must have the function 'void main()'. Please add it and try again:\n") + p_script);
			return;
		}

		// Create our context, prepare it, and then execute
		asIScriptContext *ctx = engine->CreateContext();
		ctx->Prepare(func);
		r = ctx->Execute();
		if (r != asEXECUTION_FINISHED) {
			// The execution didn't complete as expected. Determine what happened.
			if (r == asEXECUTION_EXCEPTION) {
				// An exception occurred, let the script writer know what happened so it can be corrected.
				printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
			}
		}
	}
protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("run", "p_path"), &AngelScriptRunner::run);
	}
};


// Implement a simple message callback function
void ASB_MessageCallback(const asSMessageInfo *msg, void *param) {
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING )
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION )
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void CHECK_CONDITION(const String& text, bool passed) {
	if (passed) {
		print_line(text + " passed");
	} else {
		ERR_PRINTS(text + " failed");
	}
}

void register_angelscript_types() {
	engine = asCreateScriptEngine();
	engine->SetMessageCallback(asFUNCTION(ASB_MessageCallback), 0, asCALL_CDECL);
	bind_angelscript_language(engine);
	engine->RegisterGlobalFunction("void check(const String &in, bool)", asFUNCTION(CHECK_CONDITION), asCALL_CDECL);
	ClassDB::register_class<AngelScriptRunner>();
}

void unregister_angelscript_types() {

}
