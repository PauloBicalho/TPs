/*
 * Break.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef BREAK_H_
#define BREAK_H_

#include "Stmt.h"

class Break: public Stmt {
public:
	Stmt* stmt;

	Break() {
		if (Stmt::Enclosing == Stmt::Null)
			error("unenclosed break");
		stmt = Stmt::Enclosing;
	}

	virtual void gen(int b, int a) {
		emit("goto L" + to_string(stmt->after));
		if (a || b) {
			;
		}
	}
	virtual ~Break() {
	}
};

#endif /* BREAK_H_ */
