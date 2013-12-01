/*
 * Id.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef ID_H_
#define ID_H_

#include "Expr.h"

class Id: public Expr {
public:
	int offset;     // relative address
	Id(Word* id, Type* p, int b) :
			Expr(id, p), offset(b) {
	}

	virtual ~Id() {
	}
};

#endif /* ID_H_ */
