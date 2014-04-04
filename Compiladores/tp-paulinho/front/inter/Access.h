/*
 * Access.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef ACCESS_H_
#define ACCESS_H_

#include "Op.h"
#include "Id.h"

class Access: public Op {
public:
	Id* array;
	Expr* index;

	Access(Id* a, Expr* i, Type* p) :
			Op(new Word("[]", Tag::INDEX), p), // flattening the array
			array(a), index(i) {    // p is element type after
	}

	virtual Expr* gen() {
		return new Access(array, index->reduce(), type);
	}

	virtual void jumping(int t, int f) {
		emitjumps(reduce()->toString(), t, f);
	}

	virtual string toString() {
		return array->toString() + "[" + index->toString() + "]";
	}
	virtual ~Access() {
	}
};

#endif /* ACCESS_H_ */
