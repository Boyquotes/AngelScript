#!/usr/env python3
import os
ROOT_DIR = os.path.abspath(os.path.dirname(__file__))
TARGET = "core.gen.cpp"
value_classes = {
	"String": {
		"ext_copy_constructors": ['StringName'],
		"convertions": ['StringName', 'Variant']
	},
	"StringName": {
		"ext_copy_constructors": ['String'],
		"convertions": ['String', 'Variant']
	},
	"Vector2": {
		"convertions": ['Variant']
	},
	"Rect2": {
		"convertions": ['Variant']
	},
	"Vector3": {
		"convertions": ['Variant']
	},
	"Color": {
		"convertions": ['Variant']
	},
	"Variant": {
		"ext_copy_constructors": [],
		"convertions": ['bool', 'int', 'float', 'double', 'String', 'StringName',  'Color', 'Vector2', 'Vector3']
	},
}

def wrapp_as_register_function(funcname, text):
	return '''\
int %s(asIScriptEngine *engine) {
	ERR_FAIL_COND_V(engine == NULL, -1);
	int r = 0;
%s
	return r;
}''' % (funcname, text if text[-1] != "\n" else text[0: -1])


def gen_declare_core_types():
	text = ""
	template = '\tr = engine->RegisterObjectType("{0}", sizeof({0}), asOBJ_VALUE|asGetTypeTraits<{0}>()); ERR_FAIL_COND_V(r<0, r);\n'
	for cls in value_classes:
		text += template.format(cls)
	return wrapp_as_register_function('gen_as_declare_core_types', text)

def gen_value_behavoirs():
	text = ""
	cdka_template = '''\
	// {0}
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(as_value_constructor<{0}>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f(const {0} &in)", asFUNCTION(as_value_copy_constructor<{0}>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(as_value_desctructor<{0}>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("{0}", "{0} &opAssign(const {0} &in)", asFUNCTION((as_value_op_assign<{0}, {0}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	extc_template = '''\
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f(const {1} &in)", asFUNCTION((as_value_copy_constructor<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	convt_template = '''\
	// {0} ==> {1}
	r = engine->RegisterObjectMethod("{0}", "{0} &opAssign(const {1} &in)", asFUNCTION((as_value_op_assign<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("{0}", "{1} opImplConv() const", asFUNCTION((as_value_convert<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("{0}", "{1} opConv() const", asFUNCTION((as_value_convert<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	for cls in value_classes:
		cfg = value_classes[cls]
		text += cdka_template.format(cls)
		if cfg and 'ext_copy_constructors' in cfg:
			for ext_type in cfg['ext_copy_constructors']:
				text += extc_template.format(cls,ext_type)
		if cfg and 'convertions' in cfg:
			for ext_type in cfg['convertions']:
				text += convt_template.format(cls,ext_type)
	return wrapp_as_register_function('gen_as_bind_core_value_type_behavoirs', text)


def line(text):
	return text + '\n'

def generate_code_text():
	output_cpp = line('''\
#include <core/variant.h>
#include <core/math/math_2d.h>
#include <core/math/vector3.h>
#include <angelscript.h>
#include "core.h"
''')
	output_cpp += line('')
	output_cpp += line(gen_declare_core_types())
	output_cpp += line('')
	output_cpp += line(gen_value_behavoirs())

	try:
		needUpdate = True
		path = os.path.join(ROOT_DIR, TARGET)
		if os.path.isfile(path):
			if output_cpp == open(path).read():
				needUpdate = False
		if needUpdate:
			open(path, 'w').write(output_cpp)
	except Exception as e:
		print("Failed to generate core.gen.h")
		print(e)

if __name__ == '__main__':
	generate_code_text()
