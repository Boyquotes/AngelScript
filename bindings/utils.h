#ifndef AS_BINDING_UTILS_H
#define AS_BINDING_UTILS_H
#include <core/object.h>
#include <core/os/memory.h>
#include <angelscript.h>

namespace asb {

static void * as_memalloc(size_t size) {
	return memalloc(size);
}

static void as_memfree(void* ptr) {
	memrealloc(ptr, 0);
}

/**
 * Default constructor for value types
 */
template<class T>
void value_constructor(T *p_this) {
	memnew_placement(p_this, T);
}

template<class T, class P>
void value_constructor(P p1, T *p_this) {
	memnew_placement(p_this, T(p1));
}

template<class T, class P1, class P2>
void value_constructor(P1 p1, P2 p2, T *p_this) {
	memnew_placement(p_this, T(p1, p2));
}

template<class T, class P1, class P2, class P3>
void value_constructor(P1 p1, P2 p2, P3 p3, T *p_this) {
	memnew_placement(p_this, T(p1, p2, p3));
}

template<class T, class P1, class P2, class P3, class P4>
void value_constructor(P1 p1, P2 p2, P3 p3, P4 p4, T *p_this) {
	memnew_placement(p_this, T(p1, p2, p3, p4));
}

/**
 * Destructor of value types
 */
template<class T>
void value_desctructor(T *p_this) {
	if(p_this) p_this->~T();
}

/**
 * Default copy constructor for value types
 */
template<class T>
void value_copy_constructor(const T &other, T *p_this) {
	memnew_placement(p_this, T(other));
}

/**
 * Copy constructor from another value type
 */
template<class T, class P>
void value_copy_constructor(const P &other, T *p_this) {
	memnew_placement(p_this, T(other));
}

/**
 * Assignment operator for value types
 */
template<class T, class P>
T& value_op_assign(const P &p_value, T &p_dest) {
	p_dest = p_value;
	return p_dest;
}

/**
 * Type convertion for value types that supported by Variant
 */
template<class T, class P>
static P value_convert(T *p_this) {
	return *p_this;
}

/**
 * Construct objects
 */
template<class T>
static T* object_factory() {
	return memnew(T);
}

/**
 * free objects
 */
template<class T>
void object_free(T* p_this) {
	if (p_this) memdelete(p_this);
}

/**
 * Assignment operator
 */
template<class T, class P>
T& op_assign(P p_value, T &p_dest) {
	p_dest = p_value;
	return p_dest;
}

/**
 * Type cast for object types
 */
template<class T, class P>
P* object_convert(T* p_this) {
	return Object::cast_to<P>(p_this);
}

}
#endif // AS_BINDING_UTILS_H
