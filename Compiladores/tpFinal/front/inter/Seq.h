/*
 * Seq.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef SEQ_H_
#define SEQ_H_

#include "Stmt.h"

class Seq: public Stmt {
public:

	Stmt* stmt1;
	Stmt* stmt2;

	Seq(Stmt* s1, Stmt* s2) {
		stmt1 = s1;
		stmt2 = s2;
	}

	virtual void gen(int b, int a) {
		if (stmt1 == Stmt::Null)
			stmt2->gen(b, a);
		else if (stmt2 == Stmt::Null)
			stmt1->gen(b, a);
		else {
			int label = newlabel();
			stmt1->gen(b, label);
			emitlabel(label);
			stmt2->gen(label, a);
		}
	}
	virtual ~Seq() {
	}
};

#endif /* SEQ_H_ */
