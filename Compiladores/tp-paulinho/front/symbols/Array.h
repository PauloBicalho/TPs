/*
 * Array.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "Type.h"

class Array: public Type {
public:
	Type* of;                  // array *of* type
	int size;             // number of elements

	Array(int sz, Type* p) :
			Type("[]", Tag::INDEX, sz * p->width), of(p), size(size) {
	}

	friend ostream& operator<<(ostream &out, const Array &array) {
		out << "[" << array.size << "] " << *array.of;
		return out;
	}

	virtual string toString() {
		return "[" + of->toString() + "]";
	}

	virtual ~Array() {
		//talvez deletar of
	}
	;
};

#endif /* ARRAY_H_ */
