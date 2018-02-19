#include "register_types.h"
#include "bindings/bindings.h"
#include <core/reference.h>
#include <core/class_db.h>
#include <angelscript.h>
#include "angelscript.h"
#include "bindings/utils.h"
#include <scriptbuilder/scriptbuilder.h>
#include <core/os/os.h>

class AngelScriptRunner : public Reference {
	GDCLASS(AngelScriptRunner, Reference);
	asIScriptEngine *engine;
public:
	AngelScriptRunner() {
		engine = AngelScriptLanguage::get_singleton()->get_script_engine();
	}
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

				String section_name = ctx->GetExceptionFunction()->GetScriptSectionName();
				String func_name = ctx->GetExceptionFunction()->GetName();
				String err_message = ctx->GetExceptionString();
				OS::get_singleton()->print("An exception occurred. Please correct the code and try again.\n");
				OS::get_singleton()->print("Section: %s\n", section_name.utf8().get_data());
				OS::get_singleton()->print("Function: %s\n", func_name.utf8().get_data());
				OS::get_singleton()->print("Message: %s\n", err_message.utf8().get_data());
			}
		}
		ctx->Release();
	}
protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("run", "p_path"), &AngelScriptRunner::run);
	}
};

void register_angelscript_types() {

	asSetGlobalMemoryFunctions(asb::as_memalloc, asb::as_memfree);

	memnew(AngelScriptLanguage);
	ScriptServer::register_language(AngelScriptLanguage::get_singleton());

	ClassDB::register_class<AngelScriptRunner>();
}

void unregister_angelscript_types() {

	ScriptServer::unregister_language(AngelScriptLanguage::get_singleton());
	memdelete(AngelScriptLanguage::get_singleton());

}
