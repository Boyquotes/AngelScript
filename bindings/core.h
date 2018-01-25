#ifndef AS_BINDING_CORE_H
#define AS_BINDING_CORE_H
#include <core/variant.h>

class asIScriptEngine;

template<class T> void as_value_constructor(T *p_this) {
	memnew_placement(p_this, T);
}

template<class T> void as_value_copy_constructor(const T &other, T *p_this) {
	memnew_placement(p_this, T(other));
}

template<class T, class P> void as_value_copy_constructor(const P &other, T *p_this) {
	memnew_placement(p_this, T(other));
}

template<class T> void as_value_desctructor(T *p_this) {
	if(p_this) p_this->~T();
}

template<class T, class P> T& as_value_op_assign(const P &p_value, T &p_dest) {
	p_dest = p_value;
	return p_dest;
}

template<class T, class P> T& as_value_op_assign_raw(P p_value, T &p_dest) {
	p_dest = p_value;
	return p_dest;
}

template<class T, class P>
static P as_value_convert(T *p_this) {
	return *p_this;
}

template<class T>
static T* as_object_factory() {
	return memnew(T);
}

int gen_as_declare_core_types(asIScriptEngine* engine);
int as_declare_core_types(asIScriptEngine* engine);
int gen_as_bind_core_value_type_behavoirs(asIScriptEngine* engine);
int as_core_binding_manual(asIScriptEngine* engine);

#endif // AS_BINDING_CORE_H
