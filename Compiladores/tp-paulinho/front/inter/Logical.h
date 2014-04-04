/*
 * Logical.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef LOGICAL_H_
#define LOGICAL_H_

#include "Expr.h"
#include "Temp.h"

class Logical: public Expr {
public:
	Expr *expr1, *expr2;

	Logical(Token* tok, Expr* x1, Expr* x2) :
			Expr(tok, NULL), expr1(x1), expr2(x2) {
		type = this->check(expr1->type, expr2->type);

		if (type == NULL)
			error("type error");
	}

	Logical(Token* tok, Expr* x1, Expr* x2, bool i) :
			Expr(tok, NULL), expr1(x1), expr2(x2) {
		if (i)
			type = NULL;
	}

	virtual Type* check(Type* p1, Type* p2) {

		if (*p1 == Type::Bool && *p2 == Type::Bool)
			return &Type::Bool;
		else
			return NULL;
	}

	virtual Expr* gen() {
		int f = newlabel();
		int a = newlabel();
		Temp* temp = new Temp(type);
		this->jumping(0, f);
		emit(temp->toString() + " = true");
		emit("goto L" + to_string(a));
		emitlabel(f);
		emit(temp->toString() + " = false");
		emitlabel(a);
		return temp;
	}

	virtual string toString() {
		return expr1->toString() + " " + op->toString() + " "
				+ expr2->toString();
	}
	virtual ~Logical() {
	}
};

#endif /* LOGICAL_H_ */
