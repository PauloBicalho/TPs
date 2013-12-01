/*
 * Set.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef SET_H_
#define SET_H_
#include "Stmt.h"
#include "Id.h"

class Set: public Stmt {
public:

	Id* id;
	Expr* expr;

	Set(Id* i, Expr* x) {
		id = i;
		expr = x;
		if (check(id->type, expr->type) == NULL)
			error("type error");
	}

	virtual Type* check(Type* p1, Type* p2) {
		if (Type::numeric(*p1) && Type::numeric(*p2))
			return p2;
		else if (*p1 == Type::Bool && *p2 == Type::Bool)
			return p2;
		else
			return NULL;
	}

	virtual void gen(int b, int a) {
		emit(id->toString() + " = " + expr->gen()->toString());
		if (a || b) {
			;
		}
	}

	virtual ~Set() {
	}
};

#endif /* SET_H_ */
