/*
 * Do.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef DO_H_
#define DO_H_

#include "Stmt.h"

class Do: public Stmt {
public:
	Expr* expr;
	Stmt* stmt;

	Do() :
			expr(NULL), stmt(NULL) {
	}

	virtual void init(Stmt* s, Expr* x) {
		expr = x;
		stmt = s;
		if (*expr->type != Type::Bool)
			expr->error("boolean required in do");
	}

	virtual void gen(int b, int a) {
		after = a;
		int label = newlabel();   // label for expr
		stmt->gen(b, label);
		emitlabel(label);
		expr->jumping(b, 0);
	}

	virtual ~Do() {
	}
};

#endif /* DO_H_ */
