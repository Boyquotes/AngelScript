#ifndef AS_BINDING_OBJECT_H
#define AS_BINDING_OBJECT_H

#include <core/ustring.h>

class asIScriptEngine;

namespace asb {

int declare_object_types(asIScriptEngine* engine);
int define_object_types(asIScriptEngine* engine);

}

#endif // AS_BINDING_OBJECT_H
