/*
 * And.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef AND_H_
#define AND_H_

#include "Logical.h"

class And: public Logical {
public:
	And(Token* tok, Expr* x1, Expr* x2) :
			Logical(tok, x1, x2) {
	}

	virtual void jumping(int t, int f) {
		int label = f != 0 ? f : newlabel();
		expr1->jumping(0, label);
		expr2->jumping(t, f);
		if (f == 0)
			emitlabel(label);
	}
	virtual ~And() {
	}
};

#endif /* AND_H_ */
