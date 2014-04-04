/*
 * Unary.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef UNARY_H_
#define UNARY_H_

#include "Op.h"

class Unary: public Op {
public:
	Expr* expr;

	Unary(Token* tok, Expr* x) :
			Op(tok, NULL) {    // handles minus, for ! see Not
		expr = x;
		type = Type::max(Type::Int, *expr->type);
		if (type == NULL)
			error("type error");
	}

	virtual Expr* gen() {
		return new Unary(op, expr->reduce());
	}

	virtual string toString() {
		return op->toString() + " " + expr->toString();
	}

	virtual ~Unary() {
	}
};

#endif /* UNARY_H_ */
