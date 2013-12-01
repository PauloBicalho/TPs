/*
 * SetElem.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#include "Stmt.h"
#include "Id.h"
#include "Expr.h"
#include "Access.h"

#ifndef SETELEM_H_
#define SETELEM_H_

class SetElem: public Stmt {
public:
	Id* array;
	Expr* index;
	Expr* expr;

	SetElem(Access* x, Expr* y) {
		array = x->array;
		index = x->index;
		expr = y;
		if (check(x->type, expr->type) == NULL)
			error("type error");
	}

	virtual Type* check(Type* p1, Type* p2) {
		Array* a1 = dynamic_cast<Array*>(p1);
		Array* a2 = dynamic_cast<Array*>(p2);
		if (a1 || a2)
			return NULL;
		else if (p1 == p2)
			return p2;
		else if (Type::numeric(*p1) && Type::numeric(*p2))
			return p2;
		else
			return NULL;
	}

	virtual void gen(int b, int a) {
		string s1 = index->reduce()->toString();
		string s2 = expr->reduce()->toString();
		emit(array->toString() + "[" + s1 + "] = " + s2);
		if (a || b) {
			;
		}
	}
	virtual ~SetElem() {
	}
};

#endif /* SETELEM_H_ */
