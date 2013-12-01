/*
 * Arith.h
 *
 *  Created on: Nov 28, 2013
 *      Author: itamar
 */

#ifndef ARITH_H_
#define ARITH_H_

#include "Op.h"

class Arith: public Op {
public:

	Expr* expr1, *expr2;

	Arith(Token* tok, Expr* x1, Expr* x2) :
			Op(tok, NULL), expr1(x1), expr2(x2) {

		type = Type::max(*expr1->type, *expr2->type);
		if (type == NULL)
			error("type error");
	}

	virtual Expr* gen() {
		return new Arith(op, expr1->reduce(), expr2->reduce());
	}

	virtual string toString() {
		if (type->lexeme == "float")
			return expr1->toString() + " (f" + op->toString() + ") "
					+ expr2->toString();
		return expr1->toString() + " (i" + op->toString() + ") "
				+ expr2->toString();
	}
	virtual ~Arith() {
	}
};

#endif /* ARITH_H_ */
