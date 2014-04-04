/*
 * Op.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef OP_H_
#define OP_H_

#include "Expr.h"
#include "Temp.h"

class Op: public Expr {
public:

	Op(Token* tok, Type* p) :
			Expr(tok, p) {
	}

	virtual Expr* reduce() {
		Expr* x = gen();
		Temp* t = new Temp(type);
		emit(t->toString() + " = " + x->toString());
		return t;
	}
	virtual ~Op() {
	}
	;
};

#endif /* OP_H_ */
