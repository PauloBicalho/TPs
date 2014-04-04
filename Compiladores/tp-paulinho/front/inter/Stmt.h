/*
 * Stmt.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef STMT_H_
#define STMT_H_

#include "Node.h"

class Stmt: public Node {
public:
	int after;
	static Stmt* Null;
	static Stmt* Enclosing;
	Stmt() :
			after(0) {
	}

	virtual void gen(int b, int a) {
		if (a || b) {
			;
		}
	}

	virtual ~Stmt() {
	}
};

#endif /* STMT_H_ */
