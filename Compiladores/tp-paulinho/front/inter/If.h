/*
 * If.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef IF_H_
#define IF_H_

#include "Stmt.h"

class If: public Stmt {
public:
	Expr* expr;
	Stmt* stmt;

	If(Expr* x, Stmt* s) {
		expr = x;
		stmt = s;

		if (*expr->type != Type::Bool)
			expr->error("boolean required in if");
	}

	virtual void gen(int b, int a) {
		int label = newlabel(); // label for the code for stmt
		expr->jumping(0, a);     // fall through on true, goto a on false
		emitlabel(label);
		stmt->gen(label, a);
		if (b) {
			;
		}
	}
	virtual ~If() {
	}
};

#endif /* IF_H_ */
