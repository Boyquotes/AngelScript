#ifndef AS_BINDING_VALUE_TYPES_H
#define AS_BINDING_VALUE_TYPES_H
#include <core/int_types.h>

class asIScriptEngine;
namespace asb {

typedef uint32_t uint;

int declare_value_types(asIScriptEngine *engine);
int _declare_value_types_gen(asIScriptEngine *engine);

int define_value_types(asIScriptEngine *engine);
int _define_value_types_gen(asIScriptEngine *engine);

}

#endif // AS_BINDING_VALUE_TYPES_H
