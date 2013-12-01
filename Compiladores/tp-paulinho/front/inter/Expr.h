/*
 * Expr.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef EXPR_H_
#define EXPR_H_

#include "Node.h"
#include "../symbols/Type.h"
#include "../lexer/Token.h"
#include <sstream>

class Expr: public Node {
public:
	Token* op;
	Type* type;

	Expr(Token* tok, Type* p) :
			op(tok), type(p) {
	}

	virtual Expr* gen() {
		return this;
	}
	virtual Expr* reduce() {
		return this;
	}

	virtual void jumping(int t, int f) {
		emitjumps(toString(), t, f);
	}

	virtual void emitjumps(string test, int t, int f) {
		if (t != 0 && f != 0) {
			emit("if " + test + " goto L" + to_string(t));
			emit("goto L" + to_string(f));
		} else if (t != 0) {
			emit("if " + test + " goto L" + to_string(t));
		} else if (f != 0) {
			emit("iffalse " + test + " goto L" + to_string(f));
		} else {
			; // nothing since both t and f fall through
		}
	}
	virtual string toString() {
		return "var_" + type->toString() + "(" + op->toString() + ")";
	}
	virtual ~Expr() {
	}
	;
};

#endif /* EXPR_H_ */
