/*
 * While.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef WHILE_H_
#define WHILE_H_

#include "Stmt.h"

class While: public Stmt {
public:
	Expr* expr;
	Stmt* stmt;

	While() {
		expr = NULL;
		stmt = NULL;
	}

	virtual void init(Expr* x, Stmt* s) {
		expr = x;
		stmt = s;
		if (*expr->type != Type::Bool)
			expr->error("boolean required in while");
	}
	virtual void gen(int b, int a) {
		after = a;                // save label a
		expr->jumping(0, a);
		int label = newlabel();   // label for stmt
		emitlabel(label);
		stmt->gen(label, b);
		emit("goto L" + to_string(b));
	}
	virtual ~While() {
	}
};

#endif /* WHILE_H_ */
