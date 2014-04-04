/*
 * Real.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#include "Token.h"

#ifndef REAL_H_
#define REAL_H_

class Real: public Token {
public:
	const float value;
	Real(float v) :
			Token(Tag::REAL), value(v) {
	}
	friend ostream& operator<<(ostream &out, const Real &real) {
		out << real.value;
		return out;
	}

	virtual string toString() {
		return ("const_f(" + to_string(value)) + ")";
	}

	virtual ~Real() {
	}
	;
};

#endif /* REAL_H_ */
