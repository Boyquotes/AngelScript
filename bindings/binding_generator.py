#!/usr/bin/python
import json, os, sys
import xml.etree.ElementTree as ET

GODOT_ROOT = "../../.."
CLASS_INFO = {}
ROOT_DIR = os.path.abspath(os.path.dirname(__file__))

VALUE_TARGET = "value_types.gen.cpp"
OBJECT_TARGET = "objects.include.gen.cpp"

OPERATOR_MAP = {
	'OP_NEG' : '\tr = engine->RegisterObjectMethod("{0}", "bool opNeg() const", asMETHODPR({0}, operator-, () const, {0}), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_EQUALS' : '\tr = engine->RegisterObjectMethod("{0}", "bool opEquals(const {0} &in) const", asMETHODPR({0}, operator==, (const {0}&) const, bool), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_COMPARE' : '\tr = engine->RegisterObjectMethod("{0}", "int opCmp(const {0} &in) const", asFUNCTION((value_compare<{0}, {0}>)), asCALL_CDECL_OBJFIRST); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_ADD' : '\tr = engine->RegisterObjectMethod("{0}", "{0} opAdd(const {0} &in) const", asMETHODPR({0}, operator+, (const {0}&) const, {0}), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_ADD_ASSIGN_SELF' : '\tr = engine->RegisterObjectMethod("{0}", "{0}& opAddAssign(const {0} &in)", asMETHODPR({0}, operator+=, (const {0}&), {0}&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_ADD_ASSIGN_VOID' : '\tr = engine->RegisterObjectMethod("{0}", "void opAddAssign(const {0} &in)", asMETHODPR({0}, operator+=, (const {0}&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MINUS' : '\tr = engine->RegisterObjectMethod("{0}", "{0} opSub(const {0} &in) const", asMETHODPR({0}, operator-, (const {0}&) const, {0}), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MINUS_ASSIGN_SELF' : '\tr = engine->RegisterObjectMethod("{0}", "{0}& opSubAssign(const {0} &in)", asMETHODPR({0}, operator-=, (const {0}&), {0}&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MINUS_ASSIGN_VOID' : '\tr = engine->RegisterObjectMethod("{0}", "void opSubAssign(const {0} &in)", asMETHODPR({0}, operator-=, (const {0}&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MULTIPLY' : '\tr = engine->RegisterObjectMethod("{0}", "{0} opMul(const {0} &in) const", asMETHODPR({0}, operator*, (const {0}&) const, {0}), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MULTIPLY_ASSIGN_SELF' : '\tr = engine->RegisterObjectMethod("{0}", "{0}& opMulAssign(const {0} &in)", asMETHODPR({0}, operator*=, (const {0}&), {0}&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_MULTIPLY_ASSIGN_VOID' : '\tr = engine->RegisterObjectMethod("{0}", "void opMulAssign(const {0} &in)", asMETHODPR({0}, operator*=, (const {0}&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_DIVID' : '\tr = engine->RegisterObjectMethod("{0}", "{0} opDiv(const {0} &in) const", asMETHODPR({0}, operator/, (const {0}&) const, {0}), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_DIVID_ASSIGN_SELF' : '\tr = engine->RegisterObjectMethod("{0}", "{0}& opDivAssign(const {0} &in)", asMETHODPR({0}, operator/=, (const {0}&), {0}&), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
	'OP_DIVID_ASSIGN_VOID' : '\tr = engine->RegisterObjectMethod("{0}", "void opDivAssign(const {0} &in)", asMETHODPR({0}, operator/=, (const {0}&), void), asCALL_THISCALL); ERR_FAIL_COND_V( r <0, r);\n',
}

value_classes = {
	"String": {
		'operators': ['OP_EQUALS', 'OP_COMPARE', 'OP_ADD', 'OP_ADD_ASSIGN_SELF'],
		"ext_copy_constructors": [],
		"convertions": ['StringName', 'Variant'],
		"ignore_methods": [
			# The ignored methods should be exported manually
			"begins_with", "find", "hash", "replace", "to_int",
			"to_ascii", "to_utf8", # TODO
		]
	},
	"StringName": {
		"ext_copy_constructors": ['String'],
		"convertions": ['Variant']
	},
	"Vector2": {
		'operators': ['OP_EQUALS', 'OP_COMPARE','OP_ADD', 'OP_ADD_ASSIGN_VOID', 'OP_MINUS', 'OP_MINUS_ASSIGN_VOID', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_VOID', 'OP_DIVID'],
		"param_constructors": [
			['float', 'float']
		],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"ignore_methods": [
			"linear_interpolate"
		]
	},
	"Rect2": {
		"param_constructors": [
			['float', 'float', 'float', 'float'],
			['Vector2', 'Vector2'],
		],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant']
	},
	"Vector3": {
		'operators': ['OP_EQUALS', 'OP_COMPARE','OP_ADD', 'OP_ADD_ASSIGN_SELF', 'OP_MINUS', 'OP_MINUS_ASSIGN_SELF', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_SELF', 'OP_DIVID', 'OP_DIVID_ASSIGN_SELF'],
		"param_constructors": [
			['float', 'float', 'float']
		],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant']
	},
	"Plane": {
		'operators': ['OP_EQUALS', 'OP_NEG'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"param_constructors": [
			['float', 'float', 'float', 'float'],
			['Vector3', 'float'],
			['Vector3', 'Vector3'],
			#  TODO: Enum params
			# ['Vector3', 'Vector3', 'Vector3', 'int'],
		],
	},
	"AABB": {
		'operators': ['OP_EQUALS'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"param_constructors": [
			['Vector3', 'Vector3'],
		],
	},
	"Quat": {
		'operators': ['OP_EQUALS', 'OP_NEG', 'OP_ADD', 'OP_ADD_ASSIGN_VOID', 'OP_MINUS', 'OP_MINUS_ASSIGN_VOID'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"param_constructors": [
			['float', 'float', 'float', 'float'],
			['Vector3', 'float'],
			['Vector3', 'Vector3'],
		],
	},
	"Basis": {
		'operators': ['OP_EQUALS', 'OP_ADD', 'OP_ADD_ASSIGN_VOID', 'OP_MINUS', 'OP_MINUS_ASSIGN_VOID', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_VOID'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"ignore_methods": [
			"rotated"
		],
		"param_constructors": [
			['float', 'float', 'float', 'float', 'float', 'float', 'float', 'float', 'float'],
			['Quat'],
			['Vector3'],
			['Vector3', 'float'],
		],
	},
	"Transform": {
		'operators': ['OP_EQUALS', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_VOID'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"ignore_methods": [
			"xform", "xform_inv"
		],
		"param_constructors": [
			['Basis', 'Vector3'],
		],
	},
	"Transform2D": {
		'operators': ['OP_EQUALS', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_VOID'],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant'],
		"ignore_methods": [
			"xform", "xform_inv"
		],
		"param_constructors": [
			['float', 'float', 'float', 'float', 'float', 'float'],
			['float', 'Vector2'],
		],
	},
	"Color": {
		'operators': ['OP_EQUALS', 'OP_COMPARE','OP_ADD', 'OP_ADD_ASSIGN_VOID', 'OP_MINUS', 'OP_MINUS_ASSIGN_VOID', 'OP_MULTIPLY', 'OP_MULTIPLY_ASSIGN_VOID', 'OP_DIVID', 'OP_DIVID_ASSIGN_VOID'],
		"param_constructors": [
			['float', 'float', 'float'],
			['float', 'float', 'float', 'float'],
		],
		"flags": 'asOBJ_APP_CLASS_ALLFLOATS',
		"convertions": ['Variant']
	},
	"NodePath": {
		"convertions": ['Variant'],
		"ext_copy_constructors": [
			"String"
		],
	},
	"REF": {
		"ext_copy_constructors": [],
		"convertions": ['Variant']
	},
	"RID": {
		"flags": "asOBJ_APP_CLASS_ALLINTS",
		"ext_copy_constructors": [],
		"convertions": ['Variant']
	},
	"Dictionary": {
		"convertions": ['Variant'],
	},
	"Array": {
		'operators': ['OP_EQUALS'],
		"convertions": ['Variant']
	},
	"PoolByteArray": {
		"convertions": ['Variant'],
		"ignore_methods": [
			# TODO
			"compress", "decompress", "get_string_from_ascii", "get_string_from_utf8"
		]
	},
	"PoolIntArray": {
		"convertions": ['Variant']
	},
	"PoolRealArray": {
		"convertions": ['Variant']
	},
	"PoolStringArray": {
		"convertions": ['Variant']
	},
	"PoolVector2Array": {
		"convertions": ['Variant']
	},
	"PoolVector3Array": {
		"convertions": ['Variant']
	},
	"PoolColorArray": {
		"convertions": ['Variant']
	},
	"Variant": {
		"param_constructors": [
			['bool'],
			['int'],
			['uint'],
			['float'],
			['double'],
			['String'],
		],
		"ext_copy_constructors": [],
		"convertions": [
			"bool",
			"int",
			"uint",
			"float",
			"double",
			"String",
			"StringName",
			"Vector2",
			"Rect2",
			"Vector3",
			"Plane",
			"AABB",
			"Quat",
			"Basis",
			"Transform",
			"Transform2D",
			"Color",
			"NodePath",
			"REF",
			"RID",
			"Dictionary",
			"Array",
			"PoolByteArray",
			"PoolIntArray",
			"PoolRealArray",
			"PoolStringArray",
			"PoolVector2Array",
			"PoolVector3Array",
			"PoolColorArray",
		]
	},
}

def line(text):
	return text + '\n'

def glob_path(path, pattern):
	import fnmatch
	result = []
	for root, subdirs, files in os.walk(path):
		for filename in files:
			if fnmatch.fnmatch(filename, pattern):
				result.append(os.path.join(root, filename))
	return result

def save_text_file(filename, text):
	try:
		needUpdate = True
		path = os.path.join(ROOT_DIR, filename)
		if os.path.isfile(path):
			if text == open(path).read():
				needUpdate = False
		if needUpdate:
			open(path, 'w').write(text)
	except Exception as e:
		print("Failed to generate core.gen.h")
		print(e)

# load methods from xml docs
def load_core_xml_doc(dir, accept_cls=[]):
	classes = {}
	def parseClass(data):
		def parseMethod(data):
			dictMethod = dict(data.attrib)
			dictMethod['description'] = data.find("description").text.strip()
			dictMethod['return_type'] = data.find("return").attrib["type"] if data.find("return") is not None else ""
			if "qualifiers" not in dictMethod:  dictMethod["qualifiers"] = ""
			dictMethod["arguments"] = []
			for arg in data.iter('argument'):
				dictMethod["arguments"].append(parseArgument(arg))
			return dictMethod
		def parseArgument(data):
			dictArg = dict(data.attrib)
			if "dictArg" in dictArg: dictArg.pop("index")
			dictArg["default_value"] = dictArg["default"] if "default" in dictArg else ""
			if "default" in dictArg: dictArg.pop("default")
			return dictArg
		def parseConstant(data):
			dictConst = dict(data.attrib)
			dictConst["description"] = data.text.strip()
			return dictConst
		def parseProperty(data):
			dictProp = dict(data.attrib)
			dictProp["description"] = data.text.strip()
			return dictProp
		dictCls = dict(data.attrib)
		dictCls['brief_description'] = data.find("brief_description").text.strip()
		dictCls['description'] = data.find("description").text.strip()
		dictCls['methods'] = []
		for m in data.find("methods"):
			dictCls['methods'].append(parseMethod(m))
		dictCls['signals'] = []
		for s in (data.find("signals") if data.find("signals") is not None else []):
			dictCls['signals'].append(parseMethod(s))
		dictCls['constants'] = []
		for c in (data.find("constants") if data.find("constants") is not None else []):
			dictCls['constants'].append(parseConstant(c))
		dictCls['properties'] = []
		for m in (data.find("members") if data.find("members") is not None else []):
			dictCls['properties'].append(parseProperty(m))
		dictCls['theme_properties'] = []
		for thi in (data.find("theme_items") if data.find("theme_items") is not None else []):
			dictCls['theme_properties'].append(parseProperty(thi))
		return dictCls
	if os.path.isdir(dir):
		for fname in os.listdir(dir):
			if fname.endswith('.xml') and fname.replace('.xml', '') in accept_cls:
				f = os.path.join(dir, fname)
				tree = ET.parse(open(f, 'r'))
				cls = tree.getroot()
				dictCls = parseClass(cls)
				classes[dictCls['name']] = dictCls
	return classes

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
	template = '\tr = engine->RegisterObjectType("{0}", sizeof({0}), {1}asOBJ_VALUE|asGetTypeTraits<{0}>()); ERR_FAIL_COND_V(r<0, r);\n'
	for cls in value_classes:
		flags = ''
		c = value_classes[cls]
		if 'flags' in c and len(c['flags']):
			flags = c['flags'] + '|'
		text += template.format(cls, flags)
	return wrapp_as_register_function('_declare_value_types_gen', text)

def gen_value_behavoirs():
	text = ""
	cdka_template = '''\
	// {0}
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(value_constructor<{0}>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f(const {0} &in)", asFUNCTION(value_copy_constructor<{0}>), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(value_desctructor<{0}>),  asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("{0}", "{0} &opAssign(const {0} &in)", asFUNCTION((value_op_assign<{0}, {0}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	param_constructor_tmp = '''\
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f({1})", asFUNCTION((value_constructor<{0}, {2}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	extc_template = '''\
	r = engine->RegisterObjectBehaviour("{0}", asBEHAVE_CONSTRUCT, "void f(const {1} &in)", asFUNCTION((value_copy_constructor<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	convt_template = '''\
	// {0} ==> {1}
	r = engine->RegisterObjectMethod("{0}", "{0} &opAssign(const {1} &in)", asFUNCTION((value_op_assign<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
	r = engine->RegisterObjectMethod("{0}", "{1} opImplConv() const", asFUNCTION((value_convert<{0}, {1}>)), asCALL_CDECL_OBJLAST); ERR_FAIL_COND_V(r<0, r);
'''
	def bind_method(cls, md):
		def gen_signature(md):
			qualifiers = ' const' if md['qualifiers'] == 'const' else ''
			args = ''
			idx = 0
			for arg in md['arguments']:
				type = arg['type']
				type = type if type != "var" else "Variant"
				type = type if type != "Object" else "bindings::Object@"
				if type in value_classes:
					type = 'const '+ type +' &in'
				args += type
				if 'default_value' in arg and len(arg['default_value']) > 0:
					val = arg['default_value']
					val = "true" if val == "True" else val
					val = "false" if val == "False" else val
					if type == "const String &in" and not val.startswith("\""):
						val = '\\"' + val + '\\"'
					args += ' arg' + str(idx) + '=' + val
				if arg != md['arguments'][-1]:
					args +=', '
				idx += 1
			ret_type = md['return_type'] if len(md['return_type']) > 0 else "void"
			ret_type = ret_type if ret_type != 'var' else "Variant"
			return '{0} {1}({2}){3}'.format(ret_type, md['name'], args, qualifiers)
		if md['name'] == cls or ('ignore_methods' in value_classes[cls] and md['name'] in value_classes[cls]['ignore_methods']): return ''
		else:
			return '\tr = engine->RegisterObjectMethod("{0}", "{1}", asMETHOD({0}, {2}), asCALL_THISCALL); ERR_FAIL_COND_V(r<0, r);\n'.format(cls, gen_signature(md), md['name'])

	for cls in value_classes:
		cfg = value_classes[cls]
		text += cdka_template.format(cls)
		if cfg and 'ext_copy_constructors' in cfg:
			for ext_type in cfg['ext_copy_constructors']:
				text += extc_template.format(cls,ext_type)
		if cfg and 'param_constructors' in cfg:
			for plist in cfg['param_constructors']:
				params = ''
				idx = 0
				for p in plist:
					if p in value_classes:
						p = "const " + p + " &in"
					params += p
					if idx < len(plist) - 1:
						params += ', '
					idx += 1
				text += param_constructor_tmp.format(cls, params, params.replace(" &in", "&"))
		if cfg and 'convertions' in cfg:
			for ext_type in cfg['convertions']:
				text += convt_template.format(cls,ext_type)
		if cfg and 'operators' in cfg and len(cfg['operators']) > 0:
			text += '\t// Operators\n'
			for op in cfg['operators']:
				text += OPERATOR_MAP[op].format(cls)
		if cls in CLASS_INFO:
			cls_info = CLASS_INFO[cls]
			if 'methods' in cls_info:
				if len(cls_info['methods']) > 0:
					text += '\t// {0} methods\n'.format(cls)
				for md in cls_info['methods']:
					text += bind_method(cls, md)
	return wrapp_as_register_function('_define_value_types_gen', text)

def generate_code_text():
	output_cpp = line('''\
#include "value_types.h"
#include "utils.h"
#include <core/variant.h>
#include <core/reference.h>
#include <core/math/math_2d.h>
#include <core/math/vector3.h>
#include <core/math/aabb.h>
#include <core/math/plane.h>
#include <core/math/transform.h>
#include <angelscript.h>
''')
	output_cpp += line('')
	output_cpp += line('namespace asb {')
	output_cpp += line(gen_declare_core_types())
	output_cpp += line('')
	output_cpp += line(gen_value_behavoirs())
	output_cpp += line('}')
	save_text_file(VALUE_TARGET, output_cpp)

if __name__ == '__main__':
	CLASS_INFO = load_core_xml_doc(os.path.join(GODOT_ROOT, 'doc', 'classes'), list(value_classes.keys()))
	generate_code_text()




