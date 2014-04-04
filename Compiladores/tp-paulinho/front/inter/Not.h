/*
 * Not.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef NOT_H_
#define NOT_H_

#include "Logical.h"

class Not: public Logical {
public:
	Not(Token* tok, Expr* x2) :
			Logical(tok, x2, x2) {
	}

	virtual void jumping(int t, int f) {
		expr2->jumping(f, t);
	}

	virtual string toString() {
		return op->toString() + " " + expr2->toString();
	}
	virtual ~Not() {
	}
};

#endif /* NOT_H_ */
