/*
 * Constant.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "Expr.h"
#include "../lexer/Num.h"

class Constant: public Expr {
public:
	Constant(Token* tok, Type* p) :
			Expr(tok, p) {
	}
	Constant(int i) :
			Expr(new Num(i), &Type::Int) {
	}

	static const Constant *True, *False;

	virtual void jumping(int t, int f) {
		if (this == True && t != 0)
			emit("goto L" + to_string(t));
		else if (this == False && f != 0)
			emit("goto L" + to_string(f));
	}
	virtual ~Constant() {
	}
};

#endif /* CONSTANT_H_ */
