/*
 * Rel.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef REL_H_
#define REL_H_

#include "Logical.h"
#include "../symbols/Array.h"

class Rel: public Logical {
public:
	Rel(Token* tok, Expr* x1, Expr* x2) :
			Logical(tok, x1, x2, true) {
		type = this->check(expr1->type, expr2->type);
		if (type == NULL)
			error("type error");
	}

	virtual Type* check(Type* p1, Type* p2) {

		Array* a1 = dynamic_cast<Array*>(p1);
		Array* a2 = dynamic_cast<Array*>(p2);
		if (a1 || a2)
			return NULL;
		else if (*p1 == *p2)
			return &Type::Bool;
		else
			return NULL;
	}

	virtual void jumping(int t, int f) {
		Expr* a = expr1->reduce();
		Expr* b = expr2->reduce();
		string test = a->toString() + " " + op->toString() + " "
				+ b->toString();
		emitjumps(test, t, f);
	}
	virtual ~Rel() {
	}
};

#endif /* REL_H_ */
