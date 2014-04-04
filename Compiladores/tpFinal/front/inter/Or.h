/*
 * Or.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef OR_H_
#define OR_H_

#include "Logical.h"

class Or: public Logical {
public:
	Or(Token* tok, Expr* x1, Expr* x2) :
			Logical(tok, x1, x2) {
	}

	virtual void jumping(int t, int f) {
		int label = t != 0 ? t : newlabel();
		expr1->jumping(label, 0);
		expr2->jumping(t, f);
		if (t == 0)
			emitlabel(label);
	}
	virtual ~Or() {
	}
};

#endif /* OR_H_ */
